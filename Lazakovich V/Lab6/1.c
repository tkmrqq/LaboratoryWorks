#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>


int array_size(int size_array) {
    printf("Input size of array:");
    while (scanf_s("%d", &size_array) == 0 || size_array < 1 || getchar() != '\n') {
        printf("\nYou need to write a right numbers\n");
        rewind(stdin);
    }
    return size_array;
}

void memory(int **array, int size_array) {
    *array = (int *) malloc(size_array * sizeof(int));
}
int choice_rand_manually(int choice) {
    printf("\n0 - manually input, 1 - random input:\n");
    while (scanf_s("%d", &choice) == 0 || choice < 0 || choice > 1 || getchar() != '\n') {
        printf("\nTry again pls))\n( 0 or 1 )");
        rewind(stdin);
    }
    return choice;
}
void array_input(int *array, int size_array) {
    for (int i = 0; i < size_array; i++) {
        printf("Enter a %d element: ", i + 1);
        while (scanf_s("%d", &array[i]) != 0 || getchar() != ' ') {
            printf("\nTry again pls))\n");
            rewind(stdin);
        }
    }
}
void array_input_random(int *array, int size_array) {
    for (int i = 0; i < size_array; i++)
        array[i] = rand() % 10;
}
void final_output(int *array, int size_array) {
    int choice = 0;
    choice = choice_rand_manually(choice);
    if (choice == 0)
        array_input(array, size_array);
    else
        array_input_random(array, size_array);
}
void print_array(int *array, int size_array) {
    for (int i = 0; i < size_array; i++)
        printf("%d ", array[i]);
    printf("\n ");
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void selectionSort(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] < 0) {
            int min_index = i;
            for (int j = i + 1; j < size; j++) {
                if (arr[j] < arr[min_index]) {
                    min_index = j;
                }
            }
            if (min_index != i) {
                swap(&arr[i], &arr[min_index]);
            }
        }
    }
}

int col_need_elem(int *array, int size_array, int col_elem) {
    for (int i = 0; i < size_array; i++) {
        if (array[i] < 0) {
            col_elem++;
        }
    }
    return col_elem;
}
void cop_array(int *array, int *copy_array, int size_array) {
    int j = 0;
    for (int i = 0; i < size_array; i++) {
        if (array[i] < 0) {
            copy_array[j] = array[i];
            j++;
        }
    }
}
void return_elem(int *array, int *copy_array, int size_array) {
    int j = 0;
    for (int i = 0; i < size_array; i++) {
        if (array[i] < 0) {
            array[i] = copy_array[j];
            j++;
        }
    }
}

int main() {
    int size = 0, *array, *copy_array = NULL;
    size = array_size(size);
    memory(&array, size);
    final_output(array, size);
    print_array(array, size);
    int col_elem = col_need_elem(array, size, col_elem);
    cop_array(array, copy_array, size);
    selectionSort(array, size);
    return_elem(array, copy_array, size);
    printf("\nFinal array:\n");
    print_array(array, size);
}
