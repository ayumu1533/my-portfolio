/**
 * 作品お気に入り登録
 * @author 本多 若菜
 */

import java.sql.*;
import java.util.Scanner;

public class AddFavoritWorks extends AbstractExecuter2 {
    private Scanner scanner = new Scanner(System.in);
    private int userID;
    private String title;
    private int workID;

    @Override
    public String getSQLtemplate() {
        return "INSERT INTO work_favorite_table VALUES (?, ?)";
    }

    @Override
    public void preQuery() {
        try {
            System.out.print("ユーザーIDを入力してください: ");
            userID = Integer.parseInt(scanner.nextLine());

            System.out.print("お気に入り登録をする作品名を入力してください: ");
            title = scanner.nextLine();

            workID = getWorkID(title); // ここでIDも取得

        } catch (NumberFormatException e) {
            System.out.println("ユーザーIDは数値で入力してください。");
            throw new RuntimeException("入力エラー: " + e.getMessage());
        } catch (Exception e) {
            System.out.println("入力内容に誤りがあります: " + e.getMessage());
            throw new RuntimeException("前処理エラー: " + e.getMessage());
        }
    }

    @Override
    public void setQuery(PreparedStatement st) throws SQLException {
        st.setInt(1, userID);
        st.setInt(2, workID);
    }

    @Override
    public String checkIDSQL() {
        return "SELECT * FROM work_favorite_table WHERE userID = ? AND workID = ?";
    }

    @Override
    public void setExistQuery(PreparedStatement st) throws SQLException {
        st.setInt(1, userID);
        st.setInt(2, workID);
    }

    private int getWorkID(String title) throws Exception {
        Connection conn = DriverManager.getConnection(
            "jdbc:mysql://localhost/mangareviews?useSSL=false&characterEncoding=utf8&useServerPrepStmts=true",
            "root", ""
        );

        PreparedStatement st = conn.prepareStatement("SELECT workID FROM work_table WHERE title = ?");
        st.setString(1, title);
        ResultSet rs = st.executeQuery();

        if (rs.next()) {
            int id = rs.getInt("workID");
            rs.close(); st.close(); conn.close();
            return id;
        } else {
            rs.close(); st.close(); conn.close();
            throw new Exception("指定された作品は見つかりません。");
        }
    }

    @Override
    public void showResult(int affectedRows) {
        if (affectedRows > 0) {
            System.out.println("お気に入り登録が成功しました。");
        } else {
            System.out.println("お気に入り登録に失敗しました。");
        }
    }
}
