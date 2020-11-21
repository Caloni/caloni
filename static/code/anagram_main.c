#include "permutation.h"
#include <stdio.h>
#include <malloc.h>

int main(int argc, char* argv[])
{
    if( argc == 2 )
    {
        char* src = argv[1], *dst = src;
        int i;

        while( *dst = *src++ )
        {
            if( isalpha(*dst) )
            {
                *dst = toupper(*dst);
                dst++;
            }
            else if( ! isspace(*dst) )
            {
                printf("error, invalid character: %c", *dst);
                abort();
            }
        }

        permute_global(argv[1]);

        for( i = 0; i < g_permutations_len; ++i )
        {
            printf("%s\n", g_permutations[i]);
        }
    }
}

