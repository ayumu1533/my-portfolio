//cy23263,佐藤歩
#include <stdio.h>
#define N 3 // キューのサイズ

typedef struct // キューの構造体
{
	int data[N]; // キューのデータ
	int head; // 有効データの先頭場所
	int tail; // 有効データの末尾場所
	int num; // 有効データ数
} queue;

typedef struct // 戻りの構造体
{
	int data; // 読み出されたデータ
	int status; // 読み出しの成功(1)/Not(0)
} int2;
queue queuex = { {0}, 0, -1, 0 }; // グローバル変数

int enqueue(int x)// キューに書き込み
{
	if (queuex.num >= N) {// キューが満杯のとき
		return 0;//戻り値は0
	}
	else { // キューが満杯でないとき
		queuex.tail++;//格納する場所を追加
		queuex.data[queuex.tail] = x;//新しい数字を格納
		queuex.num++;//格納している個数
		return 1;//戻り値は1
	}
}

int2 dequeue(void){// キューから読み出し

	int i;
	int2 x;

	if (queuex.num <= 0) { // キューが空のとき
		x.status = 0;//戻り値x.statusに0を代入
	}
	else { // キューが空でないとき
		x.data = queuex.data[queuex.head];//一番古い格納した値を戻り値に残しておく
		for (i = 0; i <= queuex.tail; i++) {//格納している個数の数だけ繰り返す
			queuex.data[i] = queuex.data[i + 1];//データをずらす
		}
		queuex.tail--;//最後尾の場所を1降ろす
		queuex.num--;//データの数を1減らす
		x.status = 1;//戻り値x.statusに1を代入
	}
	return x;//戻り値は構造体x
}

void printqueue(void) {// キューのプリント

	int i, j;

	for (i = 0; i < queuex.num; i++) {//
		
		printf("%d ", queuex.data[i]);
	}
	printf("\n");
}

int main(void)
{
	int m, x, rtn1;
	int2 rtn2;

	do {
		printf("Menu(1:Enqueue, 2:Dequeue, 0:End): ");
		scanf("%d", &m);
		if (m == 1) { // Enqueueの処理
			printf("Data: ");
			scanf("%d", &x);
			rtn1 = enqueue(x);
			if (rtn1 == 1) printf("Success\n");
			else printf("Queue overflow\n");
		}
		if (m == 2) { // Dequeueの処理
			rtn2 = dequeue();
			if (rtn2.status == 1)
				printf("Data = %d\n", rtn2.data);
			else printf("No data\n");
		}
		printqueue(); // キューのプリント
	} while (m != 0); // Menu 0で終了

	return 0;
}
/*



*/

