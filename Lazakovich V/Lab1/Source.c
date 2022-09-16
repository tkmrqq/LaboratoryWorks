#include <stdio.h>

int main()
{
	float r, s, l;
	float pi = 3.14159;

	printf("Input radius:\n");
	scanf("%f", &r);

	s = pi*r*r;
	l = pi*r*2;

	printf("Area of a circle = %.2f\n", s); 
	printf("Length = %.2f\n", l);

	return 0;
}