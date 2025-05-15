package Service;

import java.time.LocalDate;
import java.util.List;

import DAO.PhongDAO;
import DATA.Phong;

public class PhongService {
	private PhongDAO phongDao = new PhongDAO();

    public boolean themPhong(Phong p) throws ClassNotFoundException {
        if (p == null || p.getSoPhong() <= 0) return false;
        return phongDao.themPhong(p);
    }

    public boolean suaPhong(Phong p) throws ClassNotFoundException {
        if (p == null || p.getSoPhong() <= 0) return false;
        return phongDao.suaPhong(p);
    }

    public boolean xoaPhong(int id) throws ClassNotFoundException {
        if (id <= 0) return false;
        return phongDao.xoaPhong(id);
    }

    public List<Phong> layTatCaPhong() throws ClassNotFoundException {
        return phongDao.layTatCaPhong();
    }

    public Phong timTheoId(int id) {
        return phongDao.findById(id);
    }

    public Phong findBySoPhong(int soPhong) {
        if (soPhong <= 0) return null;
        return phongDao.findBySoPhong(soPhong);
    }
}
