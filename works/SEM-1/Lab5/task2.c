#include <stdio.h>
#include <stdlib.h>

int **input(int *n) {
  int i, j;
  int **mas;
  mas = (int **)calloc(1, sizeof(int *));
  mas[0] = (int *)calloc(1, sizeof(int));
  i = 0;
  do{
    printf("Input %d line\n", i);
    printf("for stop press any not number\n");
    j = 0;
    while (scanf_s("%d", &mas[i][j]) && mas[i][j] != -1) {
      j++;
      mas[i] = (int *)realloc(mas[i], (j + 1) * sizeof(int));
    }
    i++;
    mas = (int **)realloc(mas, (i + 1) * sizeof(int *));
    mas[i] = (int *)calloc(1, sizeof(int));
    printf("Do you want to enter one more line? (y/n)\n");
    rewind(stdin);
  }
  while(getchar() != 'n');
  *n = i;
  return mas;
}

void output(int **mas, int *n) {
  for (int i = 0; i < *n; i++) {
    int j = 0;
    while (mas[i][j] != -1) {
      printf("%5d", mas[i][j]);
      j++;
    }
    printf("\n");
  }
}

void remElement(int **array, int *n) {
  int k;
  printf("delete");
  scanf_s("%d", &k);
  (*n) = k;
  *array = (int *)realloc(*array, (*n) * sizeof(int));
  if (!(*array))
    printf("No memory...\n");
}

int main() {
  int n = 0;
  int **mas = input(&n);
  output(mas, &n);
  remElement(mas, &n);
  output(mas, &n);
  return 0;
}
