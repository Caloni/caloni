/*
 * Get a word list and mount a hash table. 
 */
#include "hash_words.h"
#include <malloc.h> 
#include <math.h>
#include <stdio.h> 
#include <string.h> 

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

string_array g_words[UCHAR_MAX + 1];
int g_biggest_hash = 0;


static void out_of_memory_abort(void* mem)
{
    if( ! mem )
    {
        printf("out of memory\n");
        abort();
    }
}


/* Function return a hash from string. */
unsigned char hash(const char* str) 
{ 
    unsigned char ret = 0;
    while( *str )
    {
        ret += *str++;
    }
    return ret;
} 


void insert_word(const char* word)
{
    unsigned char h = hash(word);
    string_array* item = &g_words[h];
    size_t word_sz = strlen(word) + 1;
    char* new_word;

    if( ! item->items || item->size == item->len )
    {
        size_t size = item->items ? item->size * 2 : 16;
        item->items = (char**) realloc(item->items, size * sizeof(char**));
        out_of_memory_abort(item->items);
        item->size = size;
    }

    new_word = (char*) malloc(word_sz);
    out_of_memory_abort(new_word);
    strcpy(new_word, word);
    item->items[item->len++] = new_word;
    g_biggest_hash = MAX(g_biggest_hash, item->len);
}


