//cy23263,ç≤ì°ï‡
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:6031)

int main(void) {

	int array[10], * p,i=0;

	p = array;

	while (p < &array[10]) {
		*p = 10;
		printf("%d %d\n", p ,*p);
		p++;
	}
	
	return 0;
}