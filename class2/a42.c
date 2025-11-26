//cy23263,佐藤歩
#include<stdio.h>

typedef struct {//構造体point
	double x;//x座標
	double y;//y座標
} point;

double area(point a,point b,point c) {//面積を計算する関数

	double i;

	i = ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) / 2;//面積を計算

	if (i >= 0) {//iがプラスの時
		return i;//戻り値はそのまま
	}
	else {//iがマイナスの時
		return -i;//戻り値はiをマイナスする
	}
}

point gravity(point a, point b, point c) {//重心を計算する関数

	point g;

	g.x = (a.x + b.x + c.x) / 3;//重心のx座標を計算
	g.y = (a.y + b.y + c.y) / 3;//重心のy座標を計算

	return g;//戻り値は重心のx,y
}

int main(void) {

	point a,b,c,g;

	//A,B,Cのx,y座標を入力
	printf("三角形ABCの頂点Aのx座標,y座標：");
	scanf("%lf %lf", &a.x, &a.y);
	printf("三角形ABCの頂点Bのx座標,y座標：");
	scanf("%lf %lf", &b.x, &b.y);
	printf("三角形ABCの頂点Cのx座標,y座標：");
	scanf("%lf %lf", &c.x, &c.y);

	g = gravity(a, b, c);//重心のx,y座標をg.xとg.yに代入

	//結果を出力
	if (area(a, b, c) == 0) {
		printf("三角形ではありません");
	}
	else {
		printf("三角形ABCの面積：%f\n", area(a, b, c));
		printf("三角形ABCの重心：(%f,%f)", g.x, g.y);
	}
	
	return 0;
}

/*
・アルゴリズム
A(a.x,a.y)、B(b.x,b.y)、C(c.x,c.y)として、面積を求めるarea関数とgravity関数を説明する。
area関数では面積を求めるために公式|((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x))| / 2
を使う。絶対値がついているため、あらかじめ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) / 2を
計算してから計算した値がプラスの時はそのままその値を戻り値として、マイナスの時は計算した値をマイナスにした値を戻り値とする。
gravity関数では3点それぞれのx値とy値を合計し3で割ると三角形の重心の位置が求まる。そしてそのxとyの値を構造体でを用いて戻り値として返す。
main関数内でarea関数から戻ってきた値をそのまま出力し、gravity関数から戻ってきた構造体はgに代入し、各メンバーに分けて出力する。
area関数から0が返ってきた場合三角形ではありませんと出力する。

・テスト
area内の関数でiが①0、②プラス、③マイナスの場合分けをする。
①A(0,0)B(1,1)C(2,2)
②A(0,0)B(1,0)C(0,1)
③A(1,1)B(2,1)C(1,2)
上記の結果が手計算と一致したためテストは正しいと判断した。

*/