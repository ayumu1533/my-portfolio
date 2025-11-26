/**
 * お気に入り作品の検索に責任を持つクラス
 * @author Ayumu Sato
 */

import java.util.*;
import java.sql.*;

public class View_favorite_work extends AbstractExecuter {
	private Scanner scanner = new Scanner(System.in);

	public String getSQLtemplate() {
		return "SELECT work_table.workID,work_table.title,work_table.summary"
			+ " FROM work_favorite_table,user_table,work_table"
			+ " WHERE user_table.userID=?"
			+ " AND user_table.userID=work_favorite_table.userID"
			+ " AND work_favorite_table.workID=work_table.workID;";
	}

	public void setQuery(PreparedStatement st) throws SQLException {
		System.out.println("自分のユーザーネームを入れてください");

		int userID = Integer.parseInt(scanner.nextLine());
		// 本来はここで入力された文字列が不正なものでないか検査した方が良い

		st.setInt(1, userID); // ここでSQLの ? の場所に値を埋め込んでいる
	}

	public void showResult(ResultSet r) {
		try {
			while(r.next()) {
				System.out.println(
						"【作品ID】"+r.getInt("workID")+"\t"+
						"【タイトル】"+r.getString("title")+"\t"+
						"【要約】"+r.getString("summary"));
			}

		} catch (SQLException se) {
			System.out.println("SQL Error 2phss: " + se.toString() + " "
				+ se.getErrorCode() + " " + se.getSQLState());
		} catch (Exception e) {
			System.out.println("Error: " + e.toString() + e.getMessage());
		}
	}
}
