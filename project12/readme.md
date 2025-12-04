# Project 12: データベース連携 漫画レビューアプリケーション (Java/JDBC)

# チームNATSUKO　メンバーリスト

- A.K

- 佐藤　歩

- W.H　

- T.N

### 担当者様に見ていただきたいファイル

- [最終発表資料](./チーム3発表資料.pdf)

## 1. 概要と目的

このプロジェクトは、Javaにおけるデータベース接続（JDBC）の習得と、オブジェクト指向プログラミング（OOP）における抽象化の概念を実践するために開発したコンソールベースの漫画データ管理システムです。

主に、CRUD操作（Create, Read, Update, Deleteの基本操作）のうち、検索（Read/Query）と挿入（Create/Insert）の処理を、役割ごとに抽象化し、構造的なコード設計を実現しました。

* **開発言語:** Java
* **データベース:** MySQL (JDBC)
* **主な技術要素:** 抽象クラス、ポリモーフィズム、Prepared Statement、テーブル結合（JOIN）

## 2. ファイル構造

<pre>
project12/ 
├── src/ 
│ ├── CourseManager4.java         // メイン実行クラス（ログイン・メニュー管理）
│ ├── AbstractExecuter.java       // 検索(SELECT)用 抽象クラス 
│ ├── AbstractExecuter2.java      // 挿入(INSERT)用 抽象クラス（ID重複チェック機能付き） 
│ ├── UserLogin.java              // ユーザーログイン処理
│ ├── MangaReviewManager.java     // 漫画レビュー投稿処理
│ ├── MangaSearch.java            // 漫画作品の総合検索クラス 
│ ├── MangaDetailSearch.java      // 漫画詳細情報検索 
│ ├── MangaReviewSearch.java      // 漫画レビュー検索 
│ ├── Genre_search.java           // ジャンル検索 
│ ├── MangaRatingExecuter.java    // 平均評価ランキング表示 
│ ├── Search_author.java          // 作者検索・作品一覧表示 
│ ├── Add_user.java               // 新規ユーザー登録
│ ├── Add_author.java             // 新規作者登録 
│ ├── Add_work.java               // 新規作品登録
│ ├── Add_writing.java            // 作品情報登録
│ ├── AddFavoritWorks.java        // お気に入り作品登録 
│ ├── Add_author_favorites.java   // お気に入り作者登録 
│ ├── View_favorite_work.java     // お気に入り作品表示 
│ └── View_favorite_author.java   // お気に入り作者表示 
├── class/                        // ビルドされた .class ファイル群 
└── MangaReviews.sql              // データベースのスキーマ定義と初期データ
</pre>

## 3. 実行環境と手順

### (1) データベースの準備

1.  **MySQL**を起動します。
2.  mysqlクライアント(bin/mysql)を実行して、インポート先のDBを作っておく。
3. 一度mysqlクライアントを終了し、再度mysqlクライアントを以下のように実行する。
`"bin/mysql" -u root -h localhost <DB名> < MangaReviews.sql`

### (2) 実行

1.  src内の.javaファイルをコンパイルします。（例: `javac -encoding Windows-31J -d class src/*.java`）
2.  CourseManager4.javaをメインクラスとして実行します。（例: `java -cp "...\mysql-8.4.5-winx64\mysql-connector-j-9.3.0.jar;class" CourseManager4`）
3.  コンソールに表示されるメニュー番号（1〜11）を入力して、各機能を実行します。