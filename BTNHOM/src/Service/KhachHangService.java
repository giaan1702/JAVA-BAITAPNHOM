package Service;

import java.util.List;

import DAO.KhachHangDAO;
import DATA.KhachHang;

public class KhachHangService {
	private KhachHangDAO khDao = new KhachHangDAO();

    public boolean themKhachHang(KhachHang kh) throws ClassNotFoundException {
        if (kh == null
            || kh.getHoTen().isBlank()
            || kh.getSoGiayTo().isBlank()) {
            return false;
        }
        // Kiểm tra trùng số giấy tờ
        KhachHang exist = khDao.findBySoGiayTo(kh.getSoGiayTo());
        if (exist != null) {
            System.out.println("Số giấy tờ đã tồn tại.");
            return false;
        }
        return khDao.themKhachHang(kh);
    }

    public boolean suaKhachHang(KhachHang kh) throws ClassNotFoundException {
    	if (kh == null || kh.getId() <= 0) return false;
        if (kh.getHoTen().isBlank() || kh.getSoGiayTo().isBlank()) {
            throw new IllegalArgumentException("Thông tin bắt buộc chưa nhập");
        }
        return khDao.suaKhachHang(kh);
    }

    public boolean xoaKhachHang(int id) throws ClassNotFoundException {
        if (id <= 0) return false;
        return khDao.xoaKhachHang(id);
    }

    public List<KhachHang> layTatCaKhachHang() throws ClassNotFoundException {
        return khDao.layTatCaKhachHang();
    }

    public KhachHang timKhachHangTheoId(int id) {
        return khDao.findById(id);
    }

    public List<KhachHang> timKhachHangTheoTen(String ten) {
        return khDao.findByName(ten);
    }
}
