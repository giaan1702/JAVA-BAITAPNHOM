package Service;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.time.LocalDate;
import java.util.*;

import DAO.DatPhongDAO;
import DAO.KhachHangDAO;
import DAO.PhongDAO;
import DATA.DBConnection;
import DATA.DatPhong;
public class DatPhongService {
	private DatPhongDAO dpDao = new DatPhongDAO();
    private PhongDAO phongDao = new PhongDAO();
    private KhachHangDAO khDao = new KhachHangDAO();

    public boolean datPhong(int khachHangId, int soPhong, LocalDate den, LocalDate di) throws ClassNotFoundException {
        // Kiểm tra khách hàng
        if (khDao.findById(khachHangId) == null) {
            System.out.println("Khách hàng không tồn tại");
            return false;
        }
        
        // Kiểm tra phòng có tồn tại không
        if (phongDao.findBySoPhong(soPhong) == null) {
            System.out.println("Phòng không tồn tại");
            return false;
        }
        
        // Kiểm tra phòng có trống không
        if (!isPhongTrong(soPhong, den, di)) {
            System.out.println("Phòng đã được đặt trong khoảng thời gian này");
            return false;
        }

        // Tạo đặt phòng mới
        DatPhong dp = new DatPhong(
            khachHangId,
            soPhong,
            java.sql.Date.valueOf(den),
            java.sql.Date.valueOf(di)
        );
        return dpDao.themDatPhong(dp);
    }

    private boolean isPhongTrong(int soPhong, LocalDate ngayDen, LocalDate ngayDi) {
        String sql = "SELECT COUNT(*) FROM datphong dp " +
                     "WHERE dp.so_phong = ? " +
                     "AND ((dp.ngay_den <= ? AND dp.ngay_di >= ?) " +
                     "OR (dp.ngay_den BETWEEN ? AND ?) " +
                     "OR (dp.ngay_di BETWEEN ? AND ?))";
        
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement ps = conn.prepareStatement(sql)) {
            
            ps.setInt(1, soPhong);
            ps.setDate(2, java.sql.Date.valueOf(ngayDi));
            ps.setDate(3, java.sql.Date.valueOf(ngayDen));
            ps.setDate(4, java.sql.Date.valueOf(ngayDen));
            ps.setDate(5, java.sql.Date.valueOf(ngayDi));
            ps.setDate(6, java.sql.Date.valueOf(ngayDen));
            ps.setDate(7, java.sql.Date.valueOf(ngayDi));
            
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) == 0;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public boolean huyDatPhong(int id) throws ClassNotFoundException {
        return dpDao.xoaDatPhong(id);
    }

    public List<DatPhong> layTatCaDatPhong() throws ClassNotFoundException {
        return dpDao.layTatCaDatPhong();
    }

    public DatPhong timDatPhongTheoId(int id) {
        return dpDao.findById(id);
    }

    public List<DatPhong> layDatPhongTheoKhachHang(int khId) {
        return dpDao.findByKhachHangId(khId);
    }
}
