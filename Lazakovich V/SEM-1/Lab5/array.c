#include "windows.h"
#include <malloc.h>
#include <stdio.h>
#include <time.h>

void process(int *array, int arraySize) {
  int tmp[arraySize], sq;
  for (int i = 0; i < arraySize; i++) {
    tmp[i] = array[i];
  }

  for (int i = 0; i < arraySize; i++) {
    sq = (tmp[i] * tmp[i]);
    array[i + 1 + i] = sq;
    array[i + 2 + i] = tmp[i + 1];
  }
}

void arrayPrint(int *array, int newArraySize) {
  for (int i = 0; i < newArraySize; i++) {
    if (i % 2 == 0) {
      printf("%d ", array[i]);
    } else {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                              FOREGROUND_GREEN);
      printf("%d ", array[i]);
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                              FOREGROUND_BLUE | FOREGROUND_RED |
                                  FOREGROUND_GREEN);
    }
  }
}

void arrayInput(int *array, int arraySize) {
  for (int i = 0; i < arraySize; i++) {
    scanf_s("%d", &array[i]);
  }
}

void arrayFill(int *array, int arraySize) {
  srand(time(0));
  for (int i = 0; i < arraySize; i++) {
    array[i] = rand() % 21 - 9;
  }
}

void choice(int *array, int arraySize) {
  printf("Input (1) to enter an array or (2) to fill an array\n");
  int x;
  while (scanf_s("%d", &x) != 1 || x > 2 || x <= 0 || getchar() != '\n') {
    rewind(stdin);
    printf("Error! Try again\n");
  }
  if (x == 1)
    arrayInput(array, arraySize);
  else if (x == 2)
    arrayFill(array, arraySize);
}

int *memory(int arraySize) {
  int *array;
  array = (int *)calloc(arraySize, sizeof(int));
  if (array == NULL) {
    printf("Memory allocation failed.");
    exit(1);
  }
  return array;
}

int *newSize(int *array, int newArraySize) {
  array = (int *)realloc(array, newArraySize * sizeof(int));
  return array;
}
int check(int n) {
  while (scanf_s("%d", &n) != 1 || getchar() != '\n' || n <= 0) {
    printf("Try again\n");
    rewind(stdin);
  }
  return n;
}

int size(int arraySize) {
  printf("Input size of array:");
  arraySize = check(arraySize);
  return arraySize;
}
