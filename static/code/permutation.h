
int word_size;
extern char** g_permutations;
extern int g_permutations_len;

typedef int (*permute_callback_t)(char* str);

void permute_global(char* a);

void permute_callback(char* a, permute_callback_t p);

