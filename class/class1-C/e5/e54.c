//cy23263,佐藤歩
#include <stdio.h>
int calc_fee(double length, double width, double depth, double weight);//プロダクト宣言

int main(void)
{
	int x,y, fee;
	double length, width, depth,weight;
	printf("縦の長さ(cm):");
	scanf("%lf",&length);//縦の長さを入力
	printf("横の長さ(cm):");
	scanf("%lf", &width);//横の長さを入力
	printf("奥行き(cm):");
	scanf("%lf", &depth);//奥行きを入力
	printf("重さ(kg):");
	scanf("%lf", &weight);//重さを入力
	printf("お急ぎ便(1) or 通常便(0):");
	scanf("%d", &x);//通常かお急ぎかを選択
	y = calc_fee(length, width, depth, weight);
	if (y == -1) {//条件に合いません
		printf("条件に合いません");
	}
	else if ((x == 0)&&(y != -1)) {//通常の時
		fee = y;//料金を計算
		printf("料金は%d円です", fee);//結果を出力
	}
	else if ((x == 1)&&(y != -1)) {//お急ぎ便の時
		fee = y+660;//料金を計算
		printf("料金は%d円です", fee);//結果を出力
	}
	return 0;
}

int calc_fee(double length,double width,double depth,double weight)//calc_fee関数を作る
{
	double sum;

	sum = length + width + depth;//縦横奥行きの和を計算
	if ((sum <= 100) && (weight <= 2)&&(0 < sum * weight)) {//和が100cmいないかつ重量2kg以下の時
		return 880;//戻り値は880
	}
	else if((sum<=180)&&(sum>100)&&(weight<=15)&&(weight>2)){//和が100より大きく180以下かつ重量が2kgより大きく15kg以下の時
		return 1760;//戻り値は1760
	}
	else if(sum>180||weight>15){//上記以外の時
		return -1;
	}
}