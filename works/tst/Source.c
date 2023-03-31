#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Определение структуры для хранения информации об автомобиле
struct Car {
    char make[20]; // марка
    char model[20]; // модель
    int year; // год выпуска
    enum { RED, BLUE, GREEN, BLACK, WHITE } color; // цвет
    float price; // стоимость
};


// Функция для создания массива структур
struct Car* createArray(int size) {
    struct Car* array = malloc(size * sizeof(struct Car));
    return array;
}

// Функция для вывода массива структур на экран
void printArray(struct Car* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s %s (%d) - ", array[i].make, array[i].model, array[i].year);
        switch (array[i].color) {
        case RED:
            printf("RED - ");
            break;
        case BLUE:
            printf("BLUE - ");
            break;
        case GREEN:
            printf("GREEN - ");
            break;
        case BLACK:
            printf("BLACK - ");
            break;
        case WHITE:
            printf("WHITE - ");
            break;
        default:
            printf("UNKNOWN COLOR - ");
            break;
        }
        printf("$%.2f\n", array[i].price);
    }
}

// Функция для инициализации экземпляра структуры
void initializeCar(struct Car* car) {
    printf("Enter make: ");
    scanf_s("%s", car->make);
    printf("Enter model: ");
    scanf_s("%s", car->model);
    printf("Enter year: ");
    scanf_s("%d", &car->year);
    printf("Enter color (0 - RED, 1 - BLUE, 2 - GREEN, 3 - BLACK, 4 - WHITE): ");
    scanf_s("%d", &car->color);
    printf("Enter price: ");
    scanf_s("%f", &car->price);
}

// Функция для сравнения автомобилей по марке
int compareByMake(struct Car a, struct Car b) {
    int cmp = strcmp(a.make, b.make);
    if (cmp == 0)
    {
        return strcmp(a.model, b.model);
    }
    return cmp;
}

int compareByModel(struct Car a, struct Car b) {
    int cmp = strcmp(a.model, b.model);
    if (cmp == 0)
    {
        return a.price - b.price;
    }
    return cmp;
}


int compareByColor(struct Car a, struct Car b)
{
    int cmp = a.color - b.color;
    if (cmp == 0)
    {
        return strcmp(a.model, b.model);
    }
    return cmp;
}

// Функция для сравнения автомобилей по году выпуска
int compareByYear(struct Car a, struct Car b) {
    int cmp = a.year - b.year;
    if (cmp == 0)
    {
        return strcmp(a.model, b.model);
    }
    return cmp;
}

// Функция для сравнения автомобилей по цене
int compareByPrice(struct Car a, struct Car b) {
    int cmp = a.price - b.price;
    if (cmp == 0)
    {
        return strcmp(a.make, b.make);
    }
    return cmp;
}



// Функция для удаления структуры из массива
void deleteCar(struct Car** Cars, int* n)
{
    int x;
    printf("Enter the number of the struct to delete:");
    scanf_s("%d", &x);
    if (x < 1 || x > *n) {
        printf("Invalid input\n");
        return;
    }
    for (int i = x - 1; i < *n - 1; i++)
    {
        (*Cars)[i] = (*Cars)[i + 1];
    }
    *n = *n - 1;
    struct Car* temp = (struct Car*)realloc(*Cars, *n * sizeof(struct Car));
    if (temp != NULL) {
        *Cars = temp;
    }
    else {
        printf("Error: memory allocation failed.\n");
        return;
    }
}

void sortStruct(struct Car* car, const int* size, int key)
{
    struct Car swap;
    int gap = *size / 2;
    while (gap > 0) {

        for (int i = 0, j = gap; j < *size; i++, j++) {
            int cmp = 0;
            if (key == 1) {
                cmp = compareByMake(car[i], car[j]);
            }
            else if (key == 2) {
                cmp = compareByYear(car[i], car[j]);
            }
            else if (key == 3) {
                cmp = compareByPrice(car[i], car[j]);
            }
            else if (key == 4) {
                cmp = compareByColor(car[i], car[j]);
            }

            if (cmp > 0) {
                swap = car[j];
                car[j] = car[i];
                car[i] = swap;
            }
        }

        gap /= 2;
    }
}

void outputStruct(struct Car* car, const int* n)
{
    for (int i = 0; i < *n; i++)
    {
        if (car[i].color >= 0 && car[i].color < 4) {
            printf("\tmake:%s\t model:%s\t year:%d\t color:%s\t price:%s\n", car[i].make, car[i].model, car[i].year, car[i].color, car[i].price);
        }
        else {
            printf("\tmake:%s\t model:%s\t year:%d\t color:%s\t price:%s\n", car[i].make, car[i].model, car[i].year);
        }
    }
}


int main() {
    int n;
    int x = 0;

//    int pn = &n;
    int key = scanf_s("%d", key);
    struct Car* car;
    car = (struct Car*)malloc(n * sizeof(struct Car));
    createArray(n);
    initializeCar(car);
    printf("1-output 2-add 3-sort 4-delete 5-exit");
    while (1)
    {
        switch (key)
        {
        case 1:
            outputStruct(car, &n);
            break;
        case 2:

            break;
        case 3:
            scanf_s("%d", x);
            sortStruct(car, &n, 1);
            break;
        case 4:

            break;
        case 5:
            printf("Exiting program\n");
            free(car);
            break;

        default:
            printf("Invalid input\n");
            break;
        }

    }
}