#include "add.h"

void copy_arr(int argc, char **string, char **argv) {
    for (int i = 1; i < argc; i++)
    {
        int j = 0;
        while (string[i][j] != '=')
        {
            if (string[i - 1] == NULL)
            {
                return;
            }
            string[i - 1][j] = argv[i][j];
            j++;
            if (j != 0)
            {
                char* storer;
                storer = (char*)realloc(string[i - 1], (j + 1) * sizeof(char));
                if (string[i - 1] != NULL)
                    string[i - 1] = storer;

            }
        }
        if (string[i - 1] == NULL)
        {
            return;
        }
        string[i - 1][j + 1] = '\0';
    }
}

int str_length(char* str) {
    int i = 0, n;
    while (*(str + i) != '\0') {
        i++;
    }
    n = i;
    return n;
}

int size_min_word(char* str) {
    int min_word_size = 0, word_size = 0, number_word = 0;
    for (int i = 0; i < str_length(str) + 1; i++) {
        if ((*(str + i) >= 'A' && *(str + i) <= 'Z') || (*(str + i) >= 'a' && *(str + i) <= 'z')) {
            int j = i;
            while (((*(str + j) >= 'A' && *(str + j) <= 'Z') || (*(str + j) >= 'a' && *(str + j) <= 'z'))) {
                word_size++;
                j++;
            }
            number_word++;
            if (number_word == 1)
                min_word_size = word_size;
            else {
                if (min_word_size > word_size) {
                    min_word_size = word_size;
                }
            }
            i = j + 1;
            word_size = 0;
        }
    }
    return min_word_size;
}

void print_string(char** str, int size) {
    for (int i = 0; i < size; i++) {
        if (*(str + i) != NULL) {
            printf("%s", *(str + i));
            printf("\n");
        }
    }
}

void insertion_sort(char** str, int size) {
    for (int i = 1; i < size; i++) {
        char* temp = str[i];
        int j = i - 1;
        while (j >= 0 && size_min_word(temp) < size_min_word(str[j])) {
            str[j + 1] = str[j];
            j--;
        }
        str[j + 1] = temp;
    }
}

