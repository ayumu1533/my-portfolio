//cy23263,佐藤歩
#include <stdio.h>

int main(void) {
	int  i, ave;
	double sum = 0, score[5];

	printf("得点を入力せよ\n");
	for (i = 1; i <= 5; i++) {//5回を繰り返す
		printf("%d人目:", i);
		scanf("%lf", &score[i - 1]);//スコアを入力
	}
	for (i = 1; i <= 5; i++) {
		sum = sum + score[i - 1];//合計を計算
	}
	ave = sum / 5.0+0.5;//平均を四捨五入
	printf("平均点:%d\n", ave);
	for (i = 1; i <= 5; i++) {//5回繰り返す
	printf("%d人目:%d(%d)\n", i,(int) score[i - 1],(int) score[i - 1] - ave);//結果を出力
	}
	return 0;
}