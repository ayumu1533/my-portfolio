//cy23263,²“¡•à,7/16,‰‰K2
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_HASH 256
#pragma warning(disable:4996)
#pragma warning(disable:6031)
char buff[100];

struct item {
	int count;
	char* word;
	struct item* next;
};
struct item* hashtable[256];
char* create_string(char* buff) {
	char* p;
	p = (char*)malloc(strlen(buff) + 1);
	if (p == 0) {
		return 0;
	}
	strcpy(p, buff);
	return p;
}

int hash(char* p) {
	int h = 0;
	while (*p != 0) {
		h = h + *p;
		p++;
	}
	return h % MAX_HASH;
}

struct item* create_item(char* key, struct item* p) {

	struct item* a;
	a = (struct item*)malloc(sizeof(struct item));
	if (a == 0) {
		return 0;
	}
	else {
		a->count = 1;
		a->word = create_string(key);
		a->next = p;
		return a;
	}
}

void print_list(struct item* p)
{
	while (p != 0) {
		printf("=><%s,%d>", p->word, p->count);
		p = p->next;
	}
	printf("\n");
}

void dump_ht(void) {
	int h = 0;
	for (h = 0; h < MAX_HASH; h++) {
		if (hashtable[h] != 0) {
			print_list(hashtable[h]);
		}
	}
}
int main(void) {
	struct item* item1, * item2, * item3, * item4, * item5, * item6;
	item1 = create_item("test1", 0);
	item2 = create_item("test2", item1);
	item3 = create_item("test3", item2);
	item4 = create_item("test4", 0);
	item5 = create_item("test5", item4);
	item6 = create_item("test6", 0);
	hashtable[0]=item3;
	hashtable[10] = item5;
	hashtable[20] = item6;
	dump_ht();
}