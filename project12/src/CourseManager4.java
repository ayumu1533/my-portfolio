/**
 *  漫画管理アプリケーションの本体となるクラス
 * @author Ayumu Sato
 */

import java.util.*;
import java.sql.*;

public class CourseManager4 {
    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        // 各機能クラスのインスタンス作成
        AbstractExecuter2 e1 = new MangaReviewManager();
        MangaSearch ms = new MangaSearch();
        AbstractExecuter2 e3 = new AddFavoritWorks();
        AbstractExecuter e4 = new Search_author();
        AbstractExecuter2 e5 = new Add_author_favorites();
        MangaRatingExecuter e6 = new MangaRatingExecuter();
        AbstractExecuter e7 = new Genre_search();
        AbstractExecuter e8 = new View_favorite_work();
        AbstractExecuter e9 = new View_favorite_author();
        AbstractExecuter2 e10 = new Add_author();

        while (true) {
            System.out.println("\n=== 漫画レビュー管理システム ===");
            System.out.println("1: ログイン");
            System.out.println("2: 新規ユーザー登録");
            System.out.println("0: 終了");
            System.out.print("番号を入力してください: ");
            String initialChoice = scanner.nextLine();

            if (initialChoice.equals("1")) {
                UserLogin userLogin = new UserLogin(); // Scanner渡すように変更
                int loginResult = userLogin.login();

                if (loginResult == 0) {
                    System.out.println(">> 管理者用メニューへようこそ。");
                    while (true) {
                        System.out.println("\n=== 管理者メニュー ===");
                        System.out.println("1: 作者登録");
                        System.out.println("2: 作品登録");
                        System.out.println("0: ログアウトして初期画面へ戻る");
                        System.out.print("番号を入力してください: ");
                        String adminChoice = scanner.nextLine();

                        switch (adminChoice) {
                            case "1":
                                Add_author addAuthor = new Add_author();
                                addAuthor.InsertAndShow();
                                break;
                            case "2":
                                Add_work addWork = new Add_work();
                                addWork.InsertAndShow();
                                break;
                            case "0":
                                System.out.println("管理者をログアウトして初期画面に戻ります。");
                                break;
                            default:
                                System.out.println("無効な入力です。もう一度入力してください。");
                                continue;
                        }

                        if (adminChoice.equals("0")) {
                            break;  // 管理者メニュー抜けて初期画面へ戻る
                        }
                    }
                } else if (loginResult > 0) {
                    System.out.println(">> ようこそ、ユーザーID: " + loginResult + "さん。");
                    // メインメニューに移行
                    mainMenu(scanner, e1, ms, e3, e4, e5, e6, e7, e8, e9, e10);
                    break;
                } else {
                    System.out.println(">> ログインに失敗しました。");
                }

            } else if (initialChoice.equals("2")) {
                AbstractExecuter2 userAdder = new Add_user();
                userAdder.InsertAndShow();
            } else if (initialChoice.equals("0")) {
                System.out.println("アプリケーションを終了します。");
                break;
            } else {
                System.out.println("無効な入力です。");
            }
        }

        scanner.close();
    }

    // メインメニュー処理を関数化
    public static void mainMenu(Scanner scanner,
                                AbstractExecuter2 e1,
                                MangaSearch ms,
                                AbstractExecuter2 e3,
                                AbstractExecuter e4,
                                AbstractExecuter2 e5,
                                MangaRatingExecuter e6,
                                AbstractExecuter e7,
                                AbstractExecuter e8,
                                AbstractExecuter e9,
                                AbstractExecuter2 e10) {
        int judge = 0;

        while (judge == 0) {
            System.out.println("\n=== メインメニュー ===");
            System.out.println("1: レビュー投稿");
            System.out.println("2: 検索機能");
            System.out.println("3: 登録機能");
            System.out.println("4: 表示・参照機能");
            System.out.println("5: 終了");
            System.out.print("メニュー番号を入力してください: ");
            String mainMenu = scanner.nextLine();

            switch (mainMenu) {
                case "1":
                    while (true) {
                        System.out.println("\n===[レビュー投稿]===");
                        System.out.println("1: レビューを投稿する");
                        System.out.println("0: メインメニューに戻る");
                        System.out.print("番号を選んでください: ");
                        String reviewMenu = scanner.nextLine();
                        switch (reviewMenu) {
                            case "1": e1.InsertAndShow(); break;
                            case "0": System.out.println("メインメニューに戻ります。"); break;
                            default: System.out.println("不正な入力です。"); continue;
                        }
                        if (reviewMenu.equals("0")) break;
                    }
                    break;

                case "2":
                    while (true) {
                        System.out.println("\n===[検索メニュー]===");
                        System.out.println("1: 漫画を検索する");
                        System.out.println("2: 作者を検索する");
                        System.out.println("3: ジャンルから作品を探す");
                        System.out.println("0: メインメニューに戻る");
                        System.out.print("番号を選んでください: ");
                        String searchMenu = scanner.nextLine();
                        switch (searchMenu) {
                            case "1": ms.queryAndShow(); break;
                            case "2": e4.queryAndShow(); break;
                            case "3": e7.queryAndShow(); break;
                            case "0": System.out.println("メインメニューに戻ります。"); break;
                            default: System.out.println("不正な入力です。"); continue;
                        }
                        if (searchMenu.equals("0")) break;
                    }
                    break;

                case "3":
                    while (true) {
                        System.out.println("\n===[登録メニュー]===");
                        System.out.println("1: 作品お気に入り登録");
                        System.out.println("2: 作者お気に入り登録");
                        System.out.println("0: メインメニューに戻る");
                        System.out.print("番号を選んでください: ");
                        String registerMenu = scanner.nextLine();
                        switch (registerMenu) {
                            case "1": e3.InsertAndShow(); break;
                            case "2": e5.InsertAndShow(); break;
                            case "0": System.out.println("メインメニューに戻ります。"); break;
                            default: System.out.println("不正な入力です。"); continue;
                        }
                        if (registerMenu.equals("0")) break;
                    }
                    break;

                case "4":
                    while (true) {
                        System.out.println("\n===[表示・参照メニュー]===");
                        System.out.println("1: ランキングを表示");
                        System.out.println("2: お気に入り作品を表示");
                        System.out.println("3: お気に入り作者を表示");
                        System.out.println("0: メインメニューに戻る");
                        System.out.print("番号を選んでください: ");
                        String viewMenu = scanner.nextLine();
                        switch (viewMenu) {
                            case "1": e6.queryAndShow(); break;
                            case "2": e8.queryAndShow(); break;
                            case "3": e9.queryAndShow(); break;
                            case "0": System.out.println("メインメニューに戻ります。"); break;
                            default: System.out.println("不正な入力です。"); continue;
                        }
                        if (viewMenu.equals("0")) break;
                    }
                    break;

                case "5":
                    System.out.println("アプリケーションを終了します。");
                    judge = 1;
                    break;

                default:
                    System.out.println("不正な番号です。");
            }
        }
    }
}
