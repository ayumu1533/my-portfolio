//cy23263,佐藤歩,7/18,演習7
/*
ハッシュ表へtom.txtの最初の100文字を登録し、その100文字が格納されたハッシュ表のwordメンバとcountメンバを全て出力し、
削除したい単語を入力することでハッシュ表からその単語が入っているitemを削除するプログラム
テスト：
まずファイルの読み込みをテストする。
p57.cが入っているファイルにtom.txtが入っていないとき実行すると、
出力：
can not open
が出力されたことを確認した。
tom.txtを入れ、再び実行すると
=><through,1>
=><Whats,1>=><CHAPTER,1>
=><heart,1>=><pride,1>
=><could,1>
=><small,1>
=><thing,1>
=><about,1>
=><under,1>
=><built,1>=><never,1>=><She,2>
=><state,1>=><THROUGH,1>=><The,1>
=><spectacles,1>
=><stove,1>=><style,1>
=><and,4>
=><You,1>
=><her,3>=><old,1>
=><she,2>
=><the,2>
=><for,3>
=><I,2>
=><boy,2>
=><but,1>
=><not,2>
=><fiercely,1>
=><out,1>
=><put,1>
=><a,4>
=><looked,4>
=><seldom,1>
=><pulled,1>
=><wonder,1>
=><moment,1>=><answer,3>
=><said,1>
=><have,1>
=><gone,1>
=><lady,1>
=><seen,1>
=><lids,1>=><pair,2>
=><them,4>
=><then,2>
=><that,1>
=><were,2>
=><well,1>
=><down,1>
=><they,1>
=><over,1>=><with,1>
=><room,1>=><No,3>
=><just,1>
=><perplexed,1>
=><as,2>
=><of,2>
=><or,1>
=><so,1>
=><up,1>
=><TOM,3>
=><service,1>
が出力された。
tom.txtの中の文字の最初の100単語と登録されている単語の数と種類を比べると一致したことを確認した。
次に削除する(それぞれの場合の削除はdelete_item関数で説明しているため省略する)。
削除したい文字列：TOM
=><through,1>
=><Whats,1>=><CHAPTER,1>
=><heart,1>=><pride,1>
=><could,1>
=><small,1>
=><thing,1>
=><about,1>
=><under,1>
=><built,1>=><never,1>=><She,2>
=><state,1>=><THROUGH,1>=><The,1>
=><spectacles,1>
=><stove,1>=><style,1>
=><and,4>
=><You,1>
=><her,3>=><old,1>
=><she,2>
=><the,2>
=><for,3>
=><I,2>
=><boy,2>
=><but,1>
=><not,2>
=><fiercely,1>
=><out,1>
=><put,1>
=><a,4>
=><looked,4>
=><seldom,1>
=><pulled,1>
=><wonder,1>
=><moment,1>=><answer,3>
=><said,1>
=><have,1>
=><gone,1>
=><lady,1>
=><seen,1>
=><lids,1>=><pair,2>
=><them,4>
=><then,2>
=><that,1>
=><were,2>
=><well,1>
=><down,1>
=><they,1>
=><over,1>=><with,1>
=><room,1>=><No,3>
=><just,1>
=><perplexed,1>
=><as,2>
=><of,2>
=><or,1>
=><so,1>
=><up,1>
=><service,1>
上記よりTOMが削除されたことを確認した。
よってこのプログラムは正しいと判断した。
*/
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_HASH 256
#pragma warning(disable:4996)
#pragma warning(disable:6031)

