//cy23263,佐藤歩
#include<stdio.h>
#include<stdlib.h>

int main(void) {

	int i, n, * x;
	double sum = 0;
	//データ数を入力
	printf("データ数：");
	scanf("%d", &n);
	if (n == 0) {
		return 0;
	}
	x = calloc(n , sizeof(int));//intの配列をn個確保

	if (x == NULL) {//先頭のポインタがNULLの時
		printf("Allocation error\n");//結果を出力
		return 0; // 強制終了
	}
	else {//最初のポインタがNULLじゃない時
		for (i = 0; i < n; i++) {//n回繰り返す
			//n個のデータを入力
			printf("データ%d：", i+1);
			scanf("%d", &x[i]);
			sum += x[i];//入力したデータの合計を計算
		}
		for (i = 0; i < n; i++) {//n回繰り返す
			printf("%d ", x[i]);//入力したデータをすべて出力
		}
		printf("\n");
		free(x);//メモリを解放

		printf("平均：%f", sum / n);//平均を出力
	}
	return 0;
}
/*
・アルゴリズム
xに先頭のポインタを代入し、n個の配列を確保する。先頭のポインタがNULLの時、
強制終了する。その他の時、データをn個入力し、for文を用いてその値をsumに足し
合わせる。そして入力した値をfor文を用いて出力し、sumをnで割った平均を出力する。

・テスト
nが0より小さい時メモリを確保できないため、Allocation errorを出力する。
nが0の時プログラムが終了した。
nが0より大きい時、







*/