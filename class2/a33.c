//cy23263,佐藤歩
#include<stdio.h>
#include<string.h>
void swap(char str1[9], char str2[9]) {//2つの配列の文字列を交換する関数

	char str3[9];

	strcpy(str3, str1);//str1の文字列をstr3にコピー
	strcpy(str1, str2);//str2の文字列をstr1にコピー
	strcpy(str2, str3);//str3の文字列をstr2にコピー

}


int main(void) {

	char str1[9], str2[9], str3[9];

	printf("文字列を3つスペースで区切って入力してください:");
	scanf("%s %s %s", str1, str2, str3);//値を入力

	if (strlen(str1) > 8 || strlen(str2) > 8 || strlen(str3) > 8) {//入力された値が8文字より大きいとき
		printf("各単語は8文字以内にしてください");//結果を出力
		return 0;
	}



	if (strcmp(str1, str2) > 0) {//str1がstr2より大きい時
		swap(str1, str2);//str1とstr2の文字列を交換する
	}
	if (strcmp(str2, str3) > 0) {//str2がstr3より大きい時
		swap(str2, str3);//str1とstr2の文字列を交換する
	}
	if (strcmp(str1, str2) > 0) {//str1がstr2より大きい時
		swap(str1, str2);//str1とstr2の文字列を交換する
	}


	printf("%s %s %s", str1, str2, str3);//結果を出力

	return 0;

}
/*
・アルゴリズム
まず、3つの入力された文字列の文字数で8より大きい配列が一つでもあるとき
各単語は8文字以内にしてくださいと出力しプログラムを終了する。それ以外の時次の操作をする。
出力された3つの文字列をa,b,cとして、aとbを比較する。aがbより大きい時、aとbを交換する。
次に、bとcを比較し、bがcより大きいのであればbとcを交換する。なお、ここでいう交換は値の入れ替えであり、
aとbとcの順番自体はそのままである。そのため、更にaとbを比較し、aがbより大きい時、aとbを交換する操作をする
必要がある。これらの操作よりa,b,cの並びが小さい順となる。そして、a,b,cをその順番のまま出力する。

・テスト
3つの文字列をstr1,str2,str3とする。
入力された文字列が8文字以下の時、次の場合を確認する
①str1>str2>str3②str1>str3>str2③str2>str1>str3④str2>str3>str1⑤str3>str1>str2⑥str3>str2>str1
①str1='c',str2='b',str3='a'
②str1='c',str2='a',str3='b'
③str1='b',str2='c',str3='a'
④str1='b',str2='a',str3='c'
⑤str1='a',str2='c',str3='b'
⑥str1='a',str2='b',str3='c'
上のすべての場合で実行した結果小さい順になった。
⑦str1=str2>str3⑧str2=str3>str1⑨str3=str1>str2⑩str3>str1=str2⑪str1>str2=str3⑫str2>str1=str3
⑦str1='b',str2='b',str3='a'
⑧str1='a',str2='b',str3='b'
⑨str1='b',str2='a',str3='b'
⑩str1='a',str2='a',str3='b'
⑪str1='b',str2='a',str3='a'
⑫str1='a',str2='b',str3='a'
上のすべての場合で実行した結果正しく並んだことを確認した。
str1、str2、str3の文字列が同じときは入れ替えないためテストしなくても自明である。
入力された文字列が1つでも8文字より大きい時各単語は8文字以内にしてくださいと出力することを確認できた。
以上よりこのプログラムは正しく動作すると判断した。

*/
