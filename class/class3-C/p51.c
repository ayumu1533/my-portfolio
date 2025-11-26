//cy23263,佐藤歩,7/16,演習1
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:6031)
char buff[100];

char* create_string(char* buff) {
	char* p;
	p = (char*)malloc(strlen(buff) + 1);
	if (p == 0) {
		return 0;
	}
	strcpy(p, buff);
	return p;
}

int main(void) {
	char* p;
	int i = 0,j=0;
	printf("入力：");
	scanf("%99s", buff);
	printf("コピーした文字列：");
	p = create_string(buff);
	printf("%s\n", p);
	return 0;
}