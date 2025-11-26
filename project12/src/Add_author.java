/**
 * ��҂�o�^����v���O����
 * @author Ayumu Sato
 */
import java.sql.*;
import java.util.Scanner;

public class Add_author extends AbstractExecuter2 {
	private int authorID;
	private String authorName;

	@Override
	public void preQuery() {
		Scanner line = new Scanner(System.in);
		try (
			Connection con = DriverManager.getConnection(
				"jdbc:mysql://localhost/mangareviews?useSSL=false&characterEncoding=utf8&useServerPrepStmts=true",
				"root", ""
			);
			Statement stmt = con.createStatement();
			ResultSet rs = stmt.executeQuery("SELECT MAX(authorID) FROM author_table")
		) {
			if (rs.next()) {
				authorID = rs.getInt(1) + 1;//������1�𑫂�����
			} else {
				authorID = 1; // �e�[�u������Ȃ�1
			}
			System.out.println("�������蓖�Ă��ꂽ���ID: " + authorID);
			System.out.print("��Җ�����͂��Ă�������: ");
			authorName = line.nextLine();

		} catch (SQLException e) {
			System.out.println("�f�[�^�x�[�X�G���[: " + e.getMessage());
		}
	}

	@Override
	public String getSQLtemplate() {
		return "INSERT INTO author_table(authorID, authorname) VALUES (?, ?)";
	}

	@Override
	public void setQuery(PreparedStatement st) throws SQLException {
		st.setInt(1, authorID);
		st.setString(2, authorName);
	}

	@Override
	public void showResult(int affectedRows) {
		if (affectedRows > 0) {
			System.out.println("��ғo�^���������܂����B");
		} else {
			System.out.println("��ғo�^�Ɏ��s���܂����B");
		}
	}
}
