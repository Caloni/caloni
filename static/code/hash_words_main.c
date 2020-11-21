#include "hash_words.h"
#include <stdio.h> 
#include <limits.h> 

/* Driver program to test above functions */
int main(int argc, char* argv[]) 
{
    if( argc == 2 )
    {
        FILE* f = fopen(argv[1], "r");

        if( f )
        {
            char line[200];
            int i, j;

            while( fgets(line, 200, f) )
            {
                line[strcspn(line, "\r\n")] = 0;
                insert_word(line);
            }

            printf("const char* g_words[%d][%d] = {\n", UCHAR_MAX + 1, g_biggest_hash);
            for( i = 0; i < UCHAR_MAX + 1; ++i )
            {
                string_array* item = &g_words[i];
                printf("  { /* %d */\n", i);
                for( j = 0; j < item->len; ++j )
                {
                    printf("    \"%s\", /* %d of %d */\n", item->items[j], j, (int) item->len);
                }
                printf("  },\n");
            }
            printf("};\n");

            fclose(f);
        }
    }
} 

