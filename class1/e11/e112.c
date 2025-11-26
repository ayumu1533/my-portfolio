//cy23263,佐藤歩
#include <stdio.h>


double ctof(double c) {//ctof関数を作成
	double f;

		f = (9.0/5.0) * c + 32;//摂氏気温を華氏気温に変換
	
	return f;//戻り値はf
}


int main(void){
	int i;
	double deta1[6] = { -17.8,0,10,20,30,37.8 },deta2[6];//deta1に値を代入

	for (i = 0; i < 6; i++) {
		deta2[i] = ctof(deta1[i]);//変換されたそれぞれの値をdeta2に代入
	}
	for (i = 0; i < 6; i++) {//6回繰り返す
		printf("%f C → %f F\n", deta1[i], deta2[i]);//deta1,deta2を出力
	}
	return 0;
}