/*
 * Process all permutations with duplicates allowed.
 */
#include "permutation.h"
#include <stdio.h> 
#include <string.h> 
#include <malloc.h> 


int word_size;
char** g_permutations;
int g_permutations_len;
int g_permutations_size;


/* Function to swap values at two pointers */
static void swap(char* x, char* y) 
{ 
	char temp; 
	temp = *x; 
	*x = *y; 
	*y = temp; 
} 


static void out_of_memory_abort(void* mem)
{
    if( ! mem )
    {
        printf("out of memory\n");
        abort();
    }
}


int insert_permutation(char* str)
{
    int i, str_sz = strlen(str) + 1;
    char* new_str;

    if( str_sz != word_size )
      return 1;

    if( g_permutations_len == g_permutations_size )
    {
        g_permutations_size = g_permutations_size ? g_permutations_size * 2 : 16;
        g_permutations = realloc(g_permutations, g_permutations_size * sizeof(char*));
        out_of_memory_abort(g_permutations);
    }

    for( i = 0; i < g_permutations_len; ++i )
    {
        if( strcmp(g_permutations[i], str) == 0 )
            return 1;
    }

    new_str = malloc(str_sz);
    out_of_memory_abort(new_str);
    strcpy(new_str, str);
    g_permutations[g_permutations_len++] = new_str;
    return 1;
}


/* Function to print permutations of string 

  This function takes four parameters: 

  1. String 
  2. Starting index of the string 
  3. Ending index of the string.
  4. Callback to call passing the permuted string.

  If callback returns 0 the permute function stops.
*/
void permute(char* a, int l, int r, permute_callback_t p) 
{ 
	int i; 

	if (l == r) 
    {
        int stop = p(a); 
        if( stop ) return;
    }
	else
    { 
		for (i = l; i <= r; i++) { 
			swap((a + l), (a + i)); 
			permute(a, l + 1, r, p); 
			swap((a + l), (a + i)); // backtrack 
		} 
	} 
} 


void permute_callback(char* a, permute_callback_t p)
{
    word_size = strlen(a) + 1;
    int l = 0, r = strlen(a) - 1;
    permute(a, l, r, p);
}


void permute_global(char* a)
{
    word_size = strlen(a) + 1;
    int l = 0, r = strlen(a) - 1;
    permute(a, l, r, insert_permutation);
}

