//cy23263,佐藤歩
#include <stdio.h>

int main(void)
{
	int i=10000, j;//iに10000を代入
	while (i > 0) {
		printf("残額は%d円です\n", i);//残額をプリント
		printf("支払金額:");
		scanf("%d", &j);//支払金額を入力
		if (j > i) {
			printf("残額が足りません\n");//残額が足りないとき
		}else {
			i = i - j;
		}//残額が足りたとき、計算

	}
	printf("残額が0円になりました\n終了します");
	return 0;
}