/**
 * 作品お気に入り登録
 * @author 本多 若菜
 */

import java.sql.*;
import java.util.Scanner;

public class AddFavoritWorks extends AbstractExecuter2 {
   	private Scanner scanner = new Scanner(System.in);

	public String getSQLtemplate() {
		return "INSERT INTO work_favorite_table"
				+ " VALUES (?, ?)";
	}

	public void setQuery(PreparedStatement st) throws SQLException {
    	System.out.println("ユーザーIDを入力してください:");
    	int userID = Integer.parseInt(scanner.nextLine());
    	System.out.println("お気に入り登録をする作品名を入力してください:");
    	String title = scanner.nextLine();
    	st.setInt(1, userID);
    	try {
        	int workID = getWorkID(title);
        	st.setInt(2, workID);
    	} catch (Exception e) {
        	throw new SQLException("作品IDの取得に失敗しました: " + e.getMessage());
    	}
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
            throw new Exception("作品が見つかりません。");
        }
    }

	public void showResult(int affectedRows) {
		if (affectedRows > 0) {
			System.out.println("お気に入り登録が成功しました。");
		} else {
			System.out.println("お気に入り登録に失敗しました。");
		}
	}
}
