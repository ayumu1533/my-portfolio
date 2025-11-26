#include<stdio.h>


int perm(int n, int r) {//nPrを導く関数

	int upstairs1, upstairs2;

	upstairs1 = fact(n);//n!をupstairs1代入

	upstairs2 = fact(n - r);//(n-r)!をupstairs2代入

	return (upstairs1 / upstairs2);//nPrが戻り値

}

int fact(int n) {//n!を導く関数

	int a, upstairs = 1;

	for (a = n; a >= 1; a--) {//n回繰り返す
		upstairs *= a;//n以下の数をすべてかける計算
	}

	return upstairs;//n!を計算

}



int main(void) {

	int i, j;

	for (i = 1; i <= 4; i++) {//nPrのnを4まで繰り返す
		for (j = 1; j <= i; j++) {//nPrのrを4まで繰り返す
				printf("%dP%d = %d\n", i, j, perm(i, j));//結果を出力
			}
	}
	return 0;

}

/*
・アルゴリズム
nを引数として戻り値n!を返すfact関数を作る。
n!の計算は引数をupstairs（初期値は1）にn以下の数をそれぞれ掛けていくことで求まる。
n,rを引数として戻り値nPrを返すperm関数を作る。
fact関数を使いn!と(n-r)!を求める。nPr=n!/(n-r)!よりnPrを求める。
main関数ではnPrのnとrに入れる数をfor文を用いて、順番に入れていく。
nPrでは必ずn>=rとなるため、nにつき次の操作を行う。
rを1ずつ増加させ、nの数になったらnを1増やし、nが4になるまでそれを繰り返す。
その都度nPrをperm関数を使い計算する。それによって出た答えを出力する。

・テスト
nPrの答えがすべて手計算と一致するため正しいと判断した。

*/