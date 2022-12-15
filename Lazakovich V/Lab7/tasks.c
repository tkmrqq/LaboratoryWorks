#include "library.h"

void task1() {
    int length, lengthOfWord;
    char *str, *word;
    printf("Input string:\n");
    str = inputString(&length);
    printf("Entered string: %s\n", str);
    printf("Input word:\n");
    word = inputWord(&lengthOfWord);
    printf("Entered word: %s\n", word);
    printf("%d", compare(word, str, length, lengthOfWord));
    free(str);
    free(word);
}

void task2() {
    int length, length0;
    char *str, *str0;
    printf("Input string:\n");
    str = inputString(&length);
    printf("Entered string: %s\n", str);
    printf("Input string:\n");
    str0 = inputString0(&length0);
    printf("Entered string: %s\n", str0);
    compareStrings(str0, str, length, length0);
    free(str);
    free(str0);
}

void task3() {
    printf("Program not ready yet :(\n");
 /*   int row;
    char **string;
    printf("Input amount of rows:");
    inputRow(&row);
    stringArrInput(&string, row);
    stringLength(string, row);
    insertionSort(string, row);
    printStringArray(string, row);
    clearMemory(string, row);*/
}

void stopProgram() {
    rewind(stdin);
    exit(EXIT_SUCCESS);
}