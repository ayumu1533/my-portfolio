//cy23263,佐藤歩
#include <stdio.h>

void inpro(double a[2][2], double b[2][2], double c[2][2]) {//内積を計算する関数を作る
	int i, j, k;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			for (k = 0; k < 2; k++) {
				
				c[i][j] += a[i][k] * b[k][j];//内積を計算

			}
		}
	}

}

void printmx(double data[2][2]) {//行列の形でベクトルを出力できる関数を作る
	int i, j;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			printf("%lf ", data[i][j]);//各要素を出力
		}
		printf("\n");
	}
}


int main(void) {

	double a[2][2] = { 1.5,1.0,2.0,3.0 }, b[2][2] = { 1.0,2.0,0.5,1.0 }, c[2][2] = { 0 };

	printf("行列A\n");
	printmx(a);//行列Aを出力
	printf("行列B\n");
	printmx(b);//行列Bを出力
	inpro(a, b, c);//A,Bの内積を計算
	printf("内積\n");
	printmx(c);//内積の行列を出力

	return 0;
}