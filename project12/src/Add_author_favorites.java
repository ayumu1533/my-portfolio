/**
 * ���C�ɓ����҂�o�^����v���O����
 * @author Ayumu Sato
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
			System.out.print("���[�U�[ID����͂��Ă�������: ");
			userID = Integer.parseInt(lane.nextLine());

			System.out.print("���C�ɓ���o�^������ID����͂��Ă�������: ");
			authorID = Integer.parseInt(lane.nextLine());
		} catch (NumberFormatException e) {
			System.out.println("���l�Ƃ��Đ�����ID����͂��Ă��������B");
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
			System.out.println("���C�ɓ���o�^���������܂����B");
		} else {
			System.out.println("���C�ɓ���o�^�Ɏ��s���܂����B");
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
