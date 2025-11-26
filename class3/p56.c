//cy23263,²“¡•à,7/16,‰‰K2
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_HASH 256
#pragma warning(disable:4996)
#pragma warning(disable:6031)

struct item {
	int count;
	char* word;
	struct item* next;
};
char buff[100];
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
		a->count =1;
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
		p = p->next;
	}
	return 0;
}

void chainhash(char* key) {
	int h = hash(key);
	struct item* list = hashtable[h],*p;
	p = search_item(key, list);
	if (p != 0) {
		p->count++;
	}
	else {
		hashtable[h] = create_item(key, list);
	}
}


int main(void) {
	int h = 0;
	FILE* istream;
	istream = fopen("tom.txt", "r");
	if (istream == 0) {
		printf("can not open");
		return 1;
	}
	for (int i = 0; i < 20; i++) {
		fscanf(istream, "%s", buff);
		chainhash(buff);
	}
	fclose(istream);
	dump_ht();
	

	return 0;
}