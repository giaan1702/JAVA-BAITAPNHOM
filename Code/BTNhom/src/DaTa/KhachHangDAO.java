package DaTa;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class KhachHangDAO {
	 // Thêm khách hàng
    public boolean themKhachHang(KhachHang kh) throws ClassNotFoundException {
        String sql = "INSERT INTO khachhang (id, ho_ten, quoc_tich, loai_giay_to, so_giay_to, sdt, email) VALUES (?, ?, ?, ?, ?, ?, ?)";
        try (Connection connection = DBConnection.getConnection();
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setInt(1, kh.getId());
            ps.setString(2, kh.getHoTen());
            ps.setString(3, kh.getQuocTich());
            ps.setString(4, kh.getLoaiGiayTo());
            ps.setString(5, kh.getSoGiayTo());
            ps.setString(6, kh.getSdt());
            ps.setString(7, kh.getEmail());
            return ps.executeUpdate() > 0;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    // Sửa thông tin khách hàng
    public boolean suaKhachHang(KhachHang kh) throws ClassNotFoundException {
        String sql = "UPDATE khachhang SET ho_ten=?, quoc_tich=?, loai_giay_to=?, so_giay_to=?, sdt=?, email=? WHERE id=?";
        try (Connection connection = DBConnection.getConnection();
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setString(1, kh.getHoTen());
            ps.setString(2, kh.getQuocTich());
            ps.setString(3, kh.getLoaiGiayTo());
            ps.setString(4, kh.getSoGiayTo());
            ps.setString(5, kh.getSdt());
            ps.setString(6, kh.getEmail());
            ps.setInt(7, kh.getId());
            return ps.executeUpdate() > 0;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    // Xóa khách hàng theo ID
    public boolean xoaKhachHang(int id) throws ClassNotFoundException {
        String sql = "DELETE FROM khachhang WHERE id=?";
        try (Connection connection = DBConnection.getConnection();
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setInt(1, id);
            return ps.executeUpdate() > 0;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    // Lấy danh sách khách hàng
    public List<KhachHang> layTatCaKhachHang() throws ClassNotFoundException {
        List<KhachHang> ds = new ArrayList<>();
        String sql = "SELECT * FROM khachhang";
        try (Connection connection = DBConnection.getConnection();
             Statement st = connection.createStatement();
             ResultSet rs = st.executeQuery(sql)) {
            while (rs.next()) {
                KhachHang kh = new KhachHang(
                        rs.getInt("id"),
                        rs.getString("ho_ten"),
                        rs.getString("quoc_tich"),
                        rs.getString("loai_giay_to"),
                        rs.getString("so_giay_to"),
                        rs.getString("sdt"),
                        rs.getString("email")
                );
                ds.add(kh);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return ds;
    }
}
