//cy23263,佐藤歩
#include <stdio.h>
#include <math.h>
#define PI 3.141592//PIを定義
int main(void)
{
		int deg, c;
		double rad;

		for (deg = 0; deg <= 360; deg += 15) {//15度ずつ足して360まで
			rad = PI / 180 * deg;//角度をラジアンに変換
			printf("%3d:", deg);//角度を出力
			for (c = 1; c <= 20 + 20 * sin(rad); c++) {//*の前のスペースの繰り返す回数をsinで求める
				printf(" ");

			}
			printf("*\n");//*を出力
		}
		return 0;
}
