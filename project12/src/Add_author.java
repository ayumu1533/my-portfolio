/**
 * 作者を登録するプログラム
 * @author Kouki Ando
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
				authorID = rs.getInt(1) + 1;//ここで1を足す処理
			} else {
				authorID = 1; // テーブルが空なら1
			}
			System.out.println("自動割り当てされた作者ID: " + authorID);
			System.out.print("作者名を入力してください: ");
			authorName = line.nextLine();

		} catch (SQLException e) {
			System.out.println("データベースエラー: " + e.getMessage());
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
			System.out.println("作者登録が成功しました。");
		} else {
			System.out.println("作者登録に失敗しました。");
		}
	}
}
