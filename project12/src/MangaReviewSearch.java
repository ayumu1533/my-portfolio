/**
 * 漫画のレビュー検索に責任を持つクラス
 * @author 本多 若菜
 */

import java.sql.*;

public class MangaReviewSearch extends AbstractExecuter {
    private String title;

    public MangaReviewSearch(String title) {
        this.title = title;
    }

	public String getSQLtemplate() {
		return "SELECT reviewarticle" + 
                " FROM work_table, review_table" +
                " WHERE work_table.workID=review_table.workID" + 
                " AND work_table.title = ?;";
	}

	public void setQuery(PreparedStatement st) throws SQLException {
		st.setString(1, title); // ここでSQLの ? の場所に値を埋め込んでいる
	}

	public void showResult(ResultSet r) {
		try {
			System.out.println("\n【『"+title+"』に対するレビュー】");
			while(r.next()) {
				System.out.println(
                    r.getString("reviewarticle"));
			}
		} catch (SQLException se) {
			System.out.println("SQL Error 2phss: " + se.toString() + " "
				+ se.getErrorCode() + " " + se.getSQLState());
		} catch (Exception e) {
			System.out.println("Error: " + e.toString() + e.getMessage());
		}
	}
}
