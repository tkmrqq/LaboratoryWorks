#include <windows.h>

void errorOutput(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    printf("Wrong input! Please, try again \n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
}

void check(int arraySize) {
    int x;
    while (scanf_s("%d", &x) != 1 || x > 100 || x < 1 || getchar() != '\n') {
        errorOutput();
        rewind(stdin);
    }
}
