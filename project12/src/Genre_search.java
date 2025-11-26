/**
 * ジャンルの検索に責任を持つクラス
 * @author Ayumu Sato
 */

import java.util.*;
import java.sql.*;

public class Genre_search extends AbstractExecuter {
	private Scanner scanner = new Scanner(System.in);
	private String genreName;

	public String getSQLtemplate() {
		return "SELECT work_table.workID,work_table.title,work_table.summary"
			+ " FROM genre_table,affiliation_table,work_table"
			+ " WHERE genre_table.genrename=?"
			+ " AND genre_table.genreID=affiliation_table.genreID"
			+ " AND affiliation_table.workID=work_table.workID;";
			
	}

	public void setQuery(PreparedStatement st) throws SQLException {
		System.out.println("ジャンル名を入力してください:");

		genreName = scanner.nextLine();
		// 本来はここで入力された文字列が不正なものでないか検査した方が良い

		st.setString(1, genreName); // ここでSQLの ? の場所に値を埋め込んでいる
	}

	public void showResult(ResultSet r) {
		try {
			System.out.println("\n---" +genreName+ "のカテゴリの作品一覧---\n");
			while(r.next()) {
				System.out.println(
						"【作品ID】"+r.getString("workID")+"\t"+
						"【タイトル】"+r.getString("title")+"\n"+
						"【要約】"+r.getString("summary")+
						"\n----------------------------------\n");
			}
		} catch (SQLException se) {
			System.out.println("SQL Error 2phss: " + se.toString() + " "
				+ se.getErrorCode() + " " + se.getSQLState());
		} catch (Exception e) {
			System.out.println("Error: " + e.toString() + e.getMessage());
		}
	}
}
