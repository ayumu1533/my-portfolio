//cy23263,佐藤歩,7/9,演習3
#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:6031)

struct node {//node構造体
	int value;//節の値
	struct node* left;//左の節
	struct node* right;//右の節
};
int x = 0;
struct node* create_node(struct node* left, int value, struct node* right) {
	struct node* p;
	p = (struct node*)malloc(sizeof(struct node));
	if (p == 0) {
		return 0;
	}
	p->value = value;
	p->left = left;
	p->right = right;
	return p;
}
void print_tree(struct node* nodep) {
	if (nodep == 0) {
		printf("@");
		return;
	}
	else if ((nodep->left == 0) && (nodep->right == 0)) {
		printf("%d", nodep->value);
	}
	else {
		printf("<");
		print_tree(nodep->left);
		printf(",");
		printf("%d", nodep->value);
		printf(",");
		print_tree(nodep->right);
		printf(">");
	}
}
struct node* read_tree(void) {
	char a;
	int value;
	struct node* left, * right;
	scanf("%c", &a);
	if (a == '@') {
		return 0;
	}
	ungetc(a, stdin);
	if ((scanf("%d", &value) == 1) && (x != 0)) {//数字
		return create_node(0, value, 0);
	}
	else {
		x++;
	}
	scanf("%c", &a);
	if (a != '<') {//<
		printf("「<」error\n");
		return 0;
	}
	left = read_tree();
	scanf("%c", &a);
	if (a == '>') {
		return left;
	}
	if (a != ',') {//,
		printf("「NO.1の,」error\n");
		return 0;
	}
	if (scanf("%d", &value) != 1) {//数字
		printf("「値」error\n");
		return 0;
	}
	scanf("%c", &a);
	if (a != ',') {//,
		printf("「NO.2の,」error\n");
		return 0;
	}
	right = read_tree();
	scanf("%c", &a);
	if (a != '>') {//>
		printf("「>」error\n");
		return 0;
	}
	return create_node(left, value, right);
}
int search_bt(struct node* nodep, int key) {
	if (nodep == 0) {
		return 0;
	}
	else if (key == nodep->value) {
		printf("%d\n", nodep->value);
		return 1;
	}
	else if (key < nodep->value) {
		printf("%d\n", nodep->value);
		return search_bt(nodep->left, key);
	}
	else {
		printf("%d\n", nodep->value);
		return search_bt(nodep->right, key);
	}
}

int check_bt(struct node* nodep, int min, int max) {
	int i = 1;
	if (nodep == 0) {
		return 1;
	}
	else {
		if ((nodep->value > min) && (nodep->value < max)) {
			i *= check_bt(nodep->left, min, nodep->value);
			i *= check_bt(nodep->right, nodep->value, max);
			return i;
		}
		else {
			return 0;
		}
	}
}

int main(void) {
	int i;
	struct node* p;
	printf("入力：");
	p = read_tree();
	i = check_bt(p, -1, 10000);
	if (i == 0) {
		printf("だめ");
	}
	else {
		printf("おけ");
	}
	return 0;
}