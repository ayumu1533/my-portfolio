//cy23263,佐藤歩
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#define N 7

void enqueue(int data);
int dequeue(void);
void print_data(void);

int queue[N], * q_end;
int* q_tail, * q_head;



int main(void)
{
	int a = 3, x, y;
	q_end = &(queue[N]); //1つ行き過ぎ
	q_head = queue;
	q_tail = queue;



	 do{
		 printf("0:End,1：enqueue,2:dequeue:");
		scanf("%d", &a);
		if (a == 1) {
			printf("データ：");
			scanf("%d", &x);
			enqueue(x);
			
		}
		else if(a==2){
			y = dequeue();
			printf("dequeueするデータ：%d\n", y);
			
		}
		print_data();
	 } while (a != 0);

	return 0;

}
void enqueue(int data)
{
	*q_tail = data;
	q_tail++;
	if (q_tail == q_end) {
		q_tail = queue;
	}
}
int dequeue(void)
{
	int val = *q_head;
	*q_head = 0;
	q_head++;
	if (q_head == q_end) {
		q_head = queue;
	}
	return val;
}
void print_data(void) {

	int z;
	for (z = 0; z < N; z++) {
		printf("%d ", queue[z]);
	}
	printf("\n");

}
