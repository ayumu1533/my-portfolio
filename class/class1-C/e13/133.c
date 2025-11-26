//cy23263,佐藤歩
#include <stdio.h>


int main(void) {

	char str[2][33];
	int i = 0, j = 0;

	printf("文字列を入力してください(半角32文字以内):");
	scanf("%s", str[0]);//文字列を入力
	printf("%s\n", str[0]);//入力した文字列を出力
    
	while (str[0][i] != 0) {//NULLまで
		if ('0' <= str[0][i] && str[0][i] <= '9') {//0～9の文字の時
			str[1][j] = str[0][i];//行列をコピー
			j++;
		}
		i++;
	}

	str[1][j] = 0;//コピーされた行列の最後にNULL
	printf("%s", str[1]);//数字だけの文字列を出力

	return 0;
}