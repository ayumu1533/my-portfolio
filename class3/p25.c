//cy23263,²“¡•à,6/18,‰‰K5
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
struct cell* tail_list(struct cell* list);
int list_length(struct cell* list);
void print_list(struct cell* list);
int insert_nth(struct cell* list, struct cell* newcell, int n);

int main(void) {

	int n;
	struct cell* cell1, * cell2, * cell3,* cell4;

	cell1 = create_cell(2, 0);
	cell2 = create_cell(5, cell1);
	cell3 = create_cell(1, cell2);
	cell4 = create_cell(1000, 0);
	printf("‰½”Ô–ÚF");
	scanf("%d", &n);
	if (insert_nth(cell3, cell4, n+1) == 1) {
		print_list(cell3);
	}
	else {
		printf("‘}“ü‚Å‚«‚Ü‚¹‚ñ‚Å‚µ‚½\n");
	}

	printf("ÅŒã‚Ì’lF%d", (tail_list(cell3)->value));

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

void print_list(struct cell* list) {

	struct cell* p;
	p = list;

	while (p != 0) {

		printf("=>%d", p->value);
		p = p->next;

	}
	printf("\n");

}
struct cell* tail_list(struct cell* list) {
	if (list->next == 0) return list;
	else return tail_list(list->next);
}
int list_length(struct cell* list)
{
	if (list == 0) return 0;
	else {
		return list_length(list->next) + 1;
	}
}

int insert_nth(struct cell * list, struct cell* newcell,int n) {
	int i;
	if (list_length(list) < n) {
		return 0;
	}
	else {
		for (i = 0; i != n-1; i++) {
			list = list->next;
		}
		newcell->next = list->next;
		list->next = newcell;
		return 1;
	}
}



