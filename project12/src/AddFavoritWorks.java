/**
 * ??i???C?????o?^
 * @author ?{?? ???
 */

import java.sql.*;
import java.util.Scanner;

public class AddFavoritWorks extends AbstractExecuter2 {
    private Scanner scanner = new Scanner(System.in);
    private int userID;
    private String title;
    private int workID;

    @Override
    public String getSQLtemplate() {
        return "INSERT INTO work_favorite_table VALUES (?, ?)";
    }

    @Override
    public void preQuery() {
        try {
            System.out.print("???[?U?[ID???????????????: ");
            userID = Integer.parseInt(scanner.nextLine());

            System.out.print("???C?????o?^???????i?????????????????: ");
            title = scanner.nextLine();

            workID = getWorkID(title); // ??????ID???ï

        } catch (NumberFormatException e) {
            System.out.println("???[?U?[ID????l????????????????B");
            throw new RuntimeException("????G???[: " + e.getMessage());
        } catch (Exception e) {
            System.out.println("??????e???–b??????: " + e.getMessage());
            throw new RuntimeException("?O?????G???[: " + e.getMessage());
        }
    }

    @Override
    public void setQuery(PreparedStatement st) throws SQLException {
        st.setInt(1, userID);
        st.setInt(2, workID);
    }

    @Override
    public String checkIDSQL() {
        return "SELECT * FROM work_favorite_table WHERE userID = ? AND workID = ?";
    }

    @Override
    public void setExistQuery(PreparedStatement st) throws SQLException {
        st.setInt(1, userID);
        st.setInt(2, workID);
    }

    private int getWorkID(String title) throws Exception {
        Connection conn = DriverManager.getConnection(
            "jdbc:mysql://localhost/mangareviews?useSSL=false&characterEncoding=utf8&useServerPrepStmts=true",
            "root", ""
        );

        PreparedStatement st = conn.prepareStatement("SELECT workID FROM work_table WHERE title = ?");
        st.setString(1, title);
        ResultSet rs = st.executeQuery();

        if (rs.next()) {
            int id = rs.getInt("workID");
            rs.close(); st.close(); conn.close();
            return id;
        } else {
            rs.close(); st.close(); conn.close();
            throw new Exception("?w??????i????????????B");
        }
    }

    @Override
    public void showResult(int affectedRows) {
        if (affectedRows > 0) {
            System.out.println("???C?????o?^??????????????B");
        } else {
            System.out.println("???C?????o?^????s????????B");
        }
    }
}
