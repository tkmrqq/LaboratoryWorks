#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <wincon.h>

void errorOutput() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    printf("Wrong input! Please, try again \n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
}

void arrayFill(int N, int array[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            array[i][j] = rand() % 21 - 9;
        }
    }
}

void arrayPrint(int N, int array[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d ", array[i][j]);
        }
        printf("\n");
    }
}

void arrayInput(int N, int array[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            while (scanf_s("%d", &array[i][j]) != 1) /*|| getchar() != '\n' || array[i][j] > 10000 ||
                   array[i][j] < -10000)*/ {
                errorOutput();
                rewind(stdin);
            }
        }
    }
    printf("\nOriginal array:\n");
}

void choice(int x, int N, int array[N][N]) {
    printf("Are you want to input array or get random numbers in it?\n");
    printf("Pick 1) for input and 2) for random values\n");
    while (scanf_s("%d", &x) != 1 || x > 2 || x <= 0 || getchar() != '\n') {
        rewind(stdin);
        errorOutput();
    }
    if (x == 1) arrayInput(N, array);
    else if (x == 2) arrayFill(N, array);
}

void min_element(int N, int array[N][N]) {
    int min = 0, i = N - 1, j;
    for (i = 0; i < N / 2; i++)
        for (j = N - i - 1; j < N; j++)
            if (min > array[i][j])
                min = array[i][j];
    for (; i < N; i++)
        for (j = N - (N - i); j < N; j++)
            if (min > array[i][j])
                min = array[i][j];
    printf("The smallest element: %d\n", min);
}

int check(int x) {
    while (scanf_s("%d", &x) != 1 || x > 100 || x < 1 || getchar() != '\n') {
        errorOutput();
        rewind(stdin);
    }
    return x;
}

int main() {
    srand(time(0));
    int N = 0, x = 0, array[100][100];
    printf("Input matrix size (N):");
    N = check(N);
    choice(x, N, array);
    printf("Array:\n");
    arrayPrint(N, array);
    min_element(N, array);
}