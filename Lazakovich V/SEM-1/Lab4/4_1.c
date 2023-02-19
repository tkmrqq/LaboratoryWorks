#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void errorOutput(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    printf("Wrong input! Please, try again \n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swapArray(int row, int column, int array[row][column], int j) {
    for (int k = 0; k < column; ++k) {
        int tmp = array[j][k];
        array[j][k] = array[j + 1][k];
        array[j + 1][k] = tmp;
    }
}

void arrayPrint(int row, int column, int array[row][column]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%4d ", array[i][j]);
        }
        printf("\n");
    }
}

void arrayFill(int row, int column, int array[row][column], int c[100]) {
    int sum;
    printf("Original array:\n");
    for (int i = 0; i < row; i++) {
        sum = 0;
        for (int j = 0; j < column; j++) {
            array[i][j] = rand() % 21 - 9;
            if (array[i][j] > 0 && array[i][j] % 2 == 0)
                sum += array[i][j];
            printf("%4d ", array[i][j]);
        }
        c[i] = sum;
        printf("\tSum = %d\n", sum);
    }
}

int arrayInput(int row, int column, int array[row][column], int c[100]) {
    int sum;
    for (int i = 0; i < row; i++) {
        sum = 0;
        for (int j = 0; j < column; j++) {
            while(scanf_s("%d", &array[i][j]) != 1 || getchar() != '\n' || array[i][j] > 10000 || array[i][j] < -10000) {
                errorOutput();
                rewind(stdin);
            }
            if (array[i][j] > 0 && array[i][j] % 2 == 0)
                sum += array[i][j];
        }
        printf("Sum%d = %d; ", i + 1, sum);
        c[i] = sum;
    }
    printf("\nOriginal array:\n");
    arrayPrint(row, column, array);
    return *c;
}

void choice(int x, int row, int column, int array[row][column], int c[100]) {
    srand(time(0));
    printf("Are you want to input array or get random numbers in it?\n");
    printf("Pick 1) for input and 2) for random values\n");
    while (scanf_s("%d", &x) != 1 || x > 2 || x <= 0 || getchar() != '\n') {
        rewind(stdin);
        errorOutput();
    }
    if (x == 1) arrayInput(row, column, array, c);
    else if (x == 2) arrayFill(row, column, array, c);
}

int check(int x) {
    while (scanf_s("%d", &x) != 1 || x > 100 || x < 1 || getchar() != '\n') {
        errorOutput();
        rewind(stdin);
    }
    return x;
}

int main() {
    int row=0, column=0, x = 0, array[100][100], c[100];
    printf("Input amount of rows:");
    row = check(row);
    printf("Input amount of columns:");
    column = check(column);
    choice(x, row, column, array, c);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row - 1; j++) {
            if (c[j] > c[j + 1]) {
                swap(&c[j], &c[j + 1]);
                swapArray(row, column, array, j);
            }
        }
    }
    printf("Final array:\n");
    arrayPrint(row, column, array);
}
