#include <stdlib.h>
#include <time.h>

#define RESET "\033[0m"
#define GREEN "\033[1;32m"
/*#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37m"*/

int **memory(int n, int m) {
    int **array;
    array = (int **) calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++) {
        if (array)
            array[i] = (int *) calloc(m, sizeof(int));
    }
    return array;
}

void sortShell(int **array, int N, int M) {
    int tmp;
    for (int gap = M / 2; gap > 0; gap /= 2) {
        int fl;
        do {
            fl = 0;
            for (int i = gap, j = 0; i < N; i++, j++) {
                //                int tmp = array[0][j];
                for (int k = 0; k < M; k++)
                    if (array[i][M - 1] > array[j][M - 1]) {
                        tmp = array[j][k];
                        array[j][k] = array[i][k];
                        array[i][k] = tmp;
                        fl = 1;
                    }
            }
        } while (fl);
    }
}


void arrayPrint(int N, int M, int **array) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (j == M - 1)
                printf("%s%4d%s", GREEN, array[i][j], RESET);
            else
                printf("%4d ", array[i][j]);
        }
        printf("\n");
    }
}

void arrayFill(int N, int M, int **array) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M - 1; j++) {
            array[i][j] = rand() % 21 - 9;
            if (j % 2 != 0) {
                array[i][M - 1] += array[i][j];
            }
        }
    }
}

void arrayInput(int N, int M, int **array) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M - 1; j++) {
            while (scanf_s("%d", &array[i][j]) != 1 || getchar() != '\n' || array[i][j] > 10000 || array[i][j] < -10000) {
                printf("Error!");
                rewind(stdin);
            }
            if (j % 2 != 0)
                array[i][M - 1] += array[i][j];
        }
    }
}

void choice(int x, int N, int M, int **array) {
    srand(time(0));
    printf("Are you want to input array or get random numbers in it?\n");
    printf("Pick 1) for input and 2) for random values\n");
    while (scanf_s("%d", &x) != 1 || x > 2 || x <= 0 || getchar() != '\n') {
        rewind(stdin);
        printf("Error!");
    }
    if (x == 1) arrayInput(N, M, array);
    else if (x == 2)
        arrayFill(N, M, array);
}

int check(int x) {
    while (scanf_s("%d", &x) != 1 || x > 1000 || x < 1 || getchar() != '\n') {
        printf("Error!");
        rewind(stdin);
    }
    return x;
}

void clearMemory(int **array, int N) {
    for (int i = 0; i < N; i++) {
        free(array[i]);
    }
    free(array);
}
