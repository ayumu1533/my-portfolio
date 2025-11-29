/**
 * 利用者のログインに責任を持つクラス
 * @author Taishi Nishimura
 */

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UserLogin {

    private String mailAddress; // ユーザーが入力したメールアドレス
    private String password;    // ユーザーが入力したパスワード

    /**
     * ユーザーにメールアドレスとパスワードの入力を求め、DBと照合します。
     * ログイン成功ならuserIDを、特定の管理者なら0を、失敗なら-1を返します。
     *
     * @return 成功時はuserID (管理者の場合は0)、失敗時は-1
     */
    public int login() {
        Scanner sc = new Scanner(System.in);
        System.out.print("メールアドレスを入力して下さい > ");
        this.mailAddress = sc.nextLine();
        System.out.print("パスワードを入力して下さい > ");
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
                    // 特定のメールアドレス（管理者）かどうかを判定
                    if (this.mailAddress.equals("user10@example.com")) {
                        System.out.println("管理者としてログインしました。");
                        return 0; // 管理者用の特定の戻り値 (0) を返す
                    }

                    // 一般ユーザーの場合、通常のuserIDを返す
                    int userId = rs.getInt("userID");
                    System.out.println("ログイン成功！ (UserID: " + userId + ")");
                    return userId;
                } else {
                    System.out.println("メールアドレスまたはパスワードが間違っています。");
                    return -1; // ログイン失敗
                }
            }
        } catch (SQLException se) {
            System.out.println("データベースエラー: " + se.getMessage());
            return -1; // エラー発生
        }
    }

    // main文での実行の仕方

    public static void main(String[] args) {
        // UserLoginクラスのインスタンスを作成
        UserLogin userLogin = new UserLogin();
        
        // loginメソッドを実行し、結果を受け取る
        int loginResult = userLogin.login();

        // ログイン結果に応じて処理を分岐
        if (loginResult == 0) {
            System.out.println(">> 管理者用メニューへようこそ。");
            // ここに管理者向けの処理を記述
        } else if (loginResult > 0) {
            System.out.println(">> ようこそ、ユーザーID: " + loginResult + "さん。");
            // ここに一般ユーザー向けの処理を記述
        } else {
            System.out.println(">> ログインに失敗したため、処理を終了します。");
        }
    }
}