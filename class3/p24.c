//cy23263,²“¡•à,6/18,‰‰K4
#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:6031)

struct cell {
	int value;
	struct cell* next;
};

struct cell* create_cell(int value, struct cell* next);
void print_list(struct cell* list);
struct cell* search_list(int key, struct cell* list);

int main(void) {

	struct cell* cell1, * cell2, * cell3;
	int key;
	cell1 = create_cell(2, 0);
	cell2 = create_cell(5, cell1);
	cell3 = create_cell(1, cell2);
	printf("Œ©‚Â‚¯‚é”F");
	scanf("%d", &key);
	if (search_list(key, cell3)==0) {
		printf("Œ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½");
	}
	else {
		printf("Œ©‚Â‚©‚è‚Ü‚µ‚½");
	}
	return 0;
}
struct cell* create_cell(int value, struct cell* next) {

	struct cell* p;

	p = (struct cell*)malloc(sizeof(struct cell));
	if (p == 0) {
		return 0;
	}
	else {
		p->value = value;
		p->next = next;
		return p;
	}
}
struct cell* search_list(int key ,struct cell *list) {
	if (list == 0) return 0;
	else if (list->value == key) return list;
	else return search_list(key,list->next);
	
}


