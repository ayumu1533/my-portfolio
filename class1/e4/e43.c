//cy23263,佐藤歩
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int i,n1=0,n2=0,n3=0,dice;

	srand((unsigned int)time(NULL));//ランダム
	for (i = 1; i <= 100; i++) {//100回繰り返す
		dice = rand() % 3 + 1;//1～3の数字
		printf("%d", dice);//1～3の数を出力
		if (dice == 1) {//1が出たとき
			n1++;//n1が1増える
		}
		else if (dice == 2) {//2が出たとき
			n2++;//n2が1増える
		}
		else {//3が出たとき
			n3++;//n3が1増える
		}
	}
	printf("\n1の個数:%d\n", n1);//n1の数を出力
	printf("2の個数:%d\n", n2);//n2の数を出力
	printf("3の個数:%d", n3);//n3の数を出力
	return 0;
}