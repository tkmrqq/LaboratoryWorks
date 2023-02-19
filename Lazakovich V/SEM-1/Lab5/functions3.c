#include <stdio.h>
#include <stdlib.h>

int **memory(int n, int m) {
  int **arr;
  arr = (int **)calloc(n, sizeof(int *));
  for (int i = 0; i < n; i++) {
    if (arr)
      arr[i] = (int *)calloc(m, sizeof(int));
  }
  return arr;
}

int check(int n) {
  while (scanf_s("%d", &n) != 1 || getchar() != '\n' || n < 0) {
    printf("Try again\n");
    rewind(stdin);
  }
  return n;
}

void size(int *n, int *m) {
  printf("Input number of  line\n");
  *n = check(*n);
  printf("Input number of  columns\n");
  *m = check(*m);
}

void fillArray(int **arr, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("Input the number[%d][%d]\n", i + 1, j + 1);
      while (scanf_s("%d", &arr[i][j]) != 1 || getchar() != '\n') {
        printf("Input the number\n");
        rewind(stdin);
      }
    }
  }
}

void printArray(int **arr, int n, int m) {
  printf("arr : \n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      printf("%2d  ", arr[i][j]);
    printf("\n");
  }
}

void clearMemory(int **arr, int n) {
  for (int i = 0; i < n; i++) {
    free(arr[i]);
  }
  free(arr);
}

void deleteColumns(int **arr, int n, int m) {
  int all_sum = 0, orgnlM=m;
  for (int i = 0; i < m; i++) {
    int count = 0;
    for (int j = 0; j < n; j++) {
      if (arr[j][i] < 0) {
        count++;
        all_sum++;
      }
      if (count == n) {
        for (int x = 0; x < n; x++) {
          for (int c = i; c < m - 1; c++)
            arr[x][c] = arr[x][c + 1];
        }
        m--;
        arr[i] = (int *)realloc(arr[i], (m) * sizeof(int *));
      }

    }
    if (all_sum == n + orgnlM) {
      return;
    }
  }
  printArray(arr, n, m);
}

