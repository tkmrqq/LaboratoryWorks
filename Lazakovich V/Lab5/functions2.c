#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int **memory(int n, int m) {
  int **arr;
  arr = (int **)calloc(n, sizeof(int *));
  for (int i = 0; i < n; i++) {
    arr[i] = (int *)calloc(m, sizeof(int));
  }
  if (arr == NULL) {
    printf("Memory allocation failed.");
    exit(1);
  }
  return arr;
}

void input(int **array, int n, int *m) {
  printf("Input elements. Enter -1 for new row\n");
  for (int i = 0; i < n; i++) {
    printf("Input %d row\n", i + 1);
    for (int j = 0; j < (*m); j++) {
      while (scanf_s("%d", &array[i][j]) != 1) {
        printf("Error,try again");
        rewind(stdin);
      }
      if (array[i][j] == -1)
        break;
      if (array[i][j] != -1) {
        (*m)++;
        array[i] = (int *)realloc(array[i], (*m) * sizeof(int));
      }
    }
    //    *m = 1;
  }
}

void input_rows(int *n) {
  int rows;
  printf("Input number of rows =");
  while (scanf_s("%d", &rows) != 1 || getchar() != '\n') {
    printf("try again");
    rewind(stdin);
  }
  *n = rows;
}
void output(int **array, int n, int *m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (*m); j++) {
      if (array[i][j] == -1) {
        printf("\n");
        break;
      } else {
        printf("%3d ", array[i][j]);
//                (*m)++;
      }
//      printf("\n");
    }
    printf("\n");
  }
//  printf("\n");
}

void remElement(int **array, int n, int *m) {
  int k;
  printf("After which element delete? K = ");
  scanf_s("%d", &k);
  (*m) = k;
  *array = (int *)realloc(*array, (*m) * sizeof(int));
  if (!(*array))
    printf("No memory...\n");
  printf("New array\n");
//  output(array, n, m);
}

void clearMemory(int **array, int n) {
  for (int i = 0; i < n; i++) {
    free(array[i]);
  }
  free(array);
}
