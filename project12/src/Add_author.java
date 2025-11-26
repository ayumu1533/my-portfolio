import java.sql.*;
import java.util.Scanner;

public class Add_author extends AbstractExecuter2 {
	private int authorID;
	private String authorName;

	@Override
	public void preQuery() {
		Scanner lane = new Scanner(System.in);
		try {
			System.out.print("ìÒID‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢: ");
			authorID = Integer.parseInt(lane.nextLine());

			System.out.print("ìÒ–¼‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢: ");
			authorName = lane.nextLine();
		} catch (NumberFormatException e) {
			System.out.println("³‚µ‚¢ID‚â–¼‘O‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢B");
		}
	}

	@Override
	public String getSQLtemplate() {
		return "INSERT INTO author_table(authorID, authorname) VALUES (?, ?)";
	}

	@Override
	public void setQuery(PreparedStatement st) throws SQLException {
		st.setInt(1, authorID);
		st.setString(2, authorName);
	}

	@Override
	public void showResult(int affectedRows) {
		if (affectedRows > 0) {
			System.out.println("ìÒ“o˜^‚ª¬Œ÷‚µ‚Ü‚µ‚½B");
		} else {
			System.out.println("ìÒ“o˜^‚É¸”s‚µ‚Ü‚µ‚½B");
		}
	}

	@Override
	public String checkIDSQL() {
		return "SELECT authorID FROM author_table WHERE authorID = ?";
	}

	@Override
	public void setExistQuery(PreparedStatement st) throws SQLException {
		st.setInt(1, authorID);
	}
}
