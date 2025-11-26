/**
 * ��҂���������v���O����
 * @author K.A
 */
import java.sql.*;
import java.util.*;

public class Search_author extends AbstractExecuter {
	private Scanner scanner = new Scanner(System.in);
	private int selectedAuthorID = -1;

	@Override
public String getSQLtemplate() {
	return "SELECT w.title, w.summary, a.authorname " +
	       "FROM work_table w " +
	       "JOIN writing_table wt ON w.workID = wt.workID " +
	       "JOIN author_table a ON wt.authorID = a.authorID " +
	       "WHERE a.authorID = ?";
	}

	@Override
	public void setQuery(PreparedStatement st) throws SQLException {
		System.out.print("��Җ�����͂��Ă��������F");
		String inputName = scanner.nextLine().trim();

		Connection conn = DriverManager.getConnection(
			"jdbc:mysql://localhost/mangareviews?useSSL=false&characterEncoding=utf8&useServerPrepStmts=true",
			"root", ""
		);
		PreparedStatement stAuthors = conn.prepareStatement(
			"SELECT authorID FROM author_table WHERE authorname = ?"
		);
		stAuthors.setString(1, inputName);

		ResultSet rs = stAuthors.executeQuery();

		List<Integer> authorIDs = new ArrayList<>();
		while (rs.next()) {
			authorIDs.add(rs.getInt("authorID"));
		}

		rs.close();
		stAuthors.close();

		if (authorIDs.isEmpty()) {
			System.out.println("���̖��O�̍�҂͂��܂���B");
			conn.close();
			throw new SQLException("�Y����҂Ȃ�");
		}

		if (authorIDs.size() == 1) {
			selectedAuthorID = authorIDs.get(0);
			System.out.println("���ID: " + selectedAuthorID);
		} else {
			System.out.println("���������̍�҂�����������܂����F");
			for (int id : authorIDs) {
				System.out.println("���ID: " + id);
			}
			while (true) {
				System.out.print("���ID��I��ł��������F");
				int input = Integer.parseInt(scanner.nextLine());
				if (authorIDs.contains(input)) {
					selectedAuthorID = input;
					break;
				} else {
					System.out.println("���X�g�ɂ���ID��I��ł��������B");
				}
			}
		}
		conn.close();
		st.setInt(1, selectedAuthorID);  // �� �������ꏊ�ɒu��
	}

	@Override
	public void showResult(ResultSet r) {
		try {
			if (!r.next()) {
				System.out.println("���̍�҂̍�i�͓o�^����Ă��܂���B");
				return;
			}

			String authorName = r.getString("authorname");
			System.out.println("\n---�w" + authorName + "�x�̎��M��i�ꗗ---\n");

			do {
				String title = r.getString("title");
				String summary = r.getString("summary");
				System.out.println("�y�^�C�g���z" + title);
				System.out.println("�y�T�v�z" + summary);
				System.out.println("-----------------------------");
			} while (r.next());

		} catch (SQLException se) {
			System.out.println("�G���[: " + se.toString());
		}
	}

}
