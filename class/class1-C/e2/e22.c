//cy23263,佐藤歩
#include <stdio.h>

int main(void)
{
	int a, b;

	//データを入力
	printf("月:");
	scanf("%d", &a);//月を入力
	printf("日:");
	scanf("%d", &b);//日を入力

	if ((a == 12)||((a == 11)&&((b>4)&&(b<=30)))){
		printf("創立記念日後");//結果を出力1
	}
		else if (((a>=1) && (a<11)) || ((a == 11) && (b<4) && (b >= 1))) {
		printf("創立記念前");//結果を出力2
	}
		else if ((a == 11) && (b == 4)) {
		printf("創立記念日");//結果を出力3
	}
	return 0;
}