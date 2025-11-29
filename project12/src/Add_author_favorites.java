/**
 * お気に入り作者を登録するプログラム
 * @author Kouki Ando
 */
import java.sql.*;
import java.util.Scanner;

public class Add_author_favorites extends AbstractExecuter2 {
	private int userID;
	private int authorID;

	@Override
	public void preQuery() {
		Scanner lane = new Scanner(System.in);
		try {
			System.out.print("ユーザーIDを入力してください: ");
			userID = Integer.parseInt(lane.nextLine());

			System.out.print("お気に入り登録する作者IDを入力してください: ");
			authorID = Integer.parseInt(lane.nextLine());
		} catch (NumberFormatException e) {
			System.out.println("数値として正しいIDを入力してください。");
		}
	}

	@Override
	public String getSQLtemplate() {
		return "INSERT INTO author_favorite_table(authorID, userID) VALUES (?, ?)";
	}

	@Override
	public void setQuery(PreparedStatement st) throws SQLException {
		st.setInt(1, authorID);
		st.setInt(2, userID);
	}

	@Override
	public void showResult(int affectedRows) {
		if (affectedRows > 0) {
			System.out.println("お気に入り登録が成功しました。");
		} else {
			System.out.println("お気に入り登録に失敗しました。");
		}
	}

	@Override
	public String checkIDSQL() {
		return "SELECT * FROM author_favorite_table WHERE authorID = ? AND userID = ?";
	}

	@Override
	public void setExistQuery(PreparedStatement st) throws SQLException {
		st.setInt(1, authorID);
		st.setInt(2, userID);
	}
}
