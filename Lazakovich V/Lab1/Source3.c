#include <stdio.h>

double sqrt(double r, int x, int y) {
    int n;
    n = (x * x) + (y * y);
    while (r * r < n) { r += 0.0001; }
    return r;
}

int main()
{
    int x1, x2, x3, y1, y2, y3;
    double r1 = 0, r2 = 0, r3 = 0;

    printf("Enter coordinates of A point:");
    scanf_s("%d %d", &x1, &y1);
    printf("Enter coordinates of B point:");
    scanf_s("%d %d", &x2, &y2);
    printf("Enter coordinates of C point:");
    scanf_s("%d %d", &x3, &y3);

    r1 = sqrt(r1, x1, y1);
    r2 = sqrt(r2, x2, y2);
    r3 = sqrt(r3, x3, y3);
    
    if (r1 < r2 && r1 < r3)
        printf("The shortest distance has point A with coordinates: %d %d\n", x1, y1);
    else  if (r2 < r1 && r2 < r3)
        printf("The shortest distance has point B with coordinates: %d %d\n", x2, y2);
    else  if (r3 < r1 && r3 < r2)
        printf("The shortest distance has point C with coordinates: %d %d\n", x3, y3);
    else printf("No largest number found");

    return 0;
}