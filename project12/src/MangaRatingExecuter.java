/**
 * ���惉���L���O��\������v���O����
 * @author K.A
 */

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

/**
 * ����̍�i���Ƃ̕��ϕ]���_���Z�o���A�]���̍������ɕ\������N���X
 * @author Taishi Nishimura
 */
public class MangaRatingExecuter extends AbstractExecuter {
    @Override
    public String getSQLtemplate() {
        return "SELECT title, AVG(rating) " +
               "FROM review_table " +
               "INNER JOIN work_table ON work_table.workID = review_table.workID " +
               "GROUP BY title " +
               "ORDER BY AVG(rating) DESC;";
    }

    // /**
    //  * PreparedStatement�ɒl���Z�b�g���܂��B
    //  * �����SQL�ɂ̓p�����[�^���Ȃ����߁A���̃��\�b�h�͋�ɂȂ�܂��B
    //  * @param st PreparedStatement�I�u�W�F�N�g
    //  * @throws SQLException
    //  */
    @Override
    public void setQuery(PreparedStatement st) throws SQLException {
         // ���̃N�G���ɂ� '?' �̂悤�ȃp�����[�^�͕s�v�Ȃ��߁A�����͂���܂���B
    }

    public void showResult(ResultSet r) {
        System.out.println("\n--- �����i ���ϕ]�������L���O ---\n");
        try {
            while (r.next()) {
                String title = r.getString("title");
                double avgRating = r.getDouble("AVG(rating)");
                System.out.printf("�y��i���z %s%n�y���ϕ]���z %.2f%n", title, avgRating);
                System.out.println("----------------------------------");
            }
        } catch (SQLException e) {
            System.out.println("���ʂ̕\������SQL�G���[���������܂���: " + e.toString());
        }
    }

    public static void main(String[] args) {
        MangaRatingExecuter executer = new MangaRatingExecuter();
        // ���ۃN���X�ɒ�`���ꂽ�A�����̖{�̂ƂȂ郁�\�b�h���Ăяo���܂��B
        executer.queryAndShow();
    }
}