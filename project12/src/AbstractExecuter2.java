/**
 * �}���n��SQL�̎��s�ɐӔC�����N���X�̐��`�ƂȂ钊�ۃN���X
 *  @author K.A
*/
import java.sql.*;

public abstract class AbstractExecuter2 {
	public abstract String getSQLtemplate();
	public abstract void setQuery(PreparedStatement st) throws SQLException;
	public abstract void showResult(int affectedRows);
	public void preQuery() {}// �K�v�ɉ����ăI�[�o�[���C�h. �O����������Ȃ��Ȃ炻�̂܂܎g��

	//ID�̏d���`�F�b�N�pSQL��Ԃ��iID��}������T�u�N���X�Ȃ�I�[�o�[���C�h�j
	public String checkIDSQL() {
		return null; //�f�t�H���g�ł͏d���`�F�b�N�Ȃ�
	}
	//�`�F�b�N�pSQL�ɑ΂���p�����[�^�ݒ�icheckIDSQL���K�v�ȃT�u�N���X���I�[�o�[���C�h�j
	public void setExistQuery(PreparedStatement st) throws SQLException {
		// �f�t�H���g�͉������Ȃ�
	}
	public final void InsertAndShow() {
		try {
			//�K�v�Ȃ�O����
			preQuery();

			Connection conn = DriverManager.getConnection(
				"jdbc:mysql://localhost/mangareviews?useSSL=false&characterEncoding=utf8&useServerPrepStmts=true",
				"root", ""
			);

			//ID�d���`�F�b�N
			String existSQL = checkIDSQL();
			if (existSQL != null) {
				PreparedStatement checkSt = conn.prepareStatement(existSQL);
				setExistQuery(checkSt);
				ResultSet rs = checkSt.executeQuery();
				if (rs.next()){	//rs.next()��ture�Ȃ瓯��ID�����݂���Ƃ�����
					System.out.println("�w�肳�ꂽID�͂��łɑ��݂��Ă��܂��B�}�������𒆎~���܂��B");
					rs.close();
					checkSt.close();
					conn.close();
					return;
				}
				rs.close();
				checkSt.close();
			}
			// �}������
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
