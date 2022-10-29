#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <wincon.h>

void errorOutput(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    printf("Wrong input! Please, try again \n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
}

void arrayPrint(int row, int column, double array[row][column]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%4.0lf ", array[i][j]);
        }
        printf("\n");
    }
}

void arrayFill(int row, int column, double array[row][column]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            array[i][j] = rand() % 10 - 1;
        }
    }
}

void arrayInput(int row, int column, double array[row][column]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            scanf_s("%lf", &array[i][j]);
        }
    }
}

void choice(int x, int row, int column, double array[row][column]) {
    srand(time(0));
    printf("Are you want to input array or get random numbers in it?\n");
    printf("Pick 1) for input and 2) for random values\n");
    while (scanf_s("%d", &x) != 1 || x > 2 || x <= 0 || getchar() != '\n') {
        rewind(stdin);
        errorOutput();
    }
    if (x == 1) arrayInput(row, column, array);
    else if (x == 2) arrayFill(row, column, array);
}

void prog(int row, int column, double array[row][column]) {
    int i, j, k, m;
    for (i = 0; i < row; i++)
        for (j = 0; j < column; j++) {
            if (array[i][j] < 0) {
                for (k = 0, m = i; k < column; k++) array[k][m] /= 2;
            }
        }


    for (i = 0; i < row; i++)
        for (j = 0; j < column; j++) {
            printf("%5.2lf ", array[i][j]);
            if (j == column - 1) printf("\n");
        }
}

int check(int x) {
    while (scanf_s("%d", &x) != 1 || x > 100 || x < 1 || getchar() != '\n') {
        errorOutput();
        rewind(stdin);
    }
    return x;
}

int main() {
    int row = 0, column = 0, x = 0;
    double array[100][100];
    printf("Input amount of rows:");
    row = check(row);
    printf("Input amount of columns:");
    column = check(column);
    choice(x, row, column, array);
    arrayPrint(row, column, array);
    printf("============[FinArray]============\n");
    prog(row, column, array);
}

//Проверить, есть ли в матрице хотя бы одна строка, содержащая отрицательный элемент, и найти ее номер.
// Все элементы столбца с таким же номером уменьшить вдвое.