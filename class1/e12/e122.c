//cy23263,佐藤歩
#include <stdio.h>

int main(void) {

	char str1[21],str2[21];
	int i = 0, j = 0;

	printf("文字列を入力してください（半角20文字以内）:");
	scanf("%s", str1);//文字列を入力

	while (str1[i] != 0) {//NULLで繰り返し終了
		if (str1[i] < 'A' || str1[i] > 'Z') {//A～Z以外の時
			str2[j] = str1[i];//文字列をコピー
			j++;//str2の添字を1増加
		}
		i++;//str1の添字を1増加
	}
	str2[j] = 0;//コピーした配列の最後の文字にNULLを入れる
	printf("%s", str2);//結果を出力
	return 0;
}