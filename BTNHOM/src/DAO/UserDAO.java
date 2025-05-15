package DAO;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.sql.*;
import DATA.DBConnection;
import DATA.User;

public class UserDAO {
	// Thêm user
	public boolean themUser(User user) {
	    String sql = "INSERT INTO users (username, password, role) VALUES (?, ?, ?)";
	    try (Connection connection = DBConnection.getConnection();
	         PreparedStatement ps = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
	        
	        ps.setString(1, user.getUsername());
	        ps.setString(2, user.getPassword());
	        ps.setInt(3, user.getRole());
	        
	        int affected = ps.executeUpdate();
	        if (affected == 0) {
	            return false;
	        }
	        // (Tuỳ chọn) Lấy id mới sinh
	        try (ResultSet rs = ps.getGeneratedKeys()) {
	            if (rs.next()) {
	                int newId = rs.getInt(1);
	                user.setId(newId);
	            }
	        }
	        return true;
	    } catch (ClassNotFoundException | SQLException e) {
	        e.printStackTrace();
	    }
	    return false;
	}


    // Sửa user
    public boolean suaUser(User user) {
        String sql = "UPDATE users SET username=?, password=?, role=? WHERE id=?";
        try (Connection connection = DBConnection.getConnection();
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setString(1, user.getUsername());
            ps.setString(2, user.getPassword());
            ps.setInt(3, user.getRole());
            ps.setInt(4, user.getId());
            return ps.executeUpdate() > 0;
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    // Xóa user theo id
    public boolean xoaUser(int id) {
        String sql = "DELETE FROM users WHERE id=?";
        try (Connection connection = DBConnection.getConnection();
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setInt(1, id);
            return ps.executeUpdate() > 0;
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    // Lấy danh sách tất cả user
    public List<User> layTatCaUser() {
        List<User> list = new ArrayList<>();
        String sql = "SELECT * FROM users";
        try (Connection conn = DBConnection.getConnection();
             Statement st = conn.createStatement();
             ResultSet rs = st.executeQuery(sql)) {
            while (rs.next()) {
                User u = new User(
                    rs.getInt("id"),
                    rs.getString("username"),
                    rs.getString("password"),
                    rs.getInt("role")
                );
                list.add(u);
            }
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
        return list;
    }

    // Tìm user theo username/password (đăng nhập)
    public User login(String username, String password) {
        String sql = "SELECT * FROM users WHERE username=? AND password=?";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setString(1, username);
            ps.setString(2, password);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) {
                    return new User(
                        rs.getInt("id"),
                        rs.getString("username"),
                        rs.getString("password"),
                        rs.getInt("role")
                    );
                }
            }
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
        return null; // đăng nhập thất bại
    }
    
    public User findByUsername(String username) {
        String sql = "SELECT * FROM users WHERE username = ?";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setString(1, username);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) {
                    return new User(
                        rs.getInt("id"),
                        rs.getString("username"),
                        rs.getString("password"),
                        rs.getInt("role")
                    );
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
}
