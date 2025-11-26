//cy23263,佐藤歩
#include <stdio.h>

int compare(char k, char str_b[21]) {

	int j=0;
	while (str_b[j] != 0) {//BがNULLの時終了

		if (str_b[j] == k) {//Aの一文字とBの内の一つの数字が同じとき
			return 0;//中断
		}
		j++;
	}
	return 1;//どれも違うとき、戻り値1
}
int main(void) {
	char str_a[21], str_b[21], c[21], k;
	int i = 0, j = 0;

	

	printf("文字列Aを入力してください(半角20文字以内)\n");
	scanf("%s", str_a);//文字列Aを入力
	printf("文字列Bを入力してください(半角20文字以内)\n");
	scanf("%s", str_b);//文字列Bを入力
	while (str_a[i] != 0) {//AがNULLの時終了
		k = str_a[i];//Aの一文字をkに代入
		if (compare(k, str_b) == 1) {//Aの一文字とBのすべての文字が違うとき
			c[j] = str_a[i];//コピーする
			j++;
		}
		i++;
	}
	c[j] = 0;//コピーした最後の文字にNULL
	printf("A-B:%s", c);//結果を出力

	return 0;
}