struct item {
	int count;
	char* word;
	struct item* next;
};
struct item* hashtable[256];//ハッシュ表のそれぞれのリストの先頭へのポインタを格納する配列
/*
create_string：文字列を新たに作る関数
引数key：コピーする文字列へのポインタ
戻り値：
テスト：main関数内に
printf("入力：");
	scanf("%99s", buff);
	while (buff[i] != 0) {
		printf("%c,%d\n", buff[i], &buff[i]);
		i++;
	}
	printf("コピーした文字列：");
	p = create_string(buff);
	printf("%s\n", p);
	while (*p != 0) {
		printf("%c,%d\n", *p, p);
		p++;
	}
として入力したままの文字列とcreate_stringによってコピーされた文字列の個々の文字とアドレスを表示する。
入力：abc
a,359913248
b,359913249
c,359913250
コピーした文字列：abc
a,2064809392
b,2064809393
c,2064809394
となった。
入力した文字列とコピーされた文字列の個々の文字が同じなのに対してアドレスが異なっているため
違うメモリに文字列が記憶されたことがわかる。そのため文字列がコピーされたことを確認できた。
よってこの関数は正しく動作していると判断した。
なお、main関数内でkeyに何も入れずkeyを引数とするとstrlenに空の文字列が入るため、テストできないと判断した。
*/
char* create_string(char* key) {
	char* p;
	p = (char*)malloc(strlen(key) + 1);
	if (p == 0) {
		return 0;
	}
	strcpy(p, key);
	return p;
}
/*
hash：文字列のハッシュ値を求める関数
引数p：ハッシュ値を求めたい文字列の先頭へのポインタ
戻り値：ハッシュ値
テスト：
main関数内で
scanf("%s",key);として文字列を入力し、この関数の引数とする。
そしてhash関数の戻り値をprintf("%d",hash(key));ととして出力する。
入力：abc　出力：38
出力された値が手計算と一致したことを確認した。
またmain関数内でkeyに何も入れずに引数としてprintf("%d",hash(key));すると
出力：-65
よって空の文字列を引数とした場合、-65が戻り値となって返ってきたことを確認した。
hash関数に空の文字列を入れることはないがこのテストはhash関数がどう動くか確認するために行った。
よってこの関数が正しく動作していると判断した。
*/
int hash(char* p) {
	int h = 0;
	while (*p != 0) {
		h = h + *p;
		p++;
	}
	return h % MAX_HASH;
}
/*
create_item：リストに新しいitemを入れる関数
引数key,p：keyは新しく作るitemの中に入れる文字、pはリストの先頭へのポインタ
テスト：
main関数内に
	item1 = create_item("test1", 0);
	item2 = create_item("test2", list1);
	とする。
itemができているか確認するためにmain関数内で
	printf("%d  %s %d", item1->count, item->word,item1->next);
	printf("%d,%s,%d\n", item2->count, item2->word, item2->next);
	printf("%d\n", item1);
	として出力すると
	1,test1,0
　1,test2,1633698112
　1633698112
となる。まずitem1の各メンバが正しく表示されることを確認する。
次にitem2の各メンバを確認し、nextメンバの値がitem1のアドレスと同じになる。
つまりitem2のnextにitem1へのポインタが入り、itemがつながり、リストとなっていることが
わかる。よってitemが正しく作られたことを確認した。
よってこの関数は正しく動作したと判断した。
*/
struct item* create_item(char* key, struct item* p) {

