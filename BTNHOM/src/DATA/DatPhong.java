package DATA;

import java.sql.Date;

public class DatPhong {
	private int id;
	    private int khachHangId;
	    private int phongId;
	    private Date ngayDen;
	    private Date ngayDi;

	    public DatPhong(int khachHangId, int phongId, Date ngayDen, Date ngayDi) {
	    	
	        this.khachHangId = khachHangId;
	        this.phongId = phongId;
	        this.ngayDen = ngayDen;
	        this.ngayDi = ngayDi;
	    }
	    public DatPhong(int id, int khachHangId, int phongId, Date ngayDen, Date ngayDi) {
	        this.id = id;
	        this.khachHangId = khachHangId;
	        this.phongId = phongId;
	        this.ngayDen = ngayDen;
	        this.ngayDi = ngayDi;
	    }

	    // Getters & Setters
	    public int getId() { return id; }
	    public void setId(int id) { this.id = id; }
	    
	    public int getKhachHangId() { return khachHangId; }
	    public int getPhongId() { return phongId; }
	    public Date getNgayDen() { return ngayDen; }
	    public Date getNgayDi() { return ngayDi; }

	 
	    public void setKhachHangId(int khachHangId) { this.khachHangId = khachHangId; }
	    public void setPhongId(int phongId) { this.phongId = phongId; }
	    public void setNgayDen(Date ngayDen) { this.ngayDen = ngayDen; }
	    public void setNgayDi(Date ngayDi) { this.ngayDi = ngayDi; }
}
