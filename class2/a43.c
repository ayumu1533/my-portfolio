//cy23263,佐藤歩
#include<stdio.h>

typedef struct {//構造体student
	int num; // 番号
	char name[8]; // 名前
	int eng; // 英語
	int math; // 数学
	int sci; // 理科
}student;

int main(void) {

	student students[6] = {//データを初期化
	{2409,"Miki",83,45,63},
	{2418,"Yumi",64,77,62},
	{2425,"Taro",82,65,81},
	{2442,"Jiro",69,82,67},
	{2456,"Hana",77,66,52},
	{2481,"Saki",54,76,69} };

	int i, j, total[6];
	double sum_eng = 0, sum_math = 0, sum_sci = 0, sum_ave = 0;

	printf("番号 名前 英語 数学 理科 合計\n");//表の1列目を表示

	for (i = 0; i < 6; i++) {//6回繰り返す
		total[i] = students[i].eng + students[i].math + students[i].sci;//生徒1人の合計点を計算
		printf("%d %s %3d %4d %4d %5d\n", students[i].num, students[i].name, students[i].eng, students[i].math, students[i].sci, total[i]);//結果の出力
		sum_eng += students[i].eng;//英語の合計
		sum_math += students[i].math;//数学の合計
		sum_sci += students[i].sci;//理科の合計
		sum_ave += total[i];//合計の和
	}

	printf("平均       %2.1f %2.1f %2.1f %2.1f", sum_eng / 6, sum_math / 6, sum_sci / 6, sum_ave / 6);//結果の出力

	return 0;
}

/*
・アルゴリズム
まず表の1列目を出力する。
それぞれの生徒の英語と数学理科の点数を合計する。そしてfor文と配列、構造体を使い、6人それぞれの生徒の番号、名前、英語、数学、理科、合計点
を出力する。また、そのfor文の中で生徒全員の各科目の和と合計の和をそれぞれのsumに足し合わせる。そして6で割ることによって
各科目の平均点と各生徒の合計点の平均点が求められ、それらを出力する。出力する際に行間を合わせるため%dの間に数字を入れ調整している。
また平均点は小数第1位まで出力するように%2.1fとおいて出力している。

・テスト
計算方法は変わらないため、課題のデータで実行する。
それぞれの生徒の各科目の合計と各科目の平均点を手計算した。その値が実行結果と一致したため、このプログラムは正しいと判断した。

*/