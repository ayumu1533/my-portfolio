/**
 * ユーザーを登録するプログラム
 * @author Kouki Ando
 */
import java.sql.*;
import java.util.Scanner;

public class Add_user extends AbstractExecuter2 {
	private int userID;
	private String nickname;
	private String email;
	private String password;
	private boolean cancel = false;

	@Override
	public void preQuery() {
		Scanner sc = new Scanner(System.in);

		try (
			Connection conn = DriverManager.getConnection(
				"jdbc:mysql://localhost/mangareviews?useSSL=false&characterEncoding=utf8&useServerPrepStmts=true",
				"root", ""
			);
			Statement stmt = conn.createStatement();
			ResultSet rsMax = stmt.executeQuery("SELECT MAX(userID) FROM user_table")
		) {
			if (rsMax.next()) {
				userID = rsMax.getInt(1) + 1;
			} else {
				userID = 1;
			}
			System.out.println("自動割り当てされたユーザーID: " + userID);

			System.out.print("ニックネームを入力してください: ");
			nickname = sc.nextLine();

			System.out.print("メールアドレスを入力してください: ");
			email = sc.nextLine();

			// メール重複チェック
			String existSQL = checkIDSQL();
			if (existSQL != null) {
				PreparedStatement checkSt = conn.prepareStatement(existSQL);
				setExistQuery(checkSt);
				ResultSet rs = checkSt.executeQuery();
				if (rs.next()) {
					System.out.println("このメールアドレスはすでに登録されています。挿入処理を中止します。");
					cancel = true;
					rs.close();
					checkSt.close();
					conn.close();
					return;
				}
				rs.close();
				checkSt.close();
			}

			System.out.print("パスワードを入力してください: ");
			password = sc.nextLine();

		} catch (SQLException e) {
			System.out.println("データベースエラー: " + e.getMessage());
			cancel = true;
		}
	}
	@Override
    public String checkIDSQL() {
        return "SELECT * FROM user_table WHERE email = ?";
    }

    @Override
    public void setExistQuery(PreparedStatement st) throws SQLException {
        st.setString(1, email);
    }
	@Override
	public String getSQLtemplate() {
		return "INSERT INTO user_table(userID, nickname, email, password) VALUES (?, ?, ?, ?)";
	}

	@Override
	public void setQuery(PreparedStatement st) throws SQLException {
		if (cancel) throw new SQLException("登録キャンセル済み。");
		st.setInt(1, userID);
		st.setString(2, nickname);
		st.setString(3, email);
		st.setString(4, password);
	}

	@Override
	public void showResult(int affectedRows) {
		if (cancel) {
			System.out.println("ユーザー登録は行われませんでした。");
		} else if (affectedRows > 0) {
			System.out.println("ユーザー登録が成功しました。");
		} else {
			System.out.println("ユーザー登録に失敗しました。");
		}
	}
}
