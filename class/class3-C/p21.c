//cy23263,²“¡•à,6/18,‰‰K1
#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:6031)

struct cell {
	int value;
	struct cell* next;
};

struct cell* create_cell();

int main(void) {

	struct cell* cell1, * cell2, * cell3;

	cell1 = create_cell();
	cell1->value = 2;
	cell1->next = 0;
	cell2 = create_cell();
	cell2->value = 5;
	cell2->next = cell1;
	cell3 = create_cell();
	cell3->value = 1;
	cell3->next = cell2;

	printf("%d\n",cell2-> value);
	printf("%d\n", cell2-> next-> value);
	printf("%d\n", cell3-> next->value);
	printf("%d\n", cell3-> next-> next-> value);

	return 0;
}

struct cell* create_cell() {

	struct cell* p;
	p = (struct cell*)malloc(sizeof(struct cell));
	return p;
}
