/**
 * 漫画のレビュー投稿に責任を持つクラス
 * @author Taishi Nishimuras 
 */


import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.util.Scanner;

public class MangaReviewManager extends AbstractExecuter2 {

    private int rating;
    private String content;
    private String userNickname;
    private String workTitle;
    private Integer userId;
    private Integer workId;
    private int reviewId;

    @Override
    public void preQuery() {
        Scanner sc = new Scanner(System.in);
        System.out.print("レビュー対象の作品名を入力してください > ");
        this.workTitle = sc.nextLine();
        System.out.print("あなたのニックネームを入力してください > ");
        this.userNickname = sc.nextLine();
        System.out.print("評価（1-5）を入力してください > ");
        this.rating = Integer.parseInt(sc.nextLine());
        System.out.print("レビュー内容を入力してください > ");
        this.content = sc.nextLine();

        try (Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost/mangareviews?useSSL=false&characterEncoding=utf8&useServerPrepStmts=true",
                "root", "")) {

            try (PreparedStatement pstmt = conn.prepareStatement("SELECT MAX(reviewID) FROM review_table")) {
                ResultSet rs = pstmt.executeQuery();
                if (rs.next()) {
                    // テーブルが空の場合、MAX()は0を返すことがあるので、その場合は1から始める
                    this.reviewId = rs.getInt(1) + 1;
                } else {
                    // 結果セットが空（テーブルが完全に空）の場合も1から
                    this.reviewId = 1;
                }
            }

            this.userId = findId(conn, "SELECT userID FROM user_table WHERE nickname = ?", this.userNickname);
            if (this.userId == null) {
                throw new RuntimeException("エラー: ユーザー「" + this.userNickname + "」が見つかりません。");
            }

            this.workId = findId(conn, "SELECT workID FROM work_table WHERE title = ?", this.workTitle);
            if (this.workId == null) {
                throw new RuntimeException("エラー: 作品「" + this.workTitle + "」が見つかりません。");
            }

        } catch (SQLException e) {
            throw new RuntimeException("データベース検索中にエラーが発生しました。", e);
        }
    }

    @Override
    public String getSQLtemplate() {
        return "INSERT INTO review_table(reviewID, rating, reviewarticle, Posting, userID, workID) VALUES (?, ?, ?, ?, ?, ?)";
    }

    @Override
    public void setQuery(PreparedStatement st) throws SQLException {
        st.setInt(1, this.reviewId);
        st.setInt(2, this.rating);
        st.setString(3, this.content);
        st.setTimestamp(4, Timestamp.valueOf(LocalDateTime.now()));
        st.setInt(5, this.userId);
        st.setInt(6, this.workId);
    }

    @Override
    public void showResult(int affectedRows) {
        if (affectedRows > 0) {
            System.out.println("レビューをデータベースに正常に投稿しました！ (ID: " + this.reviewId + ")");
        } else {
            System.out.println("レビューの投稿に失敗しました。");
        }
    }

    private Integer findId(Connection conn, String sql, String parameter) throws SQLException {
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, parameter);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1);
                }
            }
        }
        return null;
    }

    //　以下はmain文での実行の仕方

    // public static void main(String[] args) {
    //     MangaReviewManager manager = new MangaReviewManager();
    //     manager.InsertAndShow();
    // }
}