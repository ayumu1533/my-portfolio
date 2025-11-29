/**
 * 挿入系のSQLの実行に責任を持つクラスの雛形となる抽象クラス
 *  @author kouki Ando
*/
import java.sql.*;

public abstract class AbstractExecuter2 {
	public abstract String getSQLtemplate();
	public abstract void setQuery(PreparedStatement st) throws SQLException;
	public abstract void showResult(int affectedRows);
	public void preQuery() {}// 必要に応じてオーバーライド. 前処理がいらないならそのまま使う

	//IDの重複チェック用SQLを返す（IDを挿入するサブクラスならオーバーライド）
	public String checkIDSQL() {
		return null; //デフォルトでは重複チェックなし
	}
	//チェック用SQLに対するパラメータ設定（checkIDSQLが必要なサブクラスがオーバーライド）
	public void setExistQuery(PreparedStatement st) throws SQLException {
		// デフォルトは何もしない
	}
	public final void InsertAndShow() {
		try {
			//必要なら前処理
			preQuery();

			Connection conn = DriverManager.getConnection(
				"jdbc:mysql://localhost/mangareviews?useSSL=false&characterEncoding=utf8&useServerPrepStmts=true",
				"root", ""
			);

			//ID重複チェック
			String existSQL = checkIDSQL();
			if (existSQL != null) {
				PreparedStatement checkSt = conn.prepareStatement(existSQL);
				setExistQuery(checkSt);
				ResultSet rs = checkSt.executeQuery();
				if (rs.next()){	//rs.next()がtureなら同一IDが存在するという事
					System.out.println("指定されたIDはすでに存在しています。挿入処理を中止します。");
					rs.close();
					checkSt.close();
					conn.close();
					return;
				}
				rs.close();
				checkSt.close();
			}
			// 挿入処理
			PreparedStatement st = conn.prepareStatement(getSQLtemplate());
			setQuery(st);
			int affectedRows = st.executeUpdate();
			showResult(affectedRows);
			st.close();
			conn.close();

		} catch (SQLException se) {
			System.out.println("SQL Error: " + se.toString());
		} catch (Exception e) {
			System.out.println("Error: " + e.toString());
		}
	}
}
