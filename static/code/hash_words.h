#include <limits.h> 

typedef struct
{
    char** items;
    size_t size;
    size_t len;

} string_array;

extern string_array g_words[UCHAR_MAX + 1];
extern int g_biggest_hash;
