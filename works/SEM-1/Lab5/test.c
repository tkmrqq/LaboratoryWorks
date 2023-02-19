#include <stdio.h>
#include <stdlib.h>

void input(int **arr, int *mas_size, int n) {
  int a;
  for (int i = 0; i < n; i++) {
    arr[i] = (int *)malloc(sizeof(int));
    int j = 0;
    do {
      printf("Input element %i rows\n", i + 1);
      while (scanf_s("%i", &a) != 1 || a < 0 || getchar() != '\n') {
        printf("Please input valid data!\n");
      }
      if (a == -1) {
        mas_size[i] = j;
        break;
      }
      arr[i][j] = a;
      j++;
      arr[i] = (int *)realloc(arr[i], sizeof(int) + sizeof(int) * j);
    } while (1);
  }
}

int **memory(int n, int m) {
  int **arr;
  m = 1;
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
        printf("%4d", array[i][j]);
        (*m)++;
      }
    }
  }
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
  output(array, n, m);
}

int main() {
  int **array, n, m;
  input_rows(&n);
  array = memory(n, m);
  input(array, n, m);
  output(array, n, &m);
  remElement(array, n, &m);
  free(array);
  return 0;
}
