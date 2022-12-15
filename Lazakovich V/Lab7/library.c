#include <malloc.h>
#include <stdio.h>

int ifLetter(char str) {
    if ((str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'Z'))
        return 1;
    return 0;
}

char *inputString(int *length) {
    int num = 256, pos = 0;
    char *str = (char *) calloc(num, sizeof(char));
    char ch;
    while (1) {
        ch = getchar();
        if (ch == '\n') {
            str[pos] = '\0';
            str = (char *) realloc(str, (pos + 1) * sizeof(char));
            return str;
        }

        str[pos] = ch;
        pos++;
        *length = pos;
        if (pos == 256)
            str = (char *) realloc(str, (pos + 1) * sizeof(char));
    }
}

char *inputString0(int *length) {
    int num = 256, pos = 0;
    char *str0 = (char *) calloc(num, sizeof(char));
    char ch;
    while (1) {
        ch = getchar();
        if (ch == '\n') {
            str0[pos] = '\0';
            str0 = (char *) realloc(str0, (pos + 1) * sizeof(char));
            return str0;
        }

        str0[pos] = ch;
        pos++;
        *length = pos;
        if (pos == 256)
            str0 = (char *) realloc(str0, (pos + 1) * sizeof(char));
    }
}

char *inputWord(int *lengthOfWord) {
    int num = 256;
    char *word = (char *) calloc(num, sizeof(char));
    char ch;
    int pos = 0;
    while (1) {
        ch = getchar();
        if (ch == '\n' || ch == ' ') {
            word[pos] = '\0';
            word = (char *) realloc(word, (pos + 1) * sizeof(char));
            return word;
        }

        word[pos] = ch;
        pos++;
        *lengthOfWord = pos;
        if (pos == 256)
            word = (char *) realloc(word, (pos + 1) * sizeof(char));
    }
}

int compare(char *word, char *str, int length, int lengthOfWord) {
    int fl = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < lengthOfWord; j++) {
            if (str[i + j] == word[j]) {
                if (j == lengthOfWord - 1) {
                    fl += 1;
                }
                if (str[i + j + 1] != '\0' && str[i + j + 1] != ' ' && str[i + j + 1] != ';' && str[i + j + 1] != '\t' && j == lengthOfWord - 1)
                    fl -= 1;
            } else
                break;
        }
    }
    return fl;
}

void compareStrings(char *word, char *str, int length, int lengthOfWord) {
    int fl = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < lengthOfWord; j++) {
            if (str[i + j] == word[j]) {
                if (j == lengthOfWord - 1) {
                    fl += 1;
                }
            } else
                break;
        }
        if (fl == 1) {
            printf("True");
            return;
        }
    }
    printf("False");
}

void inputRow(int *row) {
    while (!scanf_s("%d", row) || getchar() != '\n' || *row < 2) {
        printf("Error!\n");
        rewind(stdin);
    }
}

void stringArrInput(char ***string, int row) {
    *string = (char **) calloc(row, sizeof(char *));
    for (int i = 0; i < row; i++) {
        printf("Input %d row: \n", i + 1);
        int pos = 0;
        (*string)[i] = (char *) calloc(1, sizeof(char));
        char ch;
        while (1) {
            ch = getchar();
            if (ch == '\n') {
                (*string)[i][pos] = '\0';
                break;
            }
            (*string)[i][pos++] = ch;
            if (pos >= 1)
                (*string)[i] = (char *) realloc((*string)[i], (pos + 1) * 1);
        }
    }
}

int maxLength(char ***string, int i, int *wordNums) {
    int cnt = 0, tmp2 = 0, max = 0, k = 0;
    while ((*string)[i][k] != '\0') {
        if ((k == 0 && ifLetter((*string)[i][k] == 1)) || (ifLetter((*string)[i][k - 1]) == 0 && ifLetter((*string)[i][k]) == 1)) {

            while (ifLetter((*string)[i][k++]) != 0)
                cnt++;
            tmp2++;
            if (max < cnt) {
                *wordNums = tmp2;
                max = cnt;
            }
            cnt = 0;
        } else
            k++;
    }
    return max;
}

void stringLength(char **string, int row) {
    int max, wordNums;
    for (int i = 0; i < row; i++) {
        max = maxLength(&string, i, &wordNums);
        printf("In %d row max length %d of word nad this word number %d\n", i + 1, max, wordNums);
    }
}

void insertionSort(char **string, int row) {
    int pos;
    char *tmp, *newElement;
    int first = 0, last = row - 1;
    for (int j = 1; j < row; j++) {
        tmp = string[last];
        newElement = string[first];
        pos = j - 1;
        while (pos >= 0 && string[pos][first] < newElement) {
            string[pos + 1] = string[pos];
            pos--;
        }
        string[pos + 1] = tmp;
        string[pos + 1][first] = *newElement;
    }
}

void printStringArray(char **string, int row) {
    for (int i = 0; i < row; i++) {
        printf("[%d]: %s\n", i + 1, string[i]);
    }
}

void getIntForTask(int *task) {
    printf("\n");
    while (!scanf_s("%d", task) || *task > 4 || *task < 1 || getchar() != '\n') {
        printf_s("Error input!\n");
        rewind(stdin);
    }
}

void menu() {
    printf("\nTo choose task enter:\n1)Task 1\n2)Task 2\n3)Task 3 (8 lab)\n4)For stop program");
}

void clearMemory(char **string, int row) {
    for (int i = 0; i < row; i++)
        free(string[i]);
    free(string);
}
