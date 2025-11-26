//cy23263,佐藤歩
#include <stdio.h>

int compare(char c) {//aiueoの時戻り値1,それ以外を戻り値2とする関数

	char vowels[6] = "aiueo";//母音を代入
	int i;

	for (i = 0; i < 5; i++) {//添字が母音の時
		if (c == vowels[i]) {
			return 1;//戻り値は
		}
	}
	vowels[i] = 0;
	return 0;
}

int main(void) {

	char str1[33],str2[33];
	int i = 0;

	printf("文字列を入力してください(32文字以内)\n");
	scanf("%s",str1);//文字列を入力
	while (str1[i] != 0) {//NULLの
	if (compare(str1[i]) == 1) {//母音の時
		str2[i]='*';//*をコピーの文字列に代入
	}
	else if (compare(str1[i]) == 0) {//母音以外の時
		str2[i]=str1[i];//コピー
	}
	i++;//添字を増加
	}
	str2[i] = 0;//NULLをコピーした最後の文字に代入
	printf("%s", str2);//結果を出力

	return 0;
}