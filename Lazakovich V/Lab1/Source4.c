#include <stdio.h>

int main()
{   
    int i;
    printf("Введите номер семестра =");
    scanf("%d", &i);
    printf("В этом семестре изучаются: ");
    switch (i)
    {
    case 1:
        printf("Информатика и Ин.язык");
        break;
    case 2:
        printf("Информатика и Ин.язык");
        break;
    case 3:
        printf("Культурология, Математика и Ин.язык");
        break;
    case 4:
        printf("Культурология, Математика и Ин.язык");
        break;
    default:
        break;
    }
    return 0;
}