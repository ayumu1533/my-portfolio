/**
 * 漫画の詳細検索に責任を持つクラス
 * @author 本多 若菜
 */

import java.sql.*;

public class MangaDetailSearch extends AbstractExecuter {
	private String title;

    public MangaDetailSearch(String title) {
        this.title = title;
    }

	public String getSQLtemplate() {
		return "SELECT title, authorname, summary, publishername" + 
                " FROM work_table, author_table, writing_table, publication_table, publisher_table" + 
                " WHERE writing_table.authorID=author_table.authorID" + 
                " AND writing_table.workID=work_table.workID" + 
                " AND publication_table.workID = work_table.workID" + 
                " AND publication_table.publisherID = publisher_table.publisherID" +
                " AND work_table.title=?;";
	}

	public void setQuery(PreparedStatement st) throws SQLException {
		st.setString(1, title); // ここでSQLの ? の場所に値を埋め込んでいる
	}

	public void showResult(ResultSet r) {
		try {
			while(r.next()) {
				System.out.println("タイトル："+
                    r.getString("title")+
                    "\n" + "作者："+ r.getString("authorname") + 
                    "\n" + "出版社："+ r.getString("publishername") + 
                    "\n" + "概要："+ r.getString("summary"));
			}
		} catch (SQLException se) {
			System.out.println("SQL Error 2phss: " + se.toString() + " "
				+ se.getErrorCode() + " " + se.getSQLState());
		} catch (Exception e) {
			System.out.println("Error: " + e.toString() + e.getMessage());
		}
	}
}
