//cy23263,佐藤歩,7/9,演習2
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
int x = 0, y = 0;
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
	if (y == 1) {
		printf("<%d>", nodep->value);
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
		y++;
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
		return 1;
	}
	else if (key < nodep->value) {
		return search_bt(nodep->left, key);
	}
	else {
		return search_bt(nodep->right, key);
	}
}
int search_min(struct node* nodep) {
	if (nodep->left == 0) {
		return nodep->value;
	}
	else {
		return search_min(nodep->left);
	}
}
int search_max(struct node* nodep) {
	if (nodep->right == 0) {
		return nodep->value;
	}
	else {
		return search_max(nodep->right);
	}
}
int search_prev(struct node* nodep, struct node* ptr, int key) {
	if (search_min(nodep) == key) {
		return 0;
	}
	while (nodep != 0) {
		if (key == nodep->value) {
			if (nodep->left == 0) {
				return ptr->value;
			}
			else {
				return search_max(nodep->left);
			}
		}
		else if (key < nodep->value) {
			nodep=nodep->left;
		}
		else {
			ptr = nodep;
			nodep =  nodep->right;
		}
	}
	return 0;
}

int main(void) {
	int i,k;
	struct node* p;
	printf("入力：");
	p = read_tree();
	printf("前の値を見つけたい値：");
	scanf("%d", &i);
	k=search_prev(p, p, i);
	if (k == 0) {
		printf("見つからなかった");
		return 0;
	}
	printf("前の値：%d", k);
	return 0;
}