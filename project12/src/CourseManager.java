/**
 * 漫画管理アプリケーションの本体となるクラス
 * @author kouki Ando
 
 */

import java.util.*;
import java.sql.*;

public class CourseManager {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);

		//未実装AbstractExecuter e1 = new Post_review();
        //水曜日に話してから追加します。AbstractExecuter e3 = new AddFavoritWorks();
		AbstractExecuter e4 = new Search_author();
        AbstractExecuter2 e5 = new Add_author_favorites();
		AbstractExecuter e6 = new MangaRatingExecuter();
        AbstractExecuter e7 = new Genre_search();
		AbstractExecuter e8 = new View_favorite_work();
        AbstractExecuter e9 = new View_favorite_author();
		System.out.println("=== コース管理システム ===");
		System.out.println("メニューを選んでください: ");
        System.out.println("1: 漫画レビュー投稿(作品名指定)");
		System.out.println("2: 〇漫画検索(作品名指定)");
        System.out.println("3: △作品お気に入り登録(ユーザーID+作品名指定)");
		System.out.println("4: 〇作者検索(作者名指定)");
        System.out.println("5: 〇作者お気に入り登録(ユーザーID+作者名指定)");
        System.out.println("6: 〇ランキング表示()");
        System.out.println("7: 〇ジャンル検索(ジャンル名指定)歩夢君");
        System.out.println("8: 〇お気に入り作品表示()歩夢君");
        System.out.println("9: 〇お気に入り作者表示()歩夢君");
		System.out.println("メニュー番号を入力してください: ");
		String line = scanner.nextLine();
		switch(line) {
			case "2":
				MangaSearch ms = new MangaSearch();
				ms.queryAndShow();
				break;
			case "4":
				e4.queryAndShow();
				break;
            case "5":
				e5.InsertAndShow();
				break;
			case "6":
				e6.queryAndShow();
				break;
            case "7":
				e7.queryAndShow();
				break;
			case "8":
				e8.queryAndShow();
				break;
            case "9":
				e9.queryAndShow();
				break;
			default:
				System.out.println("Incorrect number");
		}
	}
}
