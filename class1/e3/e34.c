//cy23263,佐藤歩
#include <stdio.h>

int main(void)
{
	int n,i, j,k,l;
	printf("整数:");
	scanf("%d", &n);//整数を入力
	if ((2 >= n) || (n >= 11)) {//範囲外の時
		printf("範囲外");//結果を出力
	}
	else {
		for (i = 1; i <= n ;i++) {//n回繰り返す
			for (j = 1; j <= i; j++) {//i回繰り返す
				printf("%d",j);//結果を出力
			}
			printf("\n");
		}
		for (k = n-1; k >= 1; k--) {//n-1回繰り返す
			for (l = 1; l <=k; l++) {//k回繰り返す
				printf("%d", l);//結果を出力
			}
			printf("\n");
		}
	}
	return 0;
}