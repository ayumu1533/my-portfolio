/**
 * ����̏ڍ׌����ɐӔC�����N���X
 * @author h.w
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
		st.setString(1, title); // ������SQL�� ? �̏ꏊ�ɒl�𖄂ߍ���ł���
	}

	public void showResult(ResultSet r) {
		try {
			while(r.next()) {
				System.out.println("\n�y�^�C�g���z"+
                    r.getString("title")+
                    "\t" + "�y��ҁz"+ r.getString("authorname") + 
                    "\t" + "�y�o�ŎЁz"+ r.getString("publishername") + 
                    "\n" + "�y�T�v�z"+ r.getString("summary"));
			}
		} catch (SQLException se) {
			System.out.println("SQL Error 2phss: " + se.toString() + " "
				+ se.getErrorCode() + " " + se.getSQLState());
		} catch (Exception e) {
			System.out.println("Error: " + e.toString() + e.getMessage());
		}
	}
}
