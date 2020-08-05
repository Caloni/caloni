/** Interpreta argumentos da linha de comando (versão raiz).

@author Wanderley Caloni <wanderley.caloni@bitforge.com.br>
@date 2018-08

           ---      --- 
    argv: | * |--> | * | "testbin"
           ---      --- 
                    --- 
                   | * | "foo"
                    --- 
                    --- 
                   | * | "100"
                    --- 
            --- 
     argc: | 3 |
            --- 
    
*/
#include <stdlib.h>
#include <string.h>

const char* GetArg(int argc, char* argv[], const char* arg)
{
    for (int i = 1; i < argc; ++i)
    {
        if( strcmp(argv[i], arg) == 0 )
        {
            if( i < argc - 1 )
                return argv[i+1];
            else
                return "";
        }
    }
    return NULL;
}

