//cy23263,佐藤歩
#include <stdio.h>

int main(void)
{
	int i=0, j=1;

	do {
		i = i + 1;//iに1ずつ足していく
		j = i * j;//jの値を計算
		printf("%d!=",i);//iを出力
		printf("%d\n", j);//jを出力
	} while (j<1000);//jが1000より小さい
	return 0;
}