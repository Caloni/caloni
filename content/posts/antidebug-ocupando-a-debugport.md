---
date: "2007-08-23"
title: "Antidebug: ocupando a DebugPort"
tags: [ "code" ]
---
Quando um depurador inicia um processo para ser depurado ou, o caso abordado por este artigo, se conecta em um processo já iniciado, as comunicações entre esses dois processos é feita através de um recurso interno do Windows chamado de LPC (Local Procedure Call). O sistema cria uma "porta mágica" de comunicação específica para a depuração e os eventos trafegam por meio dela.

Entre esses eventos podemos citar os seguintes:
    
 - Breakpoints disparados.
 - Exceções lançadas.
 - Criação/saída de threads.
 - Load/unload de DLLs.
 - Saída do processo.

No caso de se conectar em um processo já existente, é chamada a função da API DebugActiveProcess. A partir dessa chamada, se retornado sucesso, o processo que depura agora está liberado para ficar chamando continuamente a função API WaitForDebugEvent. E o código se resume a isto:

    void DebugLoop()
    {
    	bool exitLoop = false;
    
    	while( ! exitLoop )
    	{
    		DEBUG_EVENT debugEvt;
    
    		WaitForDebugEvent(&debugEvt, 
          INFINITE);
    
    		switch( debugEvt.dwDebugEventCode )
    		{
    			// This one...
    
    			// That one...
    
    			// Process is going out.
    			case EXIT_PROCESS_DEBUG_EVENT:
    			  exitLoop = true;
    			  break;
    		}
    
    		// Unfreeze the thread who sent the debug event.
    		// Otherwise, it stays frozen forever!
    		ContinueDebugEvent(debugEvt.dwProcessId, 
          debugEvt.dwThreadId, 
          DBG_EXCEPTION_NOT_HANDLED);
    	}
    } 

O detalhe interessante desse processo de comunicação depurador/depurado é que um processo só pode ser depurado por apenas UM depurador. Ou seja, enquanto houver um processo depurando outro, os outros processos só ficam na vontade.

Partindo desse princípio, podemos imaginar uma proteção baseada nessa exclusividade, criando um processo protetor que conecta no processo protegido e o "depura". Fiz um [código de exemplo] que faz justamente isso: ele atacha em um processo para depurá-lo (basta passar o PID como parâmetro) e não deixa mais outro depurador ocupar a debug port. Os passos para testá-lo são:

  1. Compilar o código.
  2. Executar o notepad (ou qualquer outra vítima).
  3. Obter seu PID (Process ID).
  4. Executar o protetor passando o PID como parâmetro.
  5. Tentar "atachar" no processo através do Visual C++.

Após o processo de attach, a porta de debug é ocupada, e a comunicação entre depurador e depurado é feita através do LPC. Abaixo uma pequena ilustração de como as coisas ocorrem:

![Como funciona o LPC](/img/debugport.gif)

Basicamente o processo fica recebendo eventos de debug (através da fila de mensagens LPC) continuamente até o evento final, o de final de processo. Note que se alguém tentar derrubar o processo que depura o processo depurado cai junto.

O ponto forte desse tipo de proteção é que não afeta a compreensão e a legibilidade do código. De fato o próprio código que "protege" está em outro processo. O fraco, eu diria, é a sua alta visibilidade. Todo mundo que tentar atacar verá dois processos serem criados; e isso já faz pensar...

Por isso é necessário pensar bem na implementação. Particularmente uma coisa a ser bem arquitetada é a união entre depurador e depurado. Quanto melhor essas duas peças forem encaixadas, tão mais difícil será para o atacante separá-las. Uma idéia adicional é utilizar a mesma técnica na direção oposta, ou seja, o processo depurado se atachar no depurador.

Dessa vez não vou afirmar que, uma vez entendido o problema, a solução torna-se óbvia. Isso porque ainda não pensei o suficiente para achar uma solução óbvia. Idéias?

[código de exemplo]: /code/antidebug-debugport.cpp
