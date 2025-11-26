//cy23263,佐藤歩
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double avarage(double x[30], int n) {//平均を導き出す関数

	int i;
	double sum1 = 0;

	for (i = 0; i < n; i++) {//データの個数だけ繰り返す
		sum1 += x[i];//sum1に配列の値を足す
	}

	return sum1 / n;//戻り値は平均

}

double variance(double x[30], int n) {//分散を導き出す関数

	int j;
	double sum2 = 0, var;

	for (j = 0; j < n; j++) {//データの個数だけ繰り返す

		sum2 += x[j] * x[j];//配列の値を2乗してsum2に足す

	}

	var = sum2 / n - avarage(x, n) * avarage(x, n);//分散を計算

	return var;//戻り値は分散

}



int main(void) {

	FILE *fp;//ファイルポインタ
	char fname[16] = "data32.txt";//ファイル名
	double x[30];
	int i, n = 0;

	fp = fopen(fname, "r");//データを読み出し
	if (fp == 0) {//ファイルオープンに失敗したとき
		printf("ファイル「data32.txt」が開けませんでした\n");	//結果を出力
		return 0;
	}
	while (fscanf(fp, "%lf", &x[n]) != EOF) {//ファイルからfscanf関数の戻り値が	EOFになるまでデータを読みだす
		n++;//nを1増やす
	}
	fclose(fp);//ファイルを閉じる
	for (i = 0; i < n; i++) {//データの個数だけ繰り返す
		printf("%f\n", x[i]);//読み込んだデータを出力
	}
	printf("個数: %d\n", n);//データの個数を出力
	printf("平均: %f\n", avarage(x, n));//平均を出力
	printf("分散:%f\n", variance(x, n));//分散を出力

	return 0;

}
/*
・アルゴリズム
まず、読み出しをするためにfopen関数を使う。fopen関数から返ってきた値が0の場合ファイルオープンが失敗しているため、プログラムを終了する。
ファイルが開けたとき、そのファイル内のデータの個数とデータ自体のすべての値を読み出すためにfscanf関数からEOFが返されるまでデータの個数をnを数え、配列xにそれぞれの値を代入する。
データの個数nはそのまま出力する。
avarage関数は平均を導き出す関数である。配列xの要素が0からデータの個数になるまで配列xに代入されたそれぞれのデータをsum1に足し合計を計算し、その合計をnで割ることで平均を導く。
variance関数は分散を導き出す関数である。分散の計算方法はforを用いて配列の各々の数を2乗した数をsum2に足し、その合計を計算する。その合計をnで割りその数から平均を引くことで分散が求まる。
これらの関数で求まった数をmain関数内で出力する。

・テスト
まず、ファイル「data32.txt」を.cが入っているファイルから削除し、実行するとファイル「data32.txt」が開けませんでしたと出力されたため、プログラムが正しく動作していると判断した。
テキストファイルの値を確認しデータの個数と平均と分散を手計算で計算する。その答えと実行結果の個数と平均と分散が一致したため、プログラムが正しく動作していると判断した。

*/
