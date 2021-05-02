---
date: "2007-08-09"
title: "Antidebug: interpretação baseada em exceção (parte 2)"
categories: [ "code" ]
---
No [primeiro artigo] vimos como é possível "enganar" o depurador através de exceções e assim fazer o atacante perder um tempo considerável tentando se desvencilhar dos breakpoints de mentira. Porém, vimos também que essa é uma solução difícil de manter no código-fonte, além de possuir o ponto fraco de ser facilmente contornada se descoberta. Agora é a hora de tornar as coisas mais fáceis de manter e ao mesmo tempo garantir maior dificuldade mesmo que o atacante descubra o que está acontecendo debaixo do seu nariz.

O upgrade apresentado aqui continua utilizando o lançamento de exceções intrinsecamente, mas agora não depende mais da divisão do código em minifunções e chamá-las aos poucos. Em vez disso, temos apenas que pegar traços de código e colocá-los em torno de uma macro milagrosa que fará tudo o que quisermos. Isso, claro, depois de algumas marteladas que serão explicadas aqui.

    void LongJmp(restorePoint)
    {
      BackToStart(restorePoint);
    }
    
    int Start()
    {
      if( RestorePoint() == Defined )
      {
        LongJmp(if);
      }
      else
      {
        CallFunc();
      }
    
      return 0;
    }

A solução acima está apresentada em pseudo-código para tornar mais claro o conceito. Note que existe uma espécie de "retorno invisível", não baseado em retorno de pilha, envolvido. Para implementá-lo, contudo, podemos nos ajeitar com o velho e bom padrão C ANSI, com as rotinas setjmp  e longjmp. Para entender a implementação dessa funções na plataforma 8086 precisamos ter primeiro uma visão básica da estrutura de chamada de funções baseada em pilha.

Registradores são variáveis reservadas do processador que podem ser utilizadas pelo código assembly da plataforma envolvida. Stack frame (estrutura da pilha) nada mais é que a hierarquia de chamadas das funções, o "quem chamou quem" em uma execução qualquer. Call e ret são instruções em assembly para chamar uma função (call) e sair de uma função (ret), respectivamente. Ambas alteram o stack frame.

Imagine que você tem uma função, CallFunc, e outra função, Func, e que uma chame a outra. Para analisarmos apenas a chamada de função, e apenas isso, vamos considerar que Func não recebe nenhum parâmetro e não retorna nenhum valor. O código em C fica, então, assim:

    void Func()
    {
      return;
    }
    
    void CallFunc()
    {
      Func();
    }

Simples, não? Por esse mesmo motivo o disassembly terá que ser igualmente simples. Em CallFunc ele deverá conter a chamada da função (call) e em Func o retorno da chamada (ret). Se você compilar o código acima e o assembly vier com mais coisas pode ser que que eventualmente apareça mais código embutido em versões Debug, ou se estiver muito diferente ou inexistente pode ser uma otimização do seu compilador.

    Func:
    00411F73 prev_instruction ; ESP = 0012FD38 (four bytes stacked up)
    00411F74 ret ; *ESP = 00411FA3 (return address)
    
    CallFunc:
    00411F9C prev_instruction
    00411F9E call Func (411424h) ; ESP = 0012FD3C
    00411FA3 next_instruction

A partir do assembly acima podemos concluir no mínimo duas coisas:

 1. a pilha "cresce" para baixo, pois seu valor decrementou de quadro (0012FD3C para 0012FD38 são 4 byte a menos).
 2. o valor de retorno da função chamada é o endereço da próxima instrução após a chamada (call), no caso 00411FA3.

Ora, da mesma forma que conseguimos acompanhar essa simples execução, o atacante também o fará. Por isso que no meio dessa chamada iremos colocar o lançamento de uma exceção e, no retorno, faremos não do modo convencional apresentado, mas por uma outra técnica que, ao invés de utilizar a instrução ret, seta "manualmente" o valor do registrador ESP (estado da pilha) e "pula" para a próxima instrução de CallFunc.

    Func:
    00411F60 throw_exception
    00411F61 ...
    00411F73 catch_exception
    00411F74 mov ESP, 0012FD3C ; ESP = 0012FD3C, como em CallFunc
    00411F75 jmp 00411FA3 ; "pula" para CallFunc::next_instruction

Toda essa esculhambada em assembly não precisa ser necessariamente feita em linguagem de baixo nível. Foi apenas uma maneira que encontrei pra ilustrar as diferenças entre retorno baseado em pilha e alteração no fluxo do código. Como já foi dito, para a sorte e o bem-estar de todos, essa mesma técnica pode ser implementada com funções C da biblioteca ANSI:

    jmp_buf stack_state;

    void Func()
    {
      longjmp(stack_state, 1);
    }
    
    void CallFunc()
    {
      // setting returns 0
      // returning returns not 0
      if( setjmp(stack_state) == 0 )
        Func();
    
      int x = 10;
    }

Essa foi a técnica adicionada à solução do lançamento de exceções. E o [código final] ficou mais claro (além de rápido, por economizar o uso de uma thread para leitura dos comandos).

    /** The only purpose of 
      this function is to 
      generate an exception. */
    DWORD LongJmp(jmp_buf* env)
    {
      __try
      {
        __asm int 3
      }
        __except( EXCEPTION_EXECUTE_HANDLER )
      {
        longjmp(*env, 1);
      }
    
      return ERROR_SUCCESS;
    }
    
    /** And God said: 
      'int main!'
    */
    int main()
    {
      DWORD ret = ERROR_SUCCESS;
    
      while( cin )
      {
        string line;
    
        cout << "Type something\n";
        getline(cin, line);
    
        jmp_buf env;
    
        if( setjmp(env) == 0 )
        {
          LongJmp(&env);
        }
        else
        {
          cout << line << endl;
        }
      }
    
      return (int) ret;
    } 

À primeira vista parece um desperdício o if estar diretamente no código (lembre-se que vamos utilizar a mesma estrutura condicional em várias e várias partes do código. Para tornar mais claro seu uso, resumir a chamada protegida e permitir que a proteção seja desabilitada em debug, vamos criar uma macro:

    /** Use this macro instead LongJmp
    */
    #define ANTIDEBUG(code)
    {
      jmp_buf env;
    
      if( setjmp(env) == 0 )
      {
        LongJmp(&env);
      }
      else
      {
        code;
      }
    }
    
    /** And God said: 'int main!'
    */
    int main()
    {
      DWORD ret = ERROR_SUCCESS;
    
      while( cin )
      {
        string line;
    
        cout << "Type something\n";
        getline(cin, line);
    
        ANTIDEBUG(( cout << line << endl ));
      }
    
      return (int) ret;
    } 

Veja que como agora permitimos a seleção do anti-debug por chamada, fica mais fácil escolher quais os pontos a serem protegidos e quais não devem/podem por conta de perfomance ou outro detalhe obscuro que sempre existe na vida de um programador C++.

[primeiro artigo]: /antidebug-interpretacao-baseada-em-excecao-parte-1
[código final]: /code/antidebug-exception-2.cpp
