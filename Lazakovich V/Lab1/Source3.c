#include <stdio.h>

int main()
{
    int x1, x2, x3, y1, y2, y3;
    double r1=0, r2=0, r3=0, n1, n2, n3;

    printf("Enter coordinates of A point:");
    scanf("%d %d", &x1, &y1);
    printf("Enter coordinates of B point:");
    scanf("%d %d", &x2, &y2);
    printf("Enter coordinates of C point:");
    scanf("%d %d", &x3, &y3);

    n1 = (x1*x1)+(y1*y1);
    n2 = (x2*x2)+(y2*y2);
    n3 = (x3*x3)+(y3*y3);

    while(r1*r1 < n1) {r1+=0.0001;}; //Вычисление корней 
    while(r2*r2 < n2) {r2+=0.0001;};
    while(r3*r3 < n3) {r3+=0.0001;}; 

    printf("корень = %lf %lf %lf\n", r1, r2, r3);

    if(r1 < r2 && r1 < r3)          //Сравнение полученных расстояний
      printf("The shortest distance has point A with coordinates: %d %d\n", x1, y1);
    else  if(r2 < r1 && r2 < r3)
      printf("The shortest distance has point B with coordinates: %d %d\n", x2, y2);
    else  if(r3 < r1 && r3 < r1)
      printf("The shortest distance has point C with coordinates: %d %d\n", x3, y3);
    else printf("No largest number found");

	return 0;
}