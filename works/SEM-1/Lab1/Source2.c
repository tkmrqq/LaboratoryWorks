#include  <stdio.h>

int main()
{
	int a, b, c, d;
	printf("Input Numbers:\n");
	scanf_s("%d %d %d", &a, &b, &c);
//function
	d = a;
	if (d < b) d = b;
	if (d < c) d = c;
	printf("The biggest number is: ");
	printf("%d\n", d);
	return 0;
}