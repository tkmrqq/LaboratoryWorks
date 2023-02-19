#include <conio.h>
#include <stdio.h>

int intInp() {
    int p;
    while (scanf_s("%d", &p) != 1) {
        printf("Print correct number: ");
        rewind(stdin);
    }
    rewind(stdin);
    return p;
}

char* inputString() {
    char* str, *strEnd;
    int len = 0;
    str = new char[256];
    printf("Input string:");
    for (int i = 0; i < 256; i++) {
        if (i == 255) {
            str[i] = '\0';
            break;
        }
        str[i] = _getch();

        if (str[i] == '\r') {
            str[i] = '\0';
            break;
        }
        printf("%c", str[i]);
        if (str[i] == '\b') {
            printf(" \b");
            i -= 2;
            continue;
        }
    }
    printf("\n");
    for (int i = 0; i < 256; i++) {
        if (str[i] == '\0') {
            len = i + 1;
            break;
        }
    }
    strEnd = new char[len];
    for (int i = 0; i < len; i++) {
        strEnd[i] = str[i];
    }
    delete[] str;
    return strEnd;
}

int lenFind(char* arr) {
    int len = 0;
    while (true) {
        if (arr[len] != '\0') {
            len += 1;
        }
        else {
            len += 1;
            break;
        }
    }
    printf("Lenght is %d\n", len - 1);
    return len;
}

void outputString(int len, char* arr) {
    printf("Your string is: ");
    for (int i = 0; i < len; i++) {
        printf("%c", arr[i]);
    }
    printf("\n");
}

void labTask(char* arr, int len) {
    int firstWordStartSymbol = -1, endOfWords = -1, ourSymbol, countOfWords = 1, countAfterSymbol = 0;
    // start of words
    for (int i = 0; i < len - 1; i++) {
        if (arr[i] != ' ') {
            firstWordStartSymbol = i;
            break;
        }
    }
    // check on words
    if (firstWordStartSymbol < 0) {
        printf("No words in string..");
        return;
    }
    //end of words
    for (int i = len - 2; i >= 0; i--) {
        if (arr[i] != ' ') {
            endOfWords = i + 1;
            break;
        }
    }
    //input k
    printf("Input number of k-symbol: ");
    do {
        ourSymbol = intInp();
        if (ourSymbol < 0 || ourSymbol > len - 2) {
            printf("Inpu number from 0 to %d: ", len - 2);
        }
    } while (ourSymbol < 0 || ourSymbol > len - 2);
    // check k on words before and in
    if (ourSymbol < firstWordStartSymbol) {
        printf("We haven't words before k-symbol..");
        printf("Click 1 to continue programm..\n");
        if (_getch() == '1') {
            labTask(arr, len);
        }
        return;
    }
    // count words
    for (int i = firstWordStartSymbol; i < endOfWords; i++) {
        if (arr[i] == ' ' && arr[i - 1] != ' ') {
            countOfWords += 1;
        }
    }
    // make k in word before k if 'space'
    if (arr[ourSymbol] == ' ') {
        while (arr[ourSymbol] == ' ') {
            ourSymbol--;
        }
    }
    // words after k
    for (int i = ourSymbol; i < endOfWords; i++) {
        if (arr[i] == ' ' && arr[i - 1] != ' ') {
            countAfterSymbol += 1;
        }
    }
    // порядковый номер слова
    printf("Ordinal number of word is %d\n", countOfWords - countAfterSymbol);
    printf("Click 1 to continue programm..\n");
    if (_getch() == '1') {
        labTask(arr, len);
    }
}

int main() {
    char* string = 0;
    int len;
    string = inputString();
    len = lenFind(string);
    outputString(len, string);
    labTask(string, len);
    delete[] string;
}