#include <stdio.h>

int main() {
    fprintf(stderr, "Are you sure?(Y/N)");
    char sure;
    scanf_s("%1s", &sure);
    if(sure == 'Y' || sure == 'y')
        printf("Hello world!");
    else
        return 0;
}
