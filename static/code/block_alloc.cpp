#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

static const size_t MAX_BLOCKS = 1000;
static size_t next_free_block = 0;
void* blocks[MAX_BLOCKS] = {};

void* block_alloc(size_t bytes)
{
    if( next_free_block <= MAX_BLOCKS )
        return blocks[next_free_block++] = malloc(bytes);
    return nullptr;
}

void block_free(void* block)
{
    for( size_t i = 0; i < next_free_block; ++i )
    {
        if( blocks[i] == block )
        {
            free(blocks[i]);
            blocks[i] = blocks[next_free_block--];
            break;
        }
    }
}

int main()
{
    char* p = (char*) block_alloc(100);
    strcpy(p, "testing 1");
    printf("%s\n", p);
    block_free(p);
    assert(blocks[next_free_block] == nullptr);
    assert(next_free_block == 0);

    p = (char*) block_alloc(100);
    strcpy(p, "testing 2");
    p = (char*) block_alloc(100);
    strcpy(p, "testing 3");
    p = (char*) block_alloc(100);
    strcpy(p, "testing 4");
    block_free(p);
    p = (char*) block_alloc(100);
    strcpy(p, "testing 5");
    for( size_t i = 0; i < next_free_block; ++i )
        printf("%s\n", blocks[i]);
    assert(blocks[next_free_block] == nullptr);
    assert(next_free_block == 3);
}

