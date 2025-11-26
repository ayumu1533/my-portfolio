//cy23263,佐藤歩
#include <stdio.h>

int main(void)

{
	double a1, a2, b1, b2;

	//データを入力
	printf("一つ目の範囲[a1,a2]のa1を入力してください:");
	scanf("%lf", &a1);//a1を入力
	printf("一つ目の範囲[a1,a2]のa2を入力してください:");
	scanf("%lf", &a2);//a2を入力
	printf("二つ目の範囲[b1,b2]のb1を入力してください:");
	scanf("%lf", &b1);//b1を入力
	printf("二つ目の範囲[b1,b2]のb2を入力してください:");
	scanf("%lf", &b2);//b2を入力

	if ((a1 >= a2) || (b1 >= b2)) {
		printf("入力エラー");//結果を出力1
	}else if ((a1 < a2) && (b1 < b2) && (a1 <= b2) && (b1 <= a2)) {
		printf("重なりを持ちます");//結果を出力2
	}else {
		printf("重なりを持ちません");//結果を出力3
	}
	return 0;
}