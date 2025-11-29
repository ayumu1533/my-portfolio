/**
 * –Ÿ‰æ‚ÌÚ×ŒŸõ‚ÉÓ”C‚ğ‚ÂƒNƒ‰ƒX
 * @author honda wakana
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
		st.setString(1, title); // ‚±‚±‚ÅSQL‚Ì ? ‚ÌêŠ‚É’l‚ğ–„‚ß‚ñ‚Å‚¢‚é
	}

	public void showResult(ResultSet r) {
		try {
			while(r.next()) {
				System.out.println("\nyƒ^ƒCƒgƒ‹z"+
                    r.getString("title")+
                    "\t" + "yìÒz"+ r.getString("authorname") + 
                    "\t" + "yo”ÅĞz"+ r.getString("publishername") + 
                    "\n" + "yŠT—vz"+ r.getString("summary"));
			}
		} catch (SQLException se) {
			System.out.println("SQL Error 2phss: " + se.toString() + " "
				+ se.getErrorCode() + " " + se.getSQLState());
		} catch (Exception e) {
			System.out.println("Error: " + e.toString() + e.getMessage());
		}
	}
}
