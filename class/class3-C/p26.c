//cy23263,佐藤歩,6/19,演習6
/*
２つのリストを作り、そのリストを連結したリストを表示した後に元々のリストを表示するプログラム。
テスト：
①連結したリストの表示
1つ目のリストの末尾のセルのvalueの値：3
1つ目のリストの途中のセルのvalueの値：2
1つ目のリストの先頭のセルのvalueの値：1
2つ目のリストの末尾のセルのvalueの値：6
2つ目のリストの途中のセルのvalueの値：5
2つ目のリストの先頭のセルのvalueの値：4
とvalueの値を入力し、
①=>1=>2=>3=>4=>5=>6
と出力された。
①を見ると1つ目の末尾のセルに2つ目の先頭のセルが連結されているため正しい。
*/
#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:6031)

struct cell {//構造体struct cell
	int value;//そのcellに入ってる値
	struct cell* next;//そのcellの次のポインタ
};

//プロトタイプ宣言
struct cell* create_cell(int value, struct cell* next);
struct cell* tail_list(struct cell* list);
void print_list(struct cell* list);
struct cell* concat(struct cell* list1, struct cell* list2);

int main(void) {

	int a;
	struct cell* cell1, * cell2, * cell3, * cell4, * cell5, * cell6;//セルの用意

	//一つ目のリスト
	printf("1つ目のリストの末尾のセルのvalueの値：");
	scanf("%d", &a);
	cell1 = create_cell(a, 0);
	printf("1つ目のリストの途中のセルのvalueの値：");
	scanf("%d", &a);
	cell2 = create_cell(a, cell1);
	printf("1つ目のリストの先頭のセルのvalueの値：");
	scanf("%d", &a);
	cell3 = create_cell(a, cell2);
	//二つ目のリスト
	printf("2つ目のリストの末尾のセルのvalueの値：");
	scanf("%d", &a);
	cell4 = create_cell(a, 0);
	printf("2つ目のリストの途中のセルのvalueの値：");
	scanf("%d", &a);
	cell5 = create_cell(a, cell4);
	printf("2つ目のリストの先頭のセルのvalueの値：");
	scanf("%d", &a);
	cell6 = create_cell(a, cell5);
	//連結したリストを表示
	print_list(concat(cell3, cell6));

	//メモリを解放
	free(cell1);
	free(cell2);
	free(cell3);
	free(cell4);
	free(cell5);
	free(cell6);

	return 0;
}

/*
create_cell：新しいstruct cellの箱を作り、valueに値を代入し、nextに次のcellへのポインタを入れる関数
引数value,next：作った構造体cellのvalueに入れる値1が第1引数value。作った構造体cellのnextにいれる次のcellへのポインタが第2引数next。
戻り値：作ったリストの最初のcellへのポインタ
テスト：
引数：1,0としてmain関数内で作り出したcellをcell1に代入する。
そしてmain関数内でセルができているか確認するために	printf("%d  %d", cell1->value, cell1->next);として
出力：1,0
となったことを確認したためセルが1つ作られたことが分かった。
また、引数：2,cell1としてmain関数内で作り出したcellをcell2に代入する。
そしてmain関数内でセルができているか確認するために	printf("%d  %d %d", cell2->value, cell2->next,cell1);として
出力：2  215308160 215308160
となりcell2のnextにcell1へのポインタが入っていることを確認した。
よってcellのnextに次のcellへのポインタが入っていることが分かった。
これらの確認からcellが正常に作られたことがわかる。
*/
struct cell* create_cell(int value, struct cell* next) {//cellを作る関数

	struct cell* p;

	p = (struct cell*)malloc(sizeof(struct cell));//struct cellのメモリを確保
	if (p == 0) {//メモリが確保できなかった時
		return 0;//戻り値は0
	}
	else {//メモリが確保できた時
		p->value = value;//cellのvalueに引数の値を代入
		p->next = next;//cellのnextに引数のアドレスを代入
		return p;//戻り値は作ったcellのアドレス
	}
}
/*
print_list：リストの各cellのvalueメンバを表示する関数
引数list：表示するリストの最初のcellへのポインタ
テスト：
cell=(value,next)としてcell1=(3,0),cell2=(2,cell1),cell3=(1,cell2)という先頭がcell3であり、cell3へのポインタを引数とする。
main関数内でprint_list(cell3);として実行すると
出力：=>1=>2=>3
と表示されたことを確認したためリストの各cellのvalueメンバを先頭から末尾まで表示することが分かった。
よってこの関数は正しく動作したと判断した。
*/
void print_list(struct cell* list) {//リストの各cellのvalueメンバを表示する関数
	while (list != 0) {//引数listのポインタが0ではない時続ける
		printf("=>%d", list->value);//valueメンバの表示
		list = list->next;//次のcellへ
	}
	printf("\n");//改行
}
/*
tail_list：リストの末尾のcellへのポインタを探す関数
引数list：末尾のcellへのポインタを探すリストの先頭のcellへのポインタ
戻り値：最後のcellへのポインタ
テスト：
cell=(value,next)としてcell1=(3,0),cell2=(2,cell1),cell3=(1,cell2)という先頭がcell3であり、cell3へのポインタを引数とする。
この末尾の値は(3,0)であるため、main関数内にprint("%d %d",tail_list(cell3)->value,tail_list(cell3)->next);として実行すると
出力：3 0
と表示されたことを確認したため戻り値が末尾のcellへのポインタとなったことが分かった。
よってこの関数は正しく動作したと判断した。
*/
struct cell* tail_list(struct cell* list) {//末尾のcellへのポインタを探す関数
	if (list->next == 0) {//nextメンバが0の時
		return list;//そのリストを戻り値とする
	}
	else {//nextメンバが0でない時
		return tail_list(list->next);//戻り値は次のcellを引数にしたtail_listの戻り値
	}
}
struct cell* concat(struct cell* list1, struct cell* list2) {
	tail_list(list1)->next = list2;//list1の末尾のcellのnextメンバにlist2の先頭のcellのアドレスを代入する
	return list1;//戻り値は連結したリスト
}



