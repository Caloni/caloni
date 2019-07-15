---
date: "2007-08-23"
title: 'Antidebug: ocupando a DebugPort'
categories: [ "code" ]
---
Quando um depurador inicia um processo para ser depurado ou, o caso abordado por este artigo, se conecta em um processo já iniciado, as comunicações entre esses dois processos é feita através de um recurso interno do Windows chamado de LPC (Local Procedure Call). O sistema cria uma "porta mágica" de comunicação específica para a depuração e os eventos trafegam por meio dela.

Entre esses eventos podemos citar os seguintes:

    
  * _Breakpoints_ disparados

    
  * Exceções lançadas

    
  * Criação/saída de _threads_

    
  * _Load_/_unload_ de DLLs

    
  * Saída do processo

No caso de se conectar em um processo já existente, é chamada a função da API [DebugActiveProcess](http://www.google.com/url?sa=t&ct=res&cd=1&url=http%3A%2F%2Fmsdn2.microsoft.com%2Fen-us%2Flibrary%2Fms679295.aspx&ei=cqDERvWoA4GKerippJ0M&usg=AFQjCNFzrdQ83SQzTQxBiT9iEauTFyUPcA&sig2=4p-HOh1Wk6uhDYD0ceEMDw). A partir dessa chamada, se retornado sucesso, o processo que depura agora está liberado para ficar chamando continuamente a função API [WaitForDebugEvent](http://www.google.com/url?sa=t&ct=res&cd=1&url=http%3A%2F%2Fmsdn2.microsoft.com%2Fen-us%2Flibrary%2Fms681423.aspx&ei=sqDERq-OFpuOeZC4lJIM&usg=AFQjCNEaUTTzw3ZLCcI35UMrbDAym4lLDg&sig2=GfQ_1OH4BLoOKFmCHXGYDA). E o código se resume a isto:

```cpp
void DebugLoop()
{
	bool exitLoop = false;

	while( ! exitLoop )
	{
		DEBUG_EVENT debugEvt;

		// Wait for some debug event.
		WaitForDebugEvent(&debugEvt, INFINITE);

		// Let us see what it is about.
		switch( debugEvt.dwDebugEventCode )
		{
			// This one...

			// That one...

			// Process is going out. We get out the loop and go away.
			case EXIT_PROCESS_DEBUG_EVENT:
			exitLoop = true;
			break;
		}

		// We need to unfreeze the thread who sent the debug event.
		// Otherwise, it stays frozen forever!
		ContinueDebugEvent(debugEvt.dwProcessId, debugEvt.dwThreadId, DBG_EXCEPTION_NOT_HANDLED);
	}
} 

```

O detalhe interessante desse processo de comunicação depurador/depurado é que um processo só pode ser depurado por apenas UM depurador. Ou seja, enquanto houver um processo depurando outro, os outros processos só ficam na vontade.

Partindo desse princípio, podemos imaginar uma proteção baseada nessa exclusividade, criando um processo protetor que conecta no processo protegido e o "depura":

```cpp
/** @brief Antidebug protection based on DebugPort aquisition.
* @author Wanderley Caloni (wanderley@caloni.com.br)
* @date 2007-08
*/
#include <windows.h>

/* Every debugger needs a debugging loop. In this loop it catches
debugging events sent by the operating system.
*/
DWORD DebugLoop()
{
	DWORD ret = ERROR_SUCCESS;
	bool exitLoop = false;

	while( ! exitLoop )
	{
		DEBUG_EVENT debugEvt;

		WaitForDebugEvent(&debugEvt, INFINITE);

		switch( debugEvt.dwDebugEventCode )
		{
			// Process going out. We get out the loop and leave.
			case EXIT_PROCESS_DEBUG_EVENT:
			exitLoop = true;

			break;
		}

		// Necessary, since the current thread is frozen.
		ContinueDebugEvent(debugEvt.dwProcessId, debugEvt.dwThreadId, DBG_EXCEPTION_NOT_HANDLED);
	}

	return ret;
}

/* Attachs to the protected process againt debugging. Actually, we protect it
againt debugging being its debugger.
*/
DWORD AntiAttach(DWORD pid)
{
	DWORD ret = ERROR_SUCCESS;

	if( pid )
	{
		BOOL dbgActProc;

		dbgActProc = DebugActiveProcess(pid);

		if( dbgActProc )
			DebugLoop();
		else
			ret = GetLastError();
	}
	else
		ret = ERROR_INVALID_HANDLE;

	return ret;
}

/* In the beginning, God said: 'int main!'
*/
int main(int argc, char* argv[])
{
	DWORD ret = ERROR_SUCCESS;

	if( argc > 1 )
	{
		DWORD pid = atoi(argv[1]);
		ret = AntiAttach(pid);
	}

	return (int) ret;
} 

```

Os passos para testar o código acima são:

    
  1. Compilar o código.

    
  2. Executar o notepad (ou qualquer outra vítima).

    
  3. Obter seu PID (Process ID).

    
  4. Executar o protetor passando o PID como parâmetro.

    
  5. Tentar "atachar" no processo através do Visual C++.

Após o processo de _attach_, a porta de _debug_ é ocupada, e a comunicação entre depurador e depurado é feita através do LPC. Abaixo uma pequena ilustração de como as coisas ocorrem:

[![Como funciona o LPC](http://i.imgur.com/n0EzziA.gif)](/images/debug-port.gif)

Basicamente o processo fica recebendo eventos de _debug_ (através da fila de mensagens LPC) continuamente até o evento final, o de final de processo. Note que se alguém tentar derrubar o processo que depura o processo depurado cai junto.

**Infalível? Conte outra**

O ponto forte desse tipo de proteção é que não afeta a compreensão e a legibilidade do código. De fato o próprio código que "protege" está em outro processo. O fraco, eu diria, é a sua alta visibilidade. Todo mundo que tentar atacar verá dois processos serem criados; e isso já faz pensar...

Por isso é necessário pensar bem na implementação. Particularmente uma coisa a ser bem arquitetada é a união entre depurador e depurado. Quanto melhor essas duas peças forem encaixadas, tão mais difícil será para o atacante separá-las. Uma idéia adicional é utilizar a mesma técnica na direção oposta, ou seja, o processo depurado se atachar no depurador.

Dessa vez não vou afirmar que, uma vez entendido o problema, a solução torna-se óbvia. Isso porque ainda não pensei o suficiente para achar uma solução óbvia. Idéias?
