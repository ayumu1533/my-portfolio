//cy23263,佐藤歩
#include <stdio.h>

int main(void) {

	int i, j, k, l, m, n, data[5][3] = { {2216,81,79},{2234,92,63},{2258,76,65},{2270,67,82},{2292,55,69} };//各要素の値を代入
	double sum[5] = {0},ave[5], eng_ave = 0, math_ave = 0;

	for (i = 0; i < 5; i++) {
		for (j = 1; j < 3; j++) {
			sum[i] += data[i][j];//各生徒の数学と英語の点数を足す
		}
		ave[i] = sum[i] / 2.0;//各生徒で平均を出す
	}
	for (k = 0; k < 5; k++) {
		eng_ave += data[k][1] / 5.0;//英語の平均を計算
	}
	for (l = 0; l < 5; l++) {
		math_ave += data[l][2] / 5.0;//数学の平均を計算
	}

	printf("学生　英　数　平均\n");
	for (m = 0; m < 5; m++) {
		for (n = 0; n < 3; n++) {
			printf("%4d", data[m][n]);//学生番号、英語、数学の値を出力
		}
		printf("%11f\n", ave[m]);//各生徒の英語と数学の点数の平均を出力
	}
	printf("英語の平均：%lf\n", eng_ave);//英語の平均を出力
	printf("数学の平均：%lf\n", math_ave);//数学の平均を出力

	return 0;
}

	