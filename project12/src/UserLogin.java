/**
 * ���p�҂̃��O�C���ɐӔC�����N���X
 * @author T.N
 */

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UserLogin {

    private String mailAddress; // ���[�U�[�����͂������[���A�h���X
    private String password;    // ���[�U�[�����͂����p�X���[�h

    /**
     * ���[�U�[�Ƀ��[���A�h���X�ƃp�X���[�h�̓��͂����߁ADB�Əƍ����܂��B
     * ���O�C�������Ȃ�userID���A����̊Ǘ��҂Ȃ�0���A���s�Ȃ�-1��Ԃ��܂��B
     *
     * @return ��������userID (�Ǘ��҂̏ꍇ��0)�A���s����-1
     */
    public int login() {
        Scanner sc = new Scanner(System.in);
        System.out.print("���[���A�h���X����͂��ĉ����� > ");
        this.mailAddress = sc.nextLine();
        System.out.print("�p�X���[�h����͂��ĉ����� > ");
        this.password = sc.nextLine();


        String sql = "SELECT userID FROM user_table WHERE email = ? AND password = ?";

        try (Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost/mangareviews?useSSL=false&characterEncoding=utf8&useServerPrepStmts=true",
                "root", ""
             );
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, this.mailAddress);
            pstmt.setString(2, this.password);

            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    // ����̃��[���A�h���X�i�Ǘ��ҁj���ǂ����𔻒�
                    if (this.mailAddress.equals("user10@example.com")) {
                        System.out.println("�Ǘ��҂Ƃ��ă��O�C�����܂����B");
                        return 0; // �Ǘ��җp�̓���̖߂�l (0) ��Ԃ�
                    }

                    // ��ʃ��[�U�[�̏ꍇ�A�ʏ��userID��Ԃ�
                    int userId = rs.getInt("userID");
                    System.out.println("���O�C�������I (UserID: " + userId + ")");
                    return userId;
                } else {
                    System.out.println("���[���A�h���X�܂��̓p�X���[�h���Ԉ���Ă��܂��B");
                    return -1; // ���O�C�����s
                }
            }
        } catch (SQLException se) {
            System.out.println("�f�[�^�x�[�X�G���[: " + se.getMessage());
            return -1; // �G���[����
        }
    }

    // main���ł̎��s�̎d��

    public static void main(String[] args) {
        // UserLogin�N���X�̃C���X�^���X���쐬
        UserLogin userLogin = new UserLogin();
        
        // login���\�b�h�����s���A���ʂ��󂯎��
        int loginResult = userLogin.login();

        // ���O�C�����ʂɉ����ď����𕪊�
        if (loginResult == 0) {
            System.out.println(">> �Ǘ��җp���j���[�ւ悤�����B");
            // �����ɊǗ��Ҍ����̏������L�q
        } else if (loginResult > 0) {
            System.out.println(">> �悤�����A���[�U�[ID: " + loginResult + "����B");
            // �����Ɉ�ʃ��[�U�[�����̏������L�q
        } else {
            System.out.println(">> ���O�C���Ɏ��s�������߁A�������I�����܂��B");
        }
    }
}