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
