//cy23263,佐藤歩
#include <stdio.h>

double main(void)
{
	double x, y, sum;

	//データ入力
	printf("底辺:");
	scanf("%lf", &x); //底辺
	printf("高さ：");
	scanf("%lf", &y); //高さ
	//計算と表示
	sum = x * y / 2;//三角形の面積
	printf("面積は%lfです\n", sum);//結果をプリント
	return 0;
}