	struct item* a;
	a = (struct item*)malloc(sizeof(struct item));
	if (a == 0) {
		return 0;
	}
	else {
		a->count = 1;
		a->word = create_string(key);
		a->next = p;
		return a;
	}

}
// 構造体itemから成るリストを表示する関数 
// 引数p：表示したいリストの先頭の構造体itemへのポインタ (0でもよい) 
// 戻り値：なし (void) 
// 注意：引数が0の場合は改行だけする． 
void print_list(struct item* p)
{
	while (p != 0) {
		printf("=><%s,%d>", p->word, p->count);
		p = p->next;
	}
	printf("\n");
}
/*
dump_ht：ハッシュ表の各要素のリストのitemをすべて出力する関数
テスト：
main関数内で
	item1 = create_item("test1", 0);
	item2 = create_item("test2", item1);
	item3 = create_item("test3", item2);
	item4 = create_item("test4", 0);
	item5 = create_item("test5", item4);
	item6 = create_item("test6", 0);
このような3つのリストを作る。
　hashtable[0]=item3;
	hashtable[10] = item5;
	hashtable[20] = item6;
のようにhashtableの添え字が0,10,20にそれぞれのリストの先頭へのポインタを代入する。
その後main関数内でdump_htを呼び、出力すると
=><test3,1>=><test2,1>=><test1,1>
=><test5,1>=><test4,1>
=><test6,1>
と表示された。
リストが入っている要素は表示され、リストが入っていない要素は表示されないことを確認できた。
よってこの関数は正しく動作すると判断した。
*/
void dump_ht(void) {
	int h = 0;
	for (h = 0; h < MAX_HASH; h++) {
		if (hashtable[h] != 0) {
			print_list(hashtable[h]);
		}
	}
}
/*
search_item：リストの中からある単語が入っているitemへのポインタを探す関数
引数：keyは見つけたい単語、pは単語を探すリストへのポインタ
戻り値：探した単語がwordメンバに入っているitemへのポインタ
main関数内で
	item1 = create_item("test1", 0);
	item2 = create_item("test2", item1);
	item3 = create_item("test3", item2);
	item4 = create_item("test4", 0);
	item5 = create_item("test5", item4);
	item6 = create_item("test6", item5);
このような3つのリストを作る。
　hashtable[0]=item3;
	hashtable[10] = item6;
のようにhashtableの添え字が0,10,20にそれぞれのリストの先頭へのポインタを代入する。
引数に探したい単語であるitem1,item2,item3と探すhashtableの要素を引数として、pにsearch_item関数の戻り値を代入し、
そのitem構造体のcountメンバとwordメンバを表示する。
	p = search_item("test1", hashtable[0]);
	printf("%d,%s",p->count,p->word);
	p = search_item("test2", hashtable[0]);
	printf("%d,%s",p->count,p->word);
	p = search_item("test3", hashtable[0]);
	printf("%d,%s",p->count,p->word);
	出力：
	1,test1
　1,test2
　1,test3
 と出力されたため、探した文字列が入っているitemへのポインタが返ってきたことがわかる。
 またリストの中に探そうとしている単語が入っていない場合
  p = search_item("test3", hashtable[10]);
  printf("%d", p);
  出力：
  0
  となるため、戻り値として空のポインタが返ってきたことがわかる。
  これらの確認よりこの関数は正しく動作したと判断した。
*/
struct item* search_item(char* key, struct item* p) {
	while (p != 0) {
		if (strcmp(p->word, key) == 0) {
			return p;
		}
		p = p->next;
	}
	return 0;
}
/*
chainhash：ハッシュ表に単語を登録する関数
引数key：ハッシュ表に登録したい文字列へのポインタ
テスト：
main関数内で文字列を入力し、ハッシュ表をdump_htで表示していく。
	for (int i = 0; i < 5; i++) {
		printf("入力：");
		scanf("%s", buff);
		chainhash(buff);
		printf("ハッシュ表：\n");
		dump_ht();//ハッシュ表を出力
		printf("---------------------------\n");
	}
------------------------------------------------------
入力：a
ハッシュ表：
=><a,1>
---------------------------
入力：b
ハッシュ表：
=><a,1>
=><b,1>
---------------------------
入力：abc
ハッシュ表：
=><abc,1>
=><a,1>
=><b,1>
---------------------------
入力：zzm
ハッシュ表：
=><abc,1>
=><zzm,1>=><a,1>
=><b,1>
---------------------------
入力：mzz
ハッシュ表：
=><abc,1>
=><mzz,1>=><zzm,1>=><a,1>
=><b,1>
------------------------------------------------------
上記より入力された単語がハッシュ表の中に入れられたことが分かった。
また、aとzzmとmzzは同じハッシュ値であるため、hashtableの同じ要素のリストに入れられ、
左側に新しくitemが追加されていることを確認した。
入力：ayumu
ハッシュ表：
=><ayumu,1>
---------------------------
入力：taisi
ハッシュ表：
=><taisi,1>
=><ayumu,1>
---------------------------
入力：ryuuiti
ハッシュ表：
=><taisi,1>
=><ryuuiti,1>
=><ayumu,1>
---------------------------
入力：ayumu
ハッシュ表：
=><taisi,1>
=><ryuuiti,1>
=><ayumu,2>
---------------------------
入力：taisi
ハッシュ表：
=><taisi,2>
=><ryuuiti,1>
=><ayumu,2>
---------------------------
上記より同じ単語を入力したとき、その単語が入っているitemのcountメンバの
値が1増えていることを確認した。
*/
void chainhash(char* key) {
	int h = hash(key);
	struct item* list = hashtable[h], * p;
	p = search_item(key, list);
	if (p != 0) {
		p->count++;
	}
	else {
		hashtable[h] = create_item(key, list);
	}
}
/*
delete_item：削除したい単語がwordメンバに入っているitemをハッシュ表から削除する関数
引数key,p：keyは削除したいitemのwordメンバにある単語、pは削除する単語が入っているリストの先頭へのポインタ
テスト：
①リストの先頭を削除する場合
②リストの末尾を削除する場合
③リストの途中を削除する場合
④同じハッシュ値だがwordメンバにその単語がない場合
⑤hashtableの先頭のリストが空の場合(ハッシュ表に登録してない文字を削除する場合）
を考える。
main関数で
	for (int i = 0; i < 10; i++) {
		printf("入力：");
		scanf("%s", buff);
		chainhash(buff);
		printf("ハッシュ表：\n");
		dump_ht();//ハッシュ表を出力
		printf("---------------------------\n");
	}
としてハッシュ表に登録する。またmain関数内に
	while (1) {
		printf("削除したい文字列：");
		scanf("%99s", buff);//削除する単語を入力
		h = hash(buff);
		hashtable[h] = delete_item(buff, hashtable[h]);
		dump_ht();//削除後のハッシュ表を出力
	}
として削除を何回もできるようにする。
-------------------------------------------------------------------------------------------------------------
入力：a
ハッシュ表：
=><a,1>
---------------------------
入力：b
ハッシュ表：
=><a,1>
=><b,1>
---------------------------
入力：c
ハッシュ表：
=><a,1>
=><b,1>
=><c,1>
---------------------------
入力：mzz
ハッシュ表：
=><mzz,1>=><a,1>
=><b,1>
=><c,1>
---------------------------
入力：zmz
ハッシュ表：
=><zmz,1>=><mzz,1>=><a,1>
=><b,1>
=><c,1>
---------------------------
入力：zzm
ハッシュ表：
=><zzm,1>=><zmz,1>=><mzz,1>=><a,1>
=><b,1>
=><c,1>
---------------------------
入力：tukue
ハッシュ表：
=><tukue,1>
=><zzm,1>=><zmz,1>=><mzz,1>=><a,1>
=><b,1>
=><c,1>
---------------------------
入力：isu
ハッシュ表：
=><tukue,1>
=><isu,1>
=><zzm,1>=><zmz,1>=><mzz,1>=><a,1>
=><b,1>
=><c,1>
---------------------------
入力：ai
ハッシュ表：
=><tukue,1>
=><isu,1>
=><zzm,1>=><zmz,1>=><mzz,1>=><a,1>
=><b,1>
=><c,1>
=><ai,1>
---------------------------
入力：yuujou
ハッシュ表：
=><tukue,1>
=><isu,1>
=><zzm,1>=><zmz,1>=><mzz,1>=><a,1>
=><b,1>
=><c,1>
=><yuujou,1>
=><ai,1>
---------------------------
=><tukue,1>
=><isu,1>
=><zzm,1>=><zmz,1>=><mzz,1>=><a,1>
=><b,1>
=><c,1>
=><yuujou,1>
=><ai,1>
----------------------------------------------------------------------------------ここまでが文字列の登録
削除したい文字列：mzz------------------------------------------------------③の確認
=><tukue,1>
=><isu,1>
=><zzm,1>=><zmz,1>=><a,1>
=><b,1>
=><c,1>
=><yuujou,1>
=><ai,1>
削除したい文字列：a---------------------------------------------------------②の確認
=><tukue,1>
=><isu,1>
=><zzm,1>=><zmz,1>
=><b,1>
=><c,1>
=><yuujou,1>
=><ai,1>
削除したい文字列：zzm------------------------------------------------------①の確認
=><tukue,1>
=><isu,1>
=><zmz,1>
=><b,1>
=><c,1>
=><yuujou,1>
=><ai,1>
削除したい文字列：yuujou---------------------------------------------------①の再確認
=><tukue,1>
=><isu,1>
=><zmz,1>
=><b,1>
=><c,1>
=><ai,1>
-------------------------------------------------------------------------------------------------------------
ここまでで①、②、③の確認をした。
次に④の確認をする。
-------------------------------------------------------------------------------------------------------------
入力：She
ハッシュ表：
=><She,1>
---------------------------
入力：never
ハッシュ表：
=><never,1>=><She,1>
---------------------------
入力：built
ハッシュ表：
=><built,1>=><never,1>=><She,1>
---------------------------
削除したい文字列：bilut--------------------------------------④の確認
=><built,1>=><never,1>=><She,1>
削除したい文字列：reven
=><built,1>=><never,1>=><She,1>
削除したい文字列：ehS
=><built,1>=><never,1>=><She,1>
-------------------------------------------------------------------------------------------------------------
次に⑤の確認をする。
-------------------------------------------------------------------------------------------------------------
入力：abc
ハッシュ表：
=><abc,1>
---------------------------
入力：def
ハッシュ表：
=><abc,1>
=><def,1>
---------------------------
入力：ghi
ハッシュ表：
=><abc,1>
=><def,1>
=><ghi,1>
---------------------------
削除したい文字列：jkl	----------------------------------------⑤の確認
=><abc,1>
=><def,1>
=><ghi,1>
削除したい文字列：mng
=><abc,1>
=><def,1>
=><ghi,1>
-------------------------------------------------------------------------------------------------------------
*/
struct item* delete_item(char* key, struct item* p) {
	struct item* a = p, * b;
	if (p == 0) {
		return 0;
	}
	else if (strcmp(p->word, create_string(key)) == 0) {
		a = p->next;
		free(p);
		return a;
	}
	else {
		while (p != 0) {
			if (p->next != 0) {
				if ((strcmp(p->next->word, create_string(key)) == 0)) {
					b = p->next;
					p->next = p->next->next;
					free(b);
					return a;
				}
			}
			p = p->next;
		}
		return a;
	}
}
int main(void) {
	int h;
	char buff[100];
	FILE* istream;
	istream = fopen("tom.txt", "r");//ファイルの読み込み
	if (istream == 0) {//ファイルが開けなかった時
		printf("can not open");
		return 0;
	}
	for (int i = 0; i < 100; i++) {//20回繰り返す
		fscanf(istream, "%s", buff);//文字列を読み込む
		chainhash(buff);//ハッシュ表へ読み込んだ単語を登録
	}
	dump_ht();//ハッシュ表を出力
	fclose(istream);//ファイルを閉じる
	printf("削除したい文字列：");
	scanf("%99s", buff);//削除する単語を入力
	h = hash(buff);
	hashtable[h] = delete_item(buff, hashtable[h]);
	dump_ht();//削除後のハッシュ表を出力
	return 0;
}
