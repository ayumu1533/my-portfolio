/**
 * ����̃��r���[���e�ɐӔC�����N���X
 * @author T.N 
 */


import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.util.Scanner;

public class MangaReviewManager extends AbstractExecuter2 {

    private int rating;
    private String content;
    private String userNickname;
    private String workTitle;
    private Integer userId;
    private Integer workId;
    private int reviewId;

    @Override
    public void preQuery() {
        Scanner sc = new Scanner(System.in);
        System.out.print("���r���[�Ώۂ̍�i������͂��Ă������� > ");
        this.workTitle = sc.nextLine();
        System.out.print("���Ȃ��̃j�b�N�l�[������͂��Ă������� > ");
        this.userNickname = sc.nextLine();
        System.out.print("�]���i1-5�j����͂��Ă������� > ");
        this.rating = Integer.parseInt(sc.nextLine());
        System.out.print("���r���[���e����͂��Ă������� > ");
        this.content = sc.nextLine();

        try (Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost/mangareviews?useSSL=false&characterEncoding=utf8&useServerPrepStmts=true",
                "root", "")) {

            try (PreparedStatement pstmt = conn.prepareStatement("SELECT MAX(reviewID) FROM review_table")) {
                ResultSet rs = pstmt.executeQuery();
                if (rs.next()) {
                    // �e�[�u������̏ꍇ�AMAX()��0��Ԃ����Ƃ�����̂ŁA���̏ꍇ��1����n�߂�
                    this.reviewId = rs.getInt(1) + 1;
                } else {
                    // ���ʃZ�b�g����i�e�[�u�������S�ɋ�j�̏ꍇ��1����
                    this.reviewId = 1;
                }
            }

            this.userId = findId(conn, "SELECT userID FROM user_table WHERE nickname = ?", this.userNickname);
            if (this.userId == null) {
                throw new RuntimeException("�G���[: ���[�U�[�u" + this.userNickname + "�v��������܂���B");
            }

            this.workId = findId(conn, "SELECT workID FROM work_table WHERE title = ?", this.workTitle);
            if (this.workId == null) {
                throw new RuntimeException("�G���[: ��i�u" + this.workTitle + "�v��������܂���B");
            }

        } catch (SQLException e) {
            throw new RuntimeException("�f�[�^�x�[�X�������ɃG���[���������܂����B", e);
        }
    }

    @Override
    public String getSQLtemplate() {
        return "INSERT INTO review_table(reviewID, rating, reviewarticle, Posting, userID, workID) VALUES (?, ?, ?, ?, ?, ?)";
    }

    @Override
    public void setQuery(PreparedStatement st) throws SQLException {
        st.setInt(1, this.reviewId);
        st.setInt(2, this.rating);
        st.setString(3, this.content);
        st.setTimestamp(4, Timestamp.valueOf(LocalDateTime.now()));
        st.setInt(5, this.userId);
        st.setInt(6, this.workId);
    }

    @Override
    public void showResult(int affectedRows) {
        if (affectedRows > 0) {
            System.out.println("���r���[���f�[�^�x�[�X�ɐ���ɓ��e���܂����I (ID: " + this.reviewId + ")");
        } else {
            System.out.println("���r���[�̓��e�Ɏ��s���܂����B");
        }
    }

    private Integer findId(Connection conn, String sql, String parameter) throws SQLException {
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, parameter);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1);
                }
            }
        }
        return null;
    }

    //�@�ȉ���main���ł̎��s�̎d��

    // public static void main(String[] args) {
    //     MangaReviewManager manager = new MangaReviewManager();
    //     manager.InsertAndShow();
    // }
}