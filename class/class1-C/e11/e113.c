//cy23263,佐藤歩
#include <stdio.h>

void input_vector(double data[3]) {//データを入力するための関数
	scanf("%lf %lf %lf", &data[0], &data[1], &data[2]);//データを入力
}
double inner_product(double data_a[3], double data_b[3]) {//内積を計算する関数
	int i;
	double sca=0;

	for (i = 0; i <= 2; i++) {//deta_aとdeta_bのそれぞれの値ををかけて足す
		sca = sca + data_a[i] * data_b[i];//内積を計算
	}
	return sca;//戻り値は内積sca
}
int main(void) {
	double sca,data_a[3],data_b[3];

	printf("3次元ベクトルAの各値を入力せよ\n");
	input_vector(data_a);//deta_aを入力
	printf("3次元ベクトルBの各値を入力せよ\n");
	input_vector(data_b);//deta_bを入力

	printf("AとBの内積は");
	sca = inner_product(data_a, data_b);//内積を計算
	printf("%lfです", sca);//内積を出力

	return 0;
}