//cy23263,²“¡•à,6/18,‰‰K2
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

int main(void) {

	struct cell* cell1, * cell2, * cell3;

	cell1 = create_cell(2, 0);
	cell2 = create_cell(5, cell1);
	cell3 = create_cell(1, cell2);

	print_list(cell3);
	print_list(cell2);
	print_list(cell1);

	return 0;
}

struct cell* create_cell(int value,struct cell*next) {

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
void print_list(struct cell * list) {

	struct cell* p;
	p = list;

	while (p != 0) {

		printf("=>%d", p->value);
		p = p->next;

	}
	printf("\n");
}
