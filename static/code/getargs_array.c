/** Interpreta argumentos da linha de comando com suporte a arrays.

@author Wanderley Caloni <wanderley.caloni@intelitrader.com.br>
@date 2020-08
*/
#include <stdlib.h>
#include <string.h>

const char** GetArgArray(char* argv[], const char* arg)
{
	char** ret = NULL;
	size_t cur_off = 0;

	while (*++argv)
	{
		if (strcmp(*argv, arg) == 0)
		{
			if (*(argv + 1))
			{
				char* new_arg = *(argv + 1);
				ret = (char**)realloc(ret, (cur_off + 2) * sizeof(char*));
				ret[cur_off++] = new_arg;
				ret[cur_off] = NULL;
			}
		}
	}

	return (const char**)ret;
}

