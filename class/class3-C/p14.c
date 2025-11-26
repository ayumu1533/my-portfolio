//cy23263,ç≤ì°ï‡
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#define N 80

char str[N], stack[N];
char* p;
int sp = 0;
int push(char c);
char pop(void);



int main(void) {

	int a;

	scanf("%s", str);
	p = str;
	while (*p) {
		a = push(*p);
		if (a == 0) {
			break;
		}
		else {
			p++;
		}
	}
	p = str;
	while (*p) {
		*p = pop();
		p++;
	}
	printf("%s", str);
	return 0;
}
int push(char c) {


	if (&str[N] == stack) {
		return 0;
	}
	else {
		stack[sp] = c;
		sp++;
		return 1;
	}
}
char pop(void) {

	char a;
	if (sp < 0) {
		return 0;
	}
	sp--;
	return 	stack[sp];
}