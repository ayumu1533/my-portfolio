/**
 * 漫画ランキングを表示するプログラム
 * @author Kouki Ando
 */

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

/**
 * 漫画の作品ごとの平均評価点を算出し、評価の高い順に表示するクラス
 * @author Taishi Nishimura
 */
public class MangaRatingExecuter extends AbstractExecuter {
    @Override
    public String getSQLtemplate() {
        return "SELECT title, AVG(rating) " +
               "FROM review_table " +
               "INNER JOIN work_table ON work_table.workID = review_table.workID " +
               "GROUP BY title " +
               "ORDER BY AVG(rating) DESC;";
    }

    // /**
    //  * PreparedStatementに値をセットします。
    //  * 今回のSQLにはパラメータがないため、このメソッドは空になります。
    //  * @param st PreparedStatementオブジェクト
    //  * @throws SQLException
    //  */
    @Override
    public void setQuery(PreparedStatement st) throws SQLException {
         // このクエリには '?' のようなパラメータは不要なため、処理はありません。
    }

    public void showResult(ResultSet r) {
        System.out.println("\n--- 漫画作品 平均評価ランキング ---\n");
        try {
            while (r.next()) {
                String title = r.getString("title");
                double avgRating = r.getDouble("AVG(rating)");
                System.out.printf("【作品名】 %s%n【平均評価】 %.2f%n", title, avgRating);
                System.out.println("----------------------------------");
            }
        } catch (SQLException e) {
            System.out.println("結果の表示中にSQLエラーが発生しました: " + e.toString());
        }
    }

    public static void main(String[] args) {
        MangaRatingExecuter executer = new MangaRatingExecuter();
        // 抽象クラスに定義された、処理の本体となるメソッドを呼び出します。
        executer.queryAndShow();
    }
}