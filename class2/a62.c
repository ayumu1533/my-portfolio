//cy23263,佐藤歩
#include<stdio.h>
#define N 300


void histdisp(int hist[10]) {//ヒストグラムを表示する関数

	int i,j;

	for (i = 0; i < 10; i++) {//iを0から1ずつ足して9まで繰り返す
		printf("%2d- %2d:", i * 10, (i + 1) * 10 - 1);//ヒストグラムの
		for (j = 0; j < hist[i]; j++) {//配列histのそれぞれの値だけ繰り返す
			printf("*");//*を出力
		}
		printf("\n");//改行
	}

}
void histgram(int d[N], int n) {//ヒストグラムを計算し、表示する関数

	int hist[10] = { 0 }, i = 0, j, k;
	
	while (i < n) {//i<nの時続ける
		j = d[i] / 10;//データを10で割る
		for (k = 0; k < 10; k++) {//iを0から1ずつ増やして10まで繰り返す
			if (j == k) {//データを10で割った値がkと一致したとき
				hist[j]++;//そのデータをカウント
			}
		}
		i++;//iを1足す
	}
	histdisp(hist);//ヒスとグラムの表示
}


int main(void) {

	FILE* fp;
	int i, n = 0, dat[N];
	fp = fopen("data62.txt", "r");
	if (fp == 0) {
		printf("ファイルdata62.txtが開けませんでした\n");
		return 0;
	}
	while (fscanf(fp, "%d", &dat[n]) != EOF) {
		n++;
	}
	fclose(fp);

	histgram(dat, n);

	return 0;

}
/*
・アルゴリズム







*/


