#include "library.h"
#define SIZE (argc-1)

int main(int argc, char** argv)
{
    if (argc < 2)
        return 0;
    char** string = (char**)malloc((argc) * sizeof(char*));
    if (string == NULL)
        return 1;
    for (int i = 0; i < (argc); i++)
    {
        string[i] = (char*)calloc(1, sizeof(char));
    }
    for (int i = 1; i < argc; i++)
    {
        int j = 0;
        while (string[i][j] != '=')
        {
            if (string[i-1] == NULL)
            {
                return 1;
            }
            string[i-1][j] = argv[i][j];
            j++;
            if (j != 0)
            {
                char* storer;
                storer = (char*)realloc(string[i-1], (j + 1) * sizeof(char));
                if (string[i-1] != NULL)
                    string[i-1] = storer;

            }
        }
        if (string[i-1] == NULL)
        {
            return 1;
        }
        string[i-1][j+1] = '\0';
    }
    printf("\nArray:");
    printString(string, SIZE);
    insertionSort(string, SIZE);
    printf("\nResult:");
    printString(string, SIZE);
    free(string);
    return 0;
}