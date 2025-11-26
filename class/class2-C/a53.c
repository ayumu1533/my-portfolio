//cy23263,佐藤歩
#include<stdio.h>
#include <string.h>
#define N 50

void swap(char str[N][10], int m, int n) {//配列の文字列を交換する関数

	char t[10];

		strcpy(t,str[m]);//tにstr[m]の文字列をコピー
		strcpy(str[m],str[n]);//str[m]にstr[n]をコピー
		strcpy(str[n],t);//str[n]に置換した文字列tをコピー
}

void print_data(char str[N][10]) {//全ての文字列を出力する関数

	int i;

	for (i = 0; i < N; i++) {//N回繰り返す
		printf("%s ", str[i]);//文字列を出力
	}
	printf("\n");
}



void strsort(char str[N][10]) {//バブルソートする関数

	int i, j;

	for (i = 0; i < N - 1; i++) {//N-1回繰り返される
		for (j = 0; j < N - i - 1; j++) {//N-i-1回繰り返される
			if (strcmp(str[j], str[j + 1]) > 0) {//左の文字列が右の文字列より大きい時
				swap(str, j, j + 1);//文字列を交換
			}
		}
	}
}

int main(void) {

	char str[N][10] = { "old","lady","down","he","over","about","room","or",
"then","she","put","they","up","under","she","of","never","them","small",
"out","thing","as","also","boy","her","her","heart","and","so","style",
"ant","have","through","but","just","as","well","she","for","and","not",
"but","run","still","loud","enough","the","above","hear","in" };//データを初期化

	//ソート前を出力
	printf("ソート前\n");
	print_data(str);//全ての文字列を出力
	
	strsort(str);//strsort関数を呼び出す

	printf("ソート後\n");
	print_data(str);//全ての文字列を出力
	
	return 0;
}
/*
・アルゴリズム
関数の説明をする。
swap関数は配列内にある2つの文字列を交換する関数である。str[m]の文字列を残しておくために
strcpy関数を用いてt[10]の配列に文字列をコピーする。そして、str[m]にstr[n]をコピーし、str[n]に
文字列tをコピーする。これらの操作によってstr[m]とstr[n]の文字列が交換される。
print_data関数は配列に入れられたすべての文字列を出力する関数である。for文を用いることにより
すべての文字列を出力する。そして改行する。
strsort関数は配列に入っている文字列をバブルソートし、昇順にする関数である。（要素1～N --> 左側～右側）for文を用いて左側から
右側にかけて大きい文字列を移動させる。そして一番右側に一番大きい文字列が移動したときその文字列の位置を確定する。
この際for文の次の回では確定した文字列は比較する必要はないため確定した数だけ比較する個数を減らす。
確定させる数はN-1回でその各々で比較する回数がN-i-1回(iは文字列が確定した数)である。
また比較して右側に大きい文字列を移動させるためには、もし左側の文字列が右側の文字列より大きい時に
swap関数を使ってそれらの文字列を入れ替え、左側の文字列が右側の文字列より小さいときは何もしないようにすれば、
右側に大きい文字列を移動させることができる。
main関数内では配列strにまずデータを入れ初期化する。ソート前の初期状態のデータをprint_data関数を用いてすべての文字列を出力する。
その後、strsort関数を用いて昇順にしてからまたprint_data関数を使ってソート後の全ての文字列を出力する。

・テスト
ソート前の実行結果が自分の初期化したデータと順序も個数も一致していた。また、ソート後の実行結果が昇順に代わっていたため
バブルソートが正常に行われていたことがわかる。これらの理由よりプログラムは正常に動作したと判断した。

*/