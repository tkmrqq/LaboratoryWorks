#include <stdio.h>
#include "functs_task2.h"

int main() {
    int N = 0, M = 0, x = 0;
    int **array;
    printf("Input amount of rows:");
    N = check(N);
    printf("Input amount of columns:");
    M = check(M);
    M += 1;
    array = memory(N, M);
    choice(x, N, M, array);
    printf("Original array:\n");
    arrayPrint(N, M, array);
    sortShell(array, N, M);
    printf("\nFinal array:\n");
    arrayPrint(N, M, array);
    clearMemory(array, N);
    printf("\nPress Enter to finish!");
    getchar();
}