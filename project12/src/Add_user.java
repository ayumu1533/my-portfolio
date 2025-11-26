/**
 * ���[�U�[��o�^����v���O����
 * @author K.A
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
			System.out.println("�������蓖�Ă��ꂽ���[�U�[ID: " + userID);

			System.out.print("�j�b�N�l�[������͂��Ă�������: ");
			nickname = sc.nextLine();

			System.out.print("���[���A�h���X����͂��Ă�������: ");
			email = sc.nextLine();

			// ���[���d���`�F�b�N
			String existSQL = checkIDSQL();
			if (existSQL != null) {
				PreparedStatement checkSt = conn.prepareStatement(existSQL);
				setExistQuery(checkSt);
				ResultSet rs = checkSt.executeQuery();
				if (rs.next()) {
					System.out.println("���̃��[���A�h���X�͂��łɓo�^����Ă��܂��B�}�������𒆎~���܂��B");
					cancel = true;
					rs.close();
					checkSt.close();
					conn.close();
					return;
				}
				rs.close();
				checkSt.close();
			}

			System.out.print("�p�X���[�h����͂��Ă�������: ");
			password = sc.nextLine();

		} catch (SQLException e) {
			System.out.println("�f�[�^�x�[�X�G���[: " + e.getMessage());
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
		if (cancel) throw new SQLException("�o�^�L�����Z���ς݁B");
		st.setInt(1, userID);
		st.setString(2, nickname);
		st.setString(3, email);
		st.setString(4, password);
	}

	@Override
	public void showResult(int affectedRows) {
		if (cancel) {
			System.out.println("���[�U�[�o�^�͍s���܂���ł����B");
		} else if (affectedRows > 0) {
			System.out.println("���[�U�[�o�^���������܂����B");
		} else {
			System.out.println("���[�U�[�o�^�Ɏ��s���܂����B");
		}
	}
}
