/**
 * 作者を検索するプログラム
 * @author Kouki Ando
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
		System.out.print("作者名を入力してください：");
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
			System.out.println("その名前の作者はいません。");
			conn.close();
			throw new SQLException("該当作者なし");
		}

		if (authorIDs.size() == 1) {
			selectedAuthorID = authorIDs.get(0);
			System.out.println("作者ID: " + selectedAuthorID);
		} else {
			System.out.println("同姓同名の作者が複数見つかりました：");
			for (int id : authorIDs) {
				System.out.println("作者ID: " + id);
			}
			while (true) {
				System.out.print("作者IDを選んでください：");
				int input = Integer.parseInt(scanner.nextLine());
				if (authorIDs.contains(input)) {
					selectedAuthorID = input;
					break;
				} else {
					System.out.println("リストにあるIDを選んでください。");
				}
			}
		}
		conn.close();
		st.setInt(1, selectedAuthorID);  // ← 正しい場所に置く
	}

	@Override
	public void showResult(ResultSet r) {
		try {
			if (!r.next()) {
				System.out.println("この作者の作品は登録されていません。");
				return;
			}

			String authorName = r.getString("authorname");
			System.out.println("\n---『" + authorName + "』の執筆作品一覧---\n");

			do {
				String title = r.getString("title");
				String summary = r.getString("summary");
				System.out.println("【タイトル】" + title);
				System.out.println("【概要】" + summary);
				System.out.println("-----------------------------");
			} while (r.next());

		} catch (SQLException se) {
			System.out.println("エラー: " + se.toString());
		}
	}

}
