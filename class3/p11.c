//cy23263,²“¡•à,6/11,‰‰K1
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:6031)

int main(void) {

	int array[10], * p;
	double f;

	p = array;

	*p = 10;
	printf("%d\n", p);

	p++;

	printf("%d\n", p);

	p++;

	printf("%d\n", p);

	*p = 20;

	printf("%d   %d", array[0], array[2]);

	p = &f;

	return 0;
}