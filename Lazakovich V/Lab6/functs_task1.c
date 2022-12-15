//#include "functs_task1.h"

void arrBadFill(int *arr, int size) {
    int j = -1;
    for (int i = 0; i < size; i++) {
        arr[i] = j;
        j--;
    }
}

void memoryOfBuff(int **arrForSort, int **arrCopy, int buffSize) {
    *arrForSort = (int *) calloc(buffSize, sizeof(int));
    *arrCopy = (int *) calloc(buffSize, sizeof(int));
}

void memory(int **arr, int size) {
    *arr = (int *) calloc(size, sizeof(int));
}

void arrDuplicate(const int *arrForSort, int *arrCopy, int buffSize) {
    for (int i = 0; i < buffSize; i++)
        arrCopy[i] = arrForSort[i];
}

void arrFill(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 21 - 10;
    }
}

void arrPrint(int *arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
}

int sizeOfBuff(int size, const int *arr) {
    int buffSize = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0)
            buffSize++;
    }
    return buffSize;
}

void arrIn(const int *arr, int *arrForSort, int size) {
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            arrForSort[j] = arr[i];
            j++;
        }
    }
}

void arrOut(int *arr, const int *arrForSort, int size) {
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            arr[i] = arrForSort[j];
            j++;
        }
    }
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubbleSort(int *arr, int size) {
    int i, j;
    for (i = 0; i < size - 1; i++) {
        if (arr[i] < 0) {
            for (j = 0; j < size - i - 1; j++)
                if (arr[j] > arr[j + 1])
                    swap(&arr[j], &arr[j + 1]);
        }
    }
}

void selectionSort(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] < 0) {
            int min_index = i;
            for (int j = i + 1; j < size; j++) {
                if (arr[j] < arr[min_index]) {
                    min_index = j;
                }
            }
            if (min_index != i) {
                swap(&arr[i], &arr[min_index]);
            }
        }
    }
}

void sortsTimeCount(int *arrForSort, int *arrCopy, int buffSize, double *timeSpentSelection, double *timeSpentBubble) {
    clock_t start = clock();
    selectionSort(arrForSort, buffSize);
    clock_t end = clock();
    *timeSpentSelection += (double) (end - start) / CLOCKS_PER_SEC;
    clock_t startB = clock();
    bubbleSort(arrCopy, buffSize);
    clock_t endB = clock();
    *timeSpentBubble += (double) (endB - startB) / CLOCKS_PER_SEC;
}

void clearMemory(int *arr) {
    free(arr);
}

void clearAllArrs(int *arr, int *arrForSort, int *arrCopy) {
    clearMemory(arr);
    clearMemory(arrForSort);
    clearMemory(arrCopy);
}

void choice(int *arr, int size){
    int x;
    printf("1)Random values\n2)Bad case\n");
    while (scanf_s("%d", &x) != 1 || getchar() != '\n' || x<1 || x>2) {
        printf("Error!");
        rewind(stdin);
    }
    if(x == 1)
        arrFill(arr, size);
    else if(x == 2)
        arrBadFill(arr, size);
}