/**
 * ��i��o�^����v���O����
 * @author K.A
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
		try (// �ڑ�...������mangareview��I�����Ă���̂ŁAmanfareviews�ɐڑ�����ۂ͋C��t���Ă�������
			Connection con = DriverManager.getConnection(
				"jdbc:mysql://localhost/mangareview?useSSL=false&characterEncoding=utf8&useServerPrepStmts=true", 
				"root", ""
				);
		     Statement stmt = con.createStatement();
		     ResultSet rs = stmt.executeQuery("SELECT MAX(workID) FROM work_table")) {

			if (rs.next()) {
				workID = rs.getInt(1) + 1;
			} else {
				workID = 1;//0�̏ꍇ
			}
			System.out.println("��iID: " + workID); // �m�F�\��

			System.out.print("��i������͂��Ă�������: ");
			title = scanner.nextLine();

			System.out.print("��i�T�v����͂��Ă�������: ");
			summary = scanner.nextLine();

		} catch (SQLException e) {
			System.out.println("�f�[�^�x�[�X�ڑ��܂���ID�擾���ɃG���[���������܂���: " + e.getMessage());
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
			System.out.println("��i�̓o�^�ɐ������܂����B");
		} else {
			System.out.println("��i�̓o�^�Ɏ��s���܂����B");
		}
	}
}
