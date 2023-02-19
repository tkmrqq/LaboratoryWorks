#include "library.h"
#include <stdio.h>

int length(char *str) {
    int i = 0, n;
    while (*(str + i) != '\0') {
        i++;
    }
    n = i;
    return n;
}

int sizeMaxWord(char *str) {
    int maxSizeWord = 0, sizeWord = 0, number_word = 0;
    for (int i = 0; i < length(str) + 1; i++) {
        if ((*(str + i) >= 'A' && *(str + i) <= 'Z') || (*(str + i) >= 'a' && *(str + i) <= 'z')) {
            int j = i;
            while (((*(str + j) >= 'A' && *(str + j) <= 'Z') || (*(str + j) >= 'a' && *(str + j) <= 'z'))) {
                sizeWord++;
                j++;
            }
            number_word++;
            if (number_word == 1)
                maxSizeWord = sizeWord;
            else {
                if (maxSizeWord < sizeWord) {
                    maxSizeWord = sizeWord;
                }
            }
            i = j + 1;
            sizeWord = 0;
        }
    }
    return maxSizeWord;
}

void printString(char **str, int size) {
    for (int i = 0; i < size; i++) {
        if (*(str + i) != NULL) {
            printf("%s", *(str + i));
            printf("\n");
        }
    }
}

void insertionSort(char **str, int size) {
    for (int i = 1; i < size; i++) {
        char *temp = str[i];
        int j = i - 1;
        while (j >= 0 && sizeMaxWord(temp)  > sizeMaxWord(str[j])) {
            str[j + 1] = str[j];
            j--;
        }
        str[j + 1] = temp;
    }
}
