//cy23263,佐藤歩,7/16,演習2
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_HASH 256
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

int hash(char *p) {
	int h = 0;
	while (*p  != 0) {
		h = h + *p;
		p++;
	}
	return h % MAX_HASH;
}

int main(void) {
	int i=0;
	printf("入力：");
	scanf("%99s", &buff);
	printf("コピーした文字列：");
	printf("%s\n", create_string(buff));
	printf("ハッシュ値：");
	printf("%d", hash(buff));
	return 0;
}