//cy23263,佐藤歩
#include <stdio.h>

double main(void)
{
	double x, y, z, a, b;

	//データ入力
	printf("1個目の実数：");
	scanf("%lf", &x);//1個目の実数
	printf("2個目の実数：");
	scanf("%lf", &y);//2個目の実数
	printf("3個目の実数：");
	scanf("%lf", &z);//3個目の実数
	//計算と表示
	a = x + y + z;//合計
	printf("合計は%lfです\n", a);//結果をプリント
	b = a / 3;//平均
	printf("平均は%lfです\n", b);//結果をプリント
	return 0;
}