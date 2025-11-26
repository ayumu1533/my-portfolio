//cy23263,佐藤歩,6/18,演習3
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
int list_length(struct cell* list);

int main(void) {

	struct cell* cell1, * cell2, * cell3;

	cell1 = create_cell(2, 0);
	cell2 = create_cell(5, cell1);
	cell3 = create_cell(1, cell2);

	printf("　長さ：%d\n", list_length(cell1));
	printf("　長さ：%d\n", list_length(cell2));
	printf("　長さ：%d", list_length(cell3));

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
	}
	return p;

}
int list_length(struct cell* list)
{
	if (list == 0) return 0;
	else {
		printf("=>%d", list->value);
		return list_length(list->next)+1;
	}
}

