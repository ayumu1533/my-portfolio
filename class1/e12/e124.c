//cy23263,佐藤歩
#include <stdio.h>


void encrypt(char str[16]) {//暗号化する関数
	int i = 0;

	while (str[i] != 0) {//NULLで終了
		if ((str[i] >= 'A') && (str[i] <= 'Z')) {//A～Zの時
			if (str[i] == 'Z') {//Zの時
				str[i] = 'A';//Aにする
			}
			else {//Z以外の時
				str[i] = str[i] + 1;//A～Yの時1文字後にずらす
			}
		}
		else if ((str[i] >= 'a') && (str[i] <= 'z')) {//a～zの時
			if (str[i] == 'a') {//aの時
				str[i] = 'z';//zにする
			}
			else {//a以外の時
				str[i] = str[i] - 1;//b～zの時1文字前にずらす
			}
		}
		else {//それ以外の時
			str[i] = str[i];//元の文字列をコピー
		}
		i++;//添え字を増加
	}
}


void decrypt(char str[16]) {//複合化する関数

	int i = 0;

	while (str[i] != 0) {//NULLで終了
		if ((str[i] >= 'A') && (str[i] <= 'Z')) {//A～Zの時
			if (str[i] == 'A') {//Aの時
				str[i] = 'Z';//Zにする
			}
			else {//Z以外の時
				str[i] = str[i] - 1;//A～Yの時1文字前にずらす
			}
		}
		else if ((str[i] >= 'a') && (str[i] <= 'z')) {//a～zの時
			if (str[i] == 'z') {//zの時
				str[i] = 'a';//aにする
			}
			else {//z以外の時
				str[i] = str[i] + 1;//a～yの時1文字後にずらす
			}
		}
		else {//それ以外の時
			str[i] = str[i];//元の文字列をコピー
		}
		i++;//添字を増加
	}
}


int main(void) {

	char str1[16];
	int i = 0;

	printf("文字列を入力してください(半角15文字以内):");
	scanf("%s", str1);//文字列を入力
	printf("暗号化前:%s\n", str1);//暗号前を出力
	encrypt(str1);//暗号化し、出力
	printf("暗号化後:%s\n", str1);//暗号を出力
	decrypt(str1);//複合化し、出力
	printf("複合化後:%s\n", str1);//複合を出力

	return 0;
}