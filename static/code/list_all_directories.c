#include <windows.h>
#include <stdio.h>

#define INITIAL_BUFFER (MAX_PATH * 5)

char *listAllDirectories(char *path) {
    WIN32_FIND_DATA data;
    size_t bufferSize = INITIAL_BUFFER;
    char *directories = (char*)calloc(1, bufferSize);
    char *buffer = directories;
    size_t offset = buffer - directories;
    HANDLE hFind = FindFirstFile(path, &data);
    if ( hFind != INVALID_HANDLE_VALUE ) {
        do {
            strcpy(buffer, data.cFileName);
            buffer += strlen(buffer) + 1;
            offset = buffer - directories;
            if( bufferSize - offset < MAX_PATH ) {
                char* newDirectories;
                bufferSize *= 2;
                newDirectories = (char*) realloc(directories, bufferSize);
                if(newDirectories == NULL) {
                    fprintf(stderr, "Falha na alocacao de memoria!\n");
                    free(directories);
                    return NULL;
                }
                directories = newDirectories;
                buffer = directories + offset;
            }

        } while (FindNextFile(hFind, &data));
        *buffer = '\0';
        FindClose(hFind);
    }
    return directories;
}

int main(int argc, char* argv[]) {
    if( argc == 2 ) {
        char* directories = listAllDirectories(argv[1]);
        if( directories != NULL ) {
            char* directory = directories;
            while( *directory ) {
                printf("%s\n", directory);
                directory += strlen(directory) + 1;
            }
            free(directories);
        }
    }
    else {
        printf("How to use: list_all_directories.exe <path_with_wildcards>\n");
        return 1;
    }
    return 0;
}

