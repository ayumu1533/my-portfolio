/**
 * 漫画管理アプリケーションの本体となるクラス
 * @author kouki Ando
 
 */

import java.util.*;
import java.sql.*;

public class CourseManager2 {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);

		int judge = 0;
		//未実装AbstractExecuter e1 = new Post_review();
        AbstractExecuter2 e3 = new AddFavoritWorks();
		AbstractExecuter e4 = new Search_author();
        AbstractExecuter2 e5 = new Add_author_favorites();
		MangaRatingExecuter e6 = new MangaRatingExecuter();
        AbstractExecuter e7 = new Genre_search();
		AbstractExecuter e8 = new View_favorite_work();
        AbstractExecuter e9 = new View_favorite_author();
		AbstractExecuter2 e10 = new Add_author();
		while(judge == 0){
			System.out.println("=== コース管理システム ===");
			System.out.println("メニューを選んでください: ");
			System.out.println("1: 漫画レビュー投稿(作品名指定)");
			System.out.println("2: 漫画検索(作品名指定)");
			System.out.println("3: 作品お気に入り登録(ユーザーID+作品名指定)");
			System.out.println("4: 作者検索(作者名指定)");
			System.out.println("5: 作者お気に入り登録(ユーザーID+作者名指定)");
			System.out.println("6: ランキング表示()");
			System.out.println("7: ジャンル検索(ジャンル名指定)");
			System.out.println("8: お気に入り作品表示()");
			System.out.println("9: お気に入り作者表示()");
			System.out.println("10:新規作者登録");
			System.out.println("11:終了");
			System.out.println("メニュー番号を入力してください: ");
			String line = scanner.nextLine();
			switch(line) {
				case "2":
					MangaSearch ms = new MangaSearch();
					ms.queryAndShow();
					break;
				case "3":
					e3.InsertAndShow();
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
				case "10":
					e10.InsertAndShow();
					break;
				case "11":
					judge = 1;
					break;
				default:
					System.out.println("Incorrect number");
			}
		}
	}
}
