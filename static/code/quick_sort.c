#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int cmpstr(void const *a, void const *b)
{
    const char const *aa = *(const char const **)a;
    const char const *bb = *(const char const **)b;
    return strcmp(aa, bb);
}


int main()
{
    char *names[] = {
        "Liam", "Olivia", "Noah", "Emma",
        "Oliver", "Ava", "William", "Sophia",
        "Elijah", "Isabella", "James", "Charlotte",
        "Benjamin", "Amelia", "Lucas", "Mia",
        "Mason", "Harper", "Ethan", "Evelyn",
    };
    size_t names_len = sizeof(names) / sizeof(char*);
    int i;

    qsort(names, names_len, sizeof(char*), cmpstr);

    for( i = 0; i < names_len; ++i )
    {
        printf("%s\n", names[i]);
    }
}
