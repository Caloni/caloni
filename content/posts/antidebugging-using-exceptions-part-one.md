---
categories:
- draft
- code
date: '2008-07-28'
title: Antidebugging using exceptions (part one)
---

A debugger puts breakpoints to stop for a moment the debuggee execution. In order to do this it makes use of a well known instruction: **int 3**. This instruction throws an exception - the breakpoint exception - that is caught by the operating system and bypassed to the handling code for this exception. For debuggee processes this code is inside the debugger. For free processes this code normally doesn't exist and the application simply crashs.

The main idea in this protection is to take care these exceptions during the application execution. Doing this, we can make use of this fact and, in the handling code, **run the protected code**. The solution here looks like a **script interpreter**. It consists basically of two threads: The first one read an instructions sequence and tells the second thread to **run it step to step**. In order to do this the second thread uses a **small functions** set with well defined code blocks. Here's the example in pseudocode:

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

The protection isn't there yet. But it will as intrinsic part of the execution thread. All we need to do is to add a exception handling and to throw lots of int 3. The thrown exceptions are caught by a second function that runs the instruction before to returning:

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

The execution thread algorithm is the same. Just the point where each instruction is executed depends to the exception throw system. Note that this exception has to be thrown in order to the next instruction run. This is fundamental, since this way nobody can just rip of the int 3 code to avoid the exception. If one does that, so no instruction will be executed at all.

In practice, if one tries to debug such a program one will have to deal with tons of exceptions until find out what's happening. Of course, as in every software protection, is's not definitive; it has as a purpose to **make hard** the reverse engineering understanding. That's not going to stop those who are [really good](http://www.codebreakers-journal.com/) doing that stuff.

**Nothing is for free**

The price paid for this protection stays on the source code visibility and understanding, compromised by the use of this technique. The programming is state machine based, and the functions are limited to some kind of behavior standard. So much smaller the code blocks inside the minifunctions, so much hard the code understanding will be.

The example bellow receives input through a command prompt and maps the first word typed to the function that must be called. The rest of the typed line is passed as arguments to the functions. The interpreter thread reads the user input and writes into a global string variable, at the same time the executor thread waits the string to be completed to starts the action. It was used the variable pool to let the code simpler, but the ideal would be some kind of synchronise, just like [events](http://msdn.microsoft.com/library/en-us/dllproc/base/createevent.asp), by example. You can download the source code [here](/images/antidebug.cpp).

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

The **strength** in this protection is to confound the attacker easily in the first steps (days, months...). Its **weakness** is the simplicity for the solution, since the attacker eventually realize what is going on. It is so easy that I will let it as an exercise for my readers.

In the next part we will se an alternative to make the code clearer and easy to use in the every day by a security software developer.