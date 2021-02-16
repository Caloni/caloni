---
date: "2007-07-20"
title: "Antidebug: interpretação baseada em exceção (parte 1)"
tags: [ "draft", "code" ]
---
Um depurador utiliza _breakpoints_ para "paralisar" momentaneamente a execução do programa sendo depurado. Para isso ele se utiliza de uma bem conhecida instrução conhecida como **int 3**. Essa instrução gera uma exceção - exceção de _breakpoint_ - que é capturada pelo sistema operacional e repassada para o **código de tratamento** dessa exceção. Em programas sendo depurados esse código está localizado no depurador. Em programas "livres" esse código normalmente não existe e ao acontecer essa exceção o aplicativo simplesmente "capota".

A idéia principal na proteção baseada em exceção é tomarmos conta dessas exceções durante a execução do aplicativo. Fazendo isso podemos nos aproveitar desse fato e, no código responsável por tratar a exceção, **executar o código protegido**. A solução discutida aqui é parecido com um **interpretador de scripts**. Consiste basicamente de duas _threads_. A primeira thread **lê uma seqüência de instruções** e manda a segunda thread **executá-las passo a passo**. Para fazer isso a segunda thread usa um conjunto de **pequenas funções** com blocos de código bem definidos. Em pseudocódigo isso ficaria assim:

```cpp
// the well-defined functions are functional blocks of code and have
// the same signature, allowing the creation of a pointer array to them
void WellDefinedFunction1( args );
void WellDefinedFunction2( args );
void WellDefinedFunction3( args );
//...
void WellDefinedFunctionN( args );

// this thread stays forever waiting execution commands from some
// well-defined function. the parameter that it receives is the function number
void ExecutionThread()
{
	// 2. ad aeternum
	while( true )
	{
		// 5. it runs some well-defined function by number
		ExecuteWellDefinedFunction( functionNumber );
	}
}

// the well-defined functions script is an integer array indicating 
// the number for the next function that is going to be called
int FunctionsToBeCalled[] = { 3, 4, 1, 2, 34, 66, 982, n };

int Start()
{
	// 1. we create the thread that is going to run commands
	CreateThread( ExecutionThread );

	// 3. for each script item (each function number)
	for( int i = 0; i < sizeof(FunctionsToBeCalled); ++i )
	{
		// 4. tells the thread to run the function number N
		TellExecutionThreadToExecuteWellDefinedFunction( FunctionToBeCalled[i] );
	}

	// 6. end of execution.
	return 0;
} 

```

A proteção ainda não está aí. Mas fará **parte intrínseca** da _thread_ de execução. Tudo que precisamos fazer é adicionar um **tratamento de exceções** e fazer chover ints 3. As exceções disparadas pela int 3 são capturadas por uma segunda função que antes de retornar o controle executa a próxima instrução enfileirada:

```cpp
// filter exceptions that were thrown by the thread below
DWORD ExceptionFilterButExecuteWellDefinedFunction()
{
	// 5. run some well-defined function by number
	ExecuteWellDefinedFunction( number );

	return EXCEPTION_EXECUTE_HANDLER; // goes to except code
}

// this thread stays forever waiting execution commands from a 
// well-defined function. its "parameter" is the function number
void ExecutionThread()
{
	// 2. ad aeternum
	while( true )
	{
		__try
		{
			__asm int 3 // breakpoint exception

			// it stops the debugger if we have an attached debugger in
			// the process, or throws an exception if there is no one
		}
		__except( ExceptionFilterButExecuteWellDefinedFunction() )
		{
			// it does nothing. here is NOT where is the code (obvious, huh?)
		}

		Sleep( someTime ); // give some time
	}
} 

```

O algoritmo da _thread_ de execução continua o mesmo. Só que o ponto onde cada instrução é executada depende do lançamento de uma exceção. Note que essa exceção **tem que ocorrer** para que a chamada da próxima instrução ocorra. Isso é **fundamental**, pois dessa forma ninguém pode simplesmente retirar o int 3 do código para evitar o lançamento da exceção. Se fizer isso, então mais nenhuma instrução será executada.

