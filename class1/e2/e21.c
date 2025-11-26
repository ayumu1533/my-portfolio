//cy23263,佐藤歩
#include <stdio.h>

int main(void)
{
	int a;

	//データを入力
	printf("正整数を入力してください\n");
	scanf("%d", &a);//正整数

	if ((a % 2 == 0) && (a>0)){
		printf("偶数");//結果を入力1
	}
		else if (a <= 0) {
		printf("対象外");//結果を入力2
	}
		else {
		printf("奇数");//結果を入力3
	}
	return 0;



}