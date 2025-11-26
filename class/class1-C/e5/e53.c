//cy23263,佐藤歩
#include <stdio.h>
void printstar(int n);//プロダクト宣言

int main(void)
{
	int n,i,j;
	printf("段数:");
	scanf("%d",&n);//段数を入力
	if (n <= 0) {//段数が0以下の時
		printf("1以上を入力してください");//結果を出力
	}
	for (i = 1; i <= n;i++) {//n回繰り返す
		printstar(i);//i回繰り返す
	}
	for (j = n - 1; j >= 1; j--) {//n-1回繰り返す
		printstar(j);//j回繰り返す
	}
	return 0;
}




void printstar(int n) //printstar関数を作る
{
	int i = 0;
	for (i = 1; i <= n; i++) {//n回繰り返す
		printf("*");//*を出力
	}
	printf("\n");//改行
}