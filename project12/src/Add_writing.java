/**
 * 作品を登録するプログラム
 * @author Kouki Ando
 */
import java.sql.*;
import java.util.Scanner;

public class Add_writing extends AbstractExecuter2 {
	private int workID;
	private String title;
	private String summary;

	@Override
	public void preQuery() {
		Scanner scanner = new Scanner(System.in);
		try (// 接続...ここでmangareviewを選択しているので、manfareviewsに接続する際は気を付けてください
			Connection con = DriverManager.getConnection(
				"jdbc:mysql://localhost/mangareview?useSSL=false&characterEncoding=utf8&useServerPrepStmts=true", 
				"root", ""
				);
		     Statement stmt = con.createStatement();
		     ResultSet rs = stmt.executeQuery("SELECT MAX(workID) FROM work_table")) {

			if (rs.next()) {
				workID = rs.getInt(1) + 1;
			} else {
				workID = 1;//0の場合
			}
			System.out.println("作品ID: " + workID); // 確認表示

			System.out.print("作品名を入力してください: ");
			title = scanner.nextLine();

			System.out.print("作品概要を入力してください: ");
			summary = scanner.nextLine();

		} catch (SQLException e) {
			System.out.println("データベース接続またはID取得時にエラーが発生しました: " + e.getMessage());
		}
	}

	@Override
	public String getSQLtemplate() {
		return "INSERT INTO work_table(workID, title, summary) VALUES (?, ?, ?)";
	}

	@Override
	public void setQuery(PreparedStatement st) throws SQLException {
		st.setInt(1, workID);
		st.setString(2, title);
		st.setString(3, summary);
	}

	@Override
	public void showResult(int affectedRows) {
		if (affectedRows > 0) {
			System.out.println("作品の登録に成功しました。");
		} else {
			System.out.println("作品の登録に失敗しました。");
		}
	}
}
