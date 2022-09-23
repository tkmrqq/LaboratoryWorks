#include <stdio.h>

int main()
{   
    double l = 0, S = 20, v1=2, v2=3, v3=5, v4; //v1 - скорость П1, v2 - скорость П2, v3 - скорость шмеля, v4 - скорость сближения пеш.
    v4 = v1 + v2;

    while (S > 0.00001)
    {
        double t=S/(5+v1);  //время полета к встр. пешеходу
        l+=t*5;             //путь шмеля за это время
        S-=t*v4;            //сокращенное расстояние между пешеходами
    }

    printf("Путь который пролетел шмель ~ %lf", l);
    getchar();
    return 0;
}