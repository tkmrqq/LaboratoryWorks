#include <malloc.h>
#include <stdio.h>


void reverse(char* str, int size)
{
    char temp;
    for (int i = 0; i < size / 2; i++)
    {
        temp = str[size - i - 1];
        str[size - i - 1] = str[i];
        str[i] = temp;
    }
}

void swapWords(char* str, int first_begin_index, int first_end_index, int second_begin_index, int second_end_index)
{
    char* str_p = &(str[first_begin_index]);
    reverse(str_p, second_end_index - first_begin_index + 1);
    reverse(str_p, second_end_index - second_begin_index + 1);
    str_p = &(str[second_begin_index - (first_end_index - first_begin_index) + (second_end_index - second_begin_index)]);
    reverse(str_p, first_end_index - first_begin_index + 1);
    str_p = &(str[second_end_index - second_begin_index + 1]);
    reverse(str_p, second_begin_index - first_end_index - 1);
}

int strLen(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

void strCopy(char *str, char **str2) {
    int len = strLen(str), i = 0;
    *str2 = (char*) calloc(len, sizeof(char));
    while(str[i] != '\0'){
        *str2[i] = str[i];
        i++;
    }
    *str2[i] = '\0';
}

int ifLetter(char s) {
    if (s >= 'a' && s <= 'z' || s >= 'A' && s <= 'Z')
        return 1;
    return 0;
}

int strCmp(char *str, char *str2){
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] - str2[i] != 0)
            return str[i] - str2[i];
        i++;
    }
    if(str[i] == '\0'){
        return -1;
    }
    return 0;
}

int findWord(char *str, int k) {
    int i = 0, cnt = 0;
    while (str[i] != 0) {
        if (i == 0 && ifLetter(str[i]) == 1 || ifLetter(str[i - 1]) == 0 && ifLetter(str[i]) == 1)
            cnt++;
        if (cnt == k)
            return i;
        i++;
    }
    return 0;
}

char *inputString(int *length) {
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

int main() {
    int length = 0;
    char *str;
    str = inputString(&length);
    return 0;
}
