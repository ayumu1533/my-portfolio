//cy23263,佐藤歩,6/13,演習5
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#define N 100

char stack[N], * sp;
/*
stack[N]の説明
・入力した文字を格納するスタックの配列
・spの最初のポインタの位置を指定する
*spの説明
・スタックに最後に入れたデータを指すポインタ
・pushとpopで操作するためグローバル変数とする。
・初期値はスタックの底を指すようにmainで代入
*/
//プロトタイプ宣言
int push(char c);
char pop(void);

int main(void) {

	int judge = 1;//judgeが1の時対応している,0の時対応していない
	char x, * p, str[N];
	//文字列を入力
	printf("入力：");
	scanf("%s", str);
	//スタックの最初のアドレスをspに代入
	sp = stack;
	//文字列の最初のアドレスをpに入力(*pは文字)
	p = str;

	while (*p) {//*pがNLLになるまで
		if (*p == '{' || *p == '(') {//文字*pが'('または'{'の時
			if (push(*p) == 0) {//push関数の戻り値が0の時、それ以外の時はpushを行い通り抜ける
				printf("overflow");//overflowを出力
				return 0;//プログラムを終了
			}


		}
		else if (*p == '}') {//文字*pが'}'の時
			x = pop();//popする
			if (x == '{') {//popされた文字が'{'の時
				p++;//pに1足す
				continue;//ループを最初から行う
			}
			if (x == '(') {//popされた数が(の時
				judge = 0;//括弧が対応していない
				break;//ループから抜ける
			}
			if (x == '0') {//underflowした時
				judge = 0;//括弧が対応していない
				printf("underflow\n");//underflowを出力
				break;//ループを抜ける
			}
		}
		else if (*p == ')') {//*pが')'の時
			x = pop();//popする
			if (x == '(') {//popされた文字が'('の時
				p++;//pに1足す
				continue;//ループを最初から行う
			}
			if (x == '{') {//popされた文字が'{'の時
				judge *= 0;	//括弧が対応していない
				break;//ループから抜ける
			}
			if (x == '0') {//underflowした時
				judge *= 0;//括弧が対応していない
				printf("underflow\n");	//underflowを出力
				break;//ループを抜ける
			}
		}
		p++;//pに1足す
	}
	if ((sp > stack) && (judge != 0)) {//開き括弧が多い時
		printf("出力：ERROR parenthesis not closed");//エラー
	}
	else if (judge == 1) {//括弧がすべて対応していた時
		printf("出力：OK");//OKを出力
	}
	return 0;
}
/*
文字列の中に丸括弧（）と波括弧{}があったら，その対応が正しいかを判定するプログラム
テスト：
文字だけ入力した場合
入力：abc　出力：OK
すべての()と{}が対応している場合
入力： ((a{bg})c(dh{e})f)　出力：OK
対応していない括弧があった場合
①文字の間に対応していない閉じ括弧がある時
入力：(a{b)c)　出力：ERROR"b)c"
入力：{a(b}c)　出力：ERROR"b}c"
②右端に対応していない閉じ括弧がある時(閉じ括弧のみ右端にある時同時にunderflowと表示する)
入力：a(}　　　出力：ERROR"(}"
入力：a{)      出力：ERROR"{)"
入力：abc)　　 underflow  出力：ERROR"c)"
入力：abc}     underflow  出力：ERROR"c}"
③左端に対応していない閉じ括弧がある時(この時同時にunderflowになるためunderflowとも表示する)
入力：}aa      underflow  出力：}a
入力：)aa      underflow  出力：)a
またunderflowが表示されるとき
入力：a)a　underflow  出力：ERROR"a)a"
入力：)aa　underflow  出力：ERROR")a"
入力：aa)　underflow  出力：ERROR"a)"
またoverflowが表示されるとき
N=3として
入力：{{{{　出力：overflow
入力：((((　出力：overflow
*/
int push(char c) {//stackにpushする関数

	if (&stack[N] == sp) {//overflowしたとき
		return 0;//戻り値が0
	}
	else {//その他の時
		*sp = c;//*spに文字cを格納
		sp++;//spに1足す
		return 1;//戻り値は1
	}
}
/*
push：1文字をstackにpushする関数
引数c：stackに格納したい文字
戻り値：stackがoverflowした時0,pushできた時1
テスト：
N=3とする。stackの容量が3として
入力：{{{{
入力：((((
の2通りを入力し、main関数内で戻り値を出力した結果0となったため正しいことを確認した。
次にNの値を変えずに正常にpushされているか見るために
入力：{
入力：((
入力：({{
printf("%s",stack);として出力するとstack内に{と(が入力された個数分pushされていることを確認した。
なお戻り値もmain関数内でprintf("%d",push(*p));として出力した結果1が出力された。
以上によりこの関数の動作が正しいことが確認できた。
*/
char pop(void) {//stackに入っている文字をpopする関数

	sp--;//spを1減らす

	if (stack > sp) {//underflowの時
		return '0';//戻り値は文字'0'
	}
	return *sp;//戻り値はpopした文字
}
/*
pop：stackに格納している文字をpopする関数
引数：なし
戻り値：underflowするとき0,popできた時1
テスト：
pop関数を行う前にpush関数を一回も行わないとき
入力：)
入力：}
の2通りを入力した結果main関数内で戻り値の文字をprintf("%c",pop());として
表示した結果'0'が出力された。
またstack内に{,(,{をpushし、})}を入力することでpopする。
入力:{({})}
pop();した後にprintf("%d",sp);を入れることでstack内の文字へのアドレスを表示すると
475124102
475124101
475124100
と減っていることを確認した。また、pop();から戻ってきた文字をprintf("%c\n",x);で出力した結果
{
(
{
となり、stackしてある文字が戻り値となっていることを確認した。
以上によりこの関数の動作が正しいことを判断した。
*/