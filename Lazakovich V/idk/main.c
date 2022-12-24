#include "add.h"
#define SIZE (argc-1)

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Error!");
        return 0;
    }
    char** string = (char**)malloc((argc) * sizeof(char*));
    for (int i = 0; i < (argc); i++)
    {
        string[i] = (char*)calloc(1, sizeof(char));
    }
    copy_arr(argc, string, argv);
    printf("\nArray:");
    print_string(string, SIZE);
    insertion_sort(string, SIZE);
    printf("\nResult:");
    print_string(string, SIZE);
    free(string);
    return 0;
}