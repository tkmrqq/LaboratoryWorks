#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int choice(int x) {
    printf("Are you want to input array or get random numbers in it?\n");
    printf("Pick 1) for input and 2) for random values\n");
    while (scanf_s("%d", &x) != 1 || x > 2 || x <= 0) {
        rewind(stdin);
        printf("Wrong input! Please, try again!\n");
    }
    return x;
}

void printArray(int row, int array1[], int array2[]) {
    printf("1st Num\n");
    for (row = 0; row < 30; row++)
        printf("%d", array1[row]);
    printf("\n");
    printf("2nd Num\n");
    for (row = 0; row < 30; row++)
        printf("%d", array2[row]);
    printf("\n");
}

int main() {
    int x = 0, row;
    int array1[100], array2[100], array3[100];
    srand(time(0));
    x = choice(x);
    switch (x) {
        case 1: {
            printf("Input first number:\n");
            for (row = 0; row < 30; row++)
            {
                while (scanf_s("%d", &array1[row]) != 1 || array1[row] < 0 || array1[row] > 10)
                {
                    rewind(stdin);
                    printf("Wrong input. Please, try again!\n");
                }
            }
            printf("Input second number:\n");
            for (row = 0; row < 30; row++)
            {
                while (scanf_s("%d", &array2[row]) != 1 || array2[row] < 0 || array2[row] > 10)
                {
                    rewind(stdin);
                    printf("Wrong input. Please, try again!\n");
                }
            }
            break;
        }
        case 2: {
            for (row = 0; row < 30; row++)
                array1[row] = rand() % 10;
            for (row = 0; row < 30; row++)
                array2[row] = rand() % 10;
            break;
        }
    }
    printArray(row, array1, array2);
    int a, b, c;
    b = array1[0];
    c = array2[0];
    if (b > c) {
        for (row = 30; row >= 0; row--) {
            if (array1[row] >= array2[row]) {
                a = array1[row] - array2[row];
                array3[row] = a;
            } else {
                a = array1[row] + 10 - array2[row];
                array3[row] = a;
                array1[row - 1] = array1[row - 1] - 1;
            }
        }
        printf("Result: \n");
        for (row = 0; row < 30; row++)
            printf("%d", array3[row]);
    } else {
        for (row = 30; row >= 0; row--) {
            if (array2[row] >= array1[row]) {
                a = array2[row] - array1[row];
                array3[row] = a;
            } else {
                a = array2[row] + 10 - array1[row];
                array3[row] = a;
                array2[row - 1] = array2[row - 1];
            }
        }
        printf("Result: \n");
        printf("-");
        for (row = 0; row < 30; row++)
            printf("%d", array3[row]);
    }
    return 0;
}
//2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
