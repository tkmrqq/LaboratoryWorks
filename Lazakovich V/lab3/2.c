#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int choice(int x) {
    printf("Are you want to input array or get random numbers in it?\n");
    printf("Pick 1) for input and 2) for random values\n");
    while (scanf_s("%d", &x) != 1 || x > 2 || x <= 0) {
        rewind(stdin);
        printf("Wrong input\n");
        printf("Try again! ^_____^\n");
    }
    return x;
}

int check(int x) {
    printf("Input size of array = ");
    while (scanf_s("%d", &x) != 1 || x > 100 || x < 1) {
        printf("Error input! Please, try again \n");
        rewind(stdin);
    }
    return x;
}

void fillArray(int x, int arraySize, int *array) {
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
}

int main() {
    int k = 0, arraySize, pos = 0, x = 0;
    srand(time(0));
    int newArray[100], array[100];
    arraySize = check(x);
    fillArray(x, arraySize, array);
    printf("\nInput k elements to remove: \n");
    scanf_s("%d", &k);
    for (int i = 0; i < arraySize; i++) {
        if ((i+1) % k == 0)                             //если итый элемент массива делится на катый без остатка(равен ему) скипаем итерацию
            continue;
        else {
            newArray[pos] = array[i];               //иначе к новому массиву прибавляем подходящий элемент
            pos++;
        }
    }
    for (int i = 0; i < pos; i++) {
        printf("%d ", newArray[i]);
    }
}
