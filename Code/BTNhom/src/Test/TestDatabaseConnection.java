package Test;
import DaTa.DBConnection;
import DaTa.User;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.List;

import DAO.UserDAO;
public class TestDatabaseConnection {
	public static void main(String[] args) {
        // Test nối đến CSDL
        System.out.println("=== Testing database connection ===");
        try (Connection connection = DBConnection.getConnection()) {
            if (connection != null && !connection.isClosed()) {
                System.out.println("Kết nối thành công đến CSDL!");
            } else {
                System.out.println("Kết nối thất bại.");
                return;
            }
        } catch (ClassNotFoundException e) {
            System.err.println("Driver JDBC không tìm thấy: " + e.getMessage());
            return;
        } catch (SQLException e) {
            System.err.println("Lỗi SQL khi kết nối: " + e.getMessage());
            return;
        }

        // Test chức năng: lấy danh sách người dùng
        System.out.println("=== Testing UserDAO.layTatCaUser() ===");
        UserDAO userDAO = new UserDAO();
        try {
            List<User> users = userDAO.layTatCaUser();
            System.out.println("Danh sách users trong CSDL:");
            for (User u : users) {
                System.out.printf("ID=%d, username=%s, role=%d\n", u.getId(), u.getUsername(), u.getRole());
            }
        } catch (Exception e) {
            System.err.println("Lỗi khi lấy danh sách users: " + e.getMessage());
        }
    }
}
