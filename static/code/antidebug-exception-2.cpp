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
#include <setjmp.h>

using namespace std;

/** The only purpose of 
  this function is to 
  generate an exception. */
DWORD LongJmp(jmp_buf* stack_state)
{
  __try
  {
    __asm int 3
  }
  __except( EXCEPTION_EXECUTE_HANDLER )
  {
    longjmp(*stack_state, 1);
  }

  return ERROR_SUCCESS;
}

/** Use this macro instead LongJmp
*/
#define ANTIDEBUG(code)      \
{                            \
  jmp_buf env;               \
                             \
  if( setjmp(env) == 0 )     \
  {                          \
    LongJmp(&env);           \
  }                          \
  else                       \
  {                          \
    code;                    \
  }                          \
}


/** and God said: 'int main!'
*/
int main()
{

   DWORD ret = ERROR_SUCCESS;
   string line;

   while( cin )
   {
     cout << "Type something\n";
     getline(cin, line);

     jmp_buf stack_state;

     ANTIDEBUG(( cout << line << endl ));
   }

   return (int) ret;
} 