Na prática, se alguém tentar depurar um programa desse tipo vai ter que enfrentar dezenas ou centenas de lançamento de exceções até descobrir o que está acontecendo. Claro que, como em toda a proteção de software, ela não é definitiva; tem por função **dificultar o trabalho** de quem tenta entender o software. Isso não vai parar aqueles que são [realmente bons no que fazem](http://www.codebreakers-journal.com/).

**Nada é de graça**

O preço pago por essa proteção fica na **visibilidade e compreensão** do código-fonte comprometidos pelo uso da técnica. A programação fica baseada em uma **máquina de estados** e as funções ficam limitadas a algum tipo de padronização no comportamento. Quando mais **granular** for o _pseudoscript_, ou seja, quanto menores forem os blocos de código contido nas minifunções, mais difícil de entender o código será.

O exemplo abaixo recebe entrada por um prompt de comandos e **mapeia a primeira palavra digitada** para o índice de uma função que deve ser chamada. O resto da linha digitada é passado como parâmetro para essa função. A _thread_ de interpretação lê a entrada do usuário e escreve em uma **variável-_string_ global**, ao mesmo tempo que a _thread_ de execução espera essa _string_ ser preenchida para executar a ação. Foi usado o _pool_ dessa variável para o código ficar mais simples, mas o ideal seria algum tipo de sincronismo, como [eventos](http://msdn.microsoft.com/library/en-us/dllproc/base/createevent.asp), por exemplo. Baixe o código-fonte [aqui](/images/antidebug.cpp).

```cpp
/** @brief Sample demonstrating how to implemente antidebug in a code exception based.
@date jul-2007
@author Wanderley Caloni
*/
#include <windows.h>

#include <iostream>
#include <map>
#include <sstream>

#include <string>
#include <stdlib.h>

using namespace std;

// show available commands
bool Help(const string&)
{

   cout << "AntiDebug Test Program\n"
      << " Echo string to be printed\n"
      << " System command [params]\n"
      << " Quit\n\n";
   return true;
}

// run system/shell command
bool System(const string& cmd)
{
   system(cmd.c_str());
   return true;
}

// print string to output
bool Echo(const string& str)
{
   cout << str << endl;
   return true;
}

// quit program
bool Quit(const string&)
{
   exit(0);
   return false;
}

// minifunctions array
bool (* (g_miniFuncs[]) )(const string&) = { Help, System, Echo, Quit };

// "minifunction -> index" mapping
map<string, int> g_miniFuncIdx;

// start minifunctions mapping
void InitializeMiniFuncIdx()
{
   g_miniFuncIdx["Help"] = 0;
   g_miniFuncIdx["System"] = 1;
   g_miniFuncIdx["Echo"] = 2;
   g_miniFuncIdx["Quit"] = 3;
}

// last line read from input
string g_currentLine;

// how much time are we going to wait for the next line?
const DWORD g_waitTime = 1000;

// run minifunctions
DWORD FilterException()
{
   DWORD ret = EXCEPTION_CONTINUE_EXECUTION;

   if( ! g_currentLine.empty() )
   {
      istringstream line(g_currentLine);
      g_currentLine.clear();

      string function;
      string params;

      line >> function;

      getline(line, params);

      // 5. run some well-defined function by number
      if( ! g_miniFuncs[g_miniFuncIdx[function] ](params) )
         ret = EXCEPTION_CONTINUE_SEARCH;
   }

   return ret;
}

DWORD WINAPI AntiDebugThread(PVOID)
{
   InitializeMiniFuncIdx(); // start minifunction mapping

   // 2. ad aeternum (or almost)
   while( true )

   {
      //FilterException();

      __try // the extern try waits for an exit command
      {
         __try // the intern try stays generating exceptions continuously
         {
            __asm int 3
         }
         // FilterException is the function who runs minifunctions
         __except( FilterException() )
         {
				// we can put some fake code here
         }
      }
      __except( EXCEPTION_EXECUTE_HANDLER )
      {
         break; // get out from ad aeternum (to the limbo?)
      }

      Sleep(g_waitTime);
   }

   return ERROR_SUCCESS;
}

/** and God said: 'int main!'
*/
int main()
{

   DWORD ret = ERROR_SUCCESS;
   DWORD tid = 0;
   HANDLE antiDebugThr;

   // 1. we create the thread that is going to run the commands
   antiDebugThr = CreateThread(NULL, 0, AntiDebugThread, NULL, 0, &tid);;

   if( antiDebugThr )
   {
      // 3. for each item in the script (function numbers)
      while( cin )
      {
         cout << "Type something\n";

         // 4. tells the thread to run the function number N
         getline(cin, g_currentLine);

         if( WaitForSingleObject(antiDebugThr, g_waitTime * 2) != WAIT_TIMEOUT )
            break;
      }

      GetExitCodeThread(antiDebugThr, &ret);
      CloseHandle(antiDebugThr), antiDebugThr = NULL;
   }

   // 6. end of execution.
   return (int) ret;
} 

```

O **ponto forte** da proteção é que a pessoa precisa entender o que está acontecendo para tomar alguma atitude inteligente para solucionar o "problema". O **ponto fraco** é que após entendido o problema a solução torna-se fácil de visualizar. Tão fácil que eu nem pretendo citar aqui.

Futuramente veremos uma maneira de tornar as coisas mais legíveis e usáveis no dia-a-dia de um programador de _software_ de segurança.
