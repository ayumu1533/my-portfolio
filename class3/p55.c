//cy23263,²“¡•à,7/16,‰‰K5
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
struct item* search_item(char* key, struct item* p) {
	while (p != 0) {
		if (strcmp(p->word, key) == 0) {
			return p;
		}
		p=p->next;
	}
	return 0;
}

int main(void) {
	int h = 0;
	struct item* list1, * list2, * list3,*p;
	list1 = create_item("test1", 0);
	list2 = create_item("test2", list1);
	list3 = create_item("test3", list2);
	hashtable[0] = list3;
	p = search_item("test1", hashtable[0]);
	printf("%d,%s\n", p->count, p->word);
	p = search_item("test2", hashtable[0]);
	printf("%d,%s\n", p->count, p->word);
	p = search_item("test", hashtable[0]);
	printf("%d", p);
	return 0;
}