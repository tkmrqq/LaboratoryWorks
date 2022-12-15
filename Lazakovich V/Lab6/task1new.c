#include <malloc.h>
#include <stdio.h>
#include <time.h>
#include "functs_task1.h"

int main() {
    srand(time(0));
    int *arr, *arrForSort, *arrCopy, size, buffSize;
    double timeSpentSelection = 0.0, timeSpentBubble = 0.0;
    printf("Input size of array:");
    scanf_s("%d", &size);
    memory(&arr, size);
    choice(arr, size);
    printf("Original arr:\n");
//    arrPrint(arr, size);
    buffSize = sizeOfBuff(size, arr);
    memoryOfBuff(&arrForSort, &arrCopy, buffSize);
    arrIn(arr, arrForSort, size);
    arrDuplicate(arrForSort, arrCopy, buffSize);
    sortsTimeCount(arrForSort, arrCopy, buffSize, &timeSpentSelection, &timeSpentBubble);
    arrOut(arr, arrForSort, size);
/*    printf("Arr for sort:\n");
    arrayPrint(arrForSort, buffSize);*/
    printf("\nSorted array:\n");
//    arrPrint(arr, size);
    printf("\nTime spent for selection sort = %f", timeSpentSelection);
    printf("\nTime spent for bubble sort = %f", timeSpentBubble);
    clearAllArrs(arr, arrForSort, arrCopy);
    return 0;
}