package DATA;

public class Phong {
	
    private int soPhong;
    private int loaiPhongId;

    public Phong( int soPhong, int loaiPhongId) {
        
        this.soPhong = soPhong;
        this.loaiPhongId = loaiPhongId;
    }

    // Getters & Setters
    
    public int getSoPhong() { return soPhong; }
    public int getLoaiPhongId() { return loaiPhongId; }

   
    public void setSoPhong(int soPhong) { this.soPhong = soPhong; }
    public void setLoaiPhongId(int loaiPhongId) { this.loaiPhongId = loaiPhongId; }
}
