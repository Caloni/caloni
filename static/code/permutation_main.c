#include "permutation.h"
#include <stdio.h>
#include <malloc.h>

int main(int argc, char* argv[])
{
    if( argc == 2 )
    {
        int i;
        char* str = argv[1];

        permute(str, insert_permutation);

        for( i = 0; i < g_permutations_len; ++i )
        {
            printf("%s\n", g_permutations[i]);
        }
    }
}

