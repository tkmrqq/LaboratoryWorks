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

void getIntForTask(int *task) {
    printf("\n");
    while (!scanf_s("%d", task) || *task > 3 || *task < 1 || getchar() != '\n') {
        printf_s("Error input!\n");
        rewind(stdin);
    }
}

void menu() {
    printf("\nTo choose task enter:\n1)Task 1\n2)Task 2\n3)For stop program");
}

