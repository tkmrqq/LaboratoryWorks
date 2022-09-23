#include <stdio.h>

int search(int a)                //опр. фунцкцию
{
    for(int i=0; i<=10; i++)
        for(int j=0; j<=10-i; j++)
            if(i+j*3+(10-i-j)*5==a) //a == m
                return 1;
    return 0;
}

int main()
{   
    int m;
    printf("Input M, that > 10 and <50\n");
    scanf_s("%d", &m);
    if (m > 50 || m < 10)   //проверка условия
    {
    printf("Input correct value\n");
    main();
    }
    else
    {
        if (search(m)) printf("%d: Possible\n", m);
        else printf("%d: Not possible\n", m);
    }
    getchar();
}