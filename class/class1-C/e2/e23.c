//cy23263,佐藤歩
#include <stdio.h>

int main(void)
{
	int a;

	//データを入力
	printf("西暦を入力してください:");
	scanf("%d", &a);//西暦入力

	if(a%4!=0){
		printf("閏年ではありません");//結果を出力1
	}
	else if ((a%4==0) && (a%100==0)&&(a%400!=0)) {
		printf("閏年ではありません");//結果を出力2
	}
	else {
		printf("閏年です");//結果を出力3
	}
	return 0;
}