#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int absA(int i) {
    if (i < 0) i = -i;
    return i;
}

int check(int x) {
    while (scanf_s("%d", &x) != 1 || x > 100 || x < 1) {
        printf("Error input! Please, try again \n");
        rewind(stdin);
    }
    return x;
}

int choice(int x) {
    printf("Are you want to input array or get random numbers in it?\n");
    printf("Pick 1) for input and 2) for random values\n");
    while (scanf_s("%d", &x) != 1 || x > 2 || x <= 0) {
        rewind(stdin);
        printf("Wrong input\n");
        printf("Try again! ^)");
    }
    return x;
}

int main() {
    int firstPositive = 0, arraySize, sum = 0, x = 0;
    srand(time(0));
    printf("Input size of array:");
    arraySize = check(x);
    int array[100];
    int l = choice(x);
    if (l == 1) {
        for (int i = 0; i < arraySize; i++) {
            printf("Element %d =", i + 1);
            scanf_s("%d", &array[i]);
        }
    } else if (l == 2) {
        printf("Generated array:\n");
        for (int i = 0; i < arraySize; i++) {
            array[i] = rand() % 201 - 100;
            printf("%d ", array[i]);
        }
    }
    int MaxNumber = array[0];
    for (int i = 0; i < arraySize; i++) {
        if (absA(array[i]) > absA(MaxNumber))
            MaxNumber = array[i];
    }

    for (int j = 0; j < arraySize; j++) {
        if (array[j] > 0) {             //если элемент положит. стопаем цикл
            firstPositive = j;
            break;
        }
    }

    sum -= array[firstPositive];        //вычитаем первый положительный элемент
    for (; firstPositive < arraySize; firstPositive++) {
        sum += array[firstPositive];
    }

    printf("\nThe greatest number: %d\n", MaxNumber);
    printf("Sum of elements: %d\n", sum);
    return 0;
}
