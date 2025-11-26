//cy23263,佐藤歩
#include <stdio.h>

int main(volid)
{
	int x, y, z;
	//データ入力
	printf("被除数");
	scanf("%d", &x);//被除数入力
	printf("除数");
	scanf("%d", &y);//除数入力
	//計算と表示
	z = x / y;//商
	printf("商は%dです\n", z);//結果をプリント
	z = x % y;//余り
	printf("余りは%dです\n", z);//結果をプリント
	return 0;
}
