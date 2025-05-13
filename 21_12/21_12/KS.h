#ifndef KH_S
#define KH_S

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "func.h"
//#include <DP.h>
using namespace std;
struct pair_IDLP_SoLuong{
    int idLP;
    int soLuong;
};
class LoaiPhong {
private:
    int idLP;
    string loaiphong;
    int giaphong;
public:
    LoaiPhong(int idLP =-1, string loai = "PhongKhongTen", int gia = 0) : idLP(idLP), loaiphong(loai), giaphong(gia) {};

    string getLoaiPhong() const {return loaiphong;}
    int getGiaPhong() const {return giaphong;}
    int getId() const {return idLP;}
    void ghiVaoFile(ofstream& out) const {
        out << idLP << " " << loaiphong << " " << giaphong << endl;
    }
    void hienThiThongTin() const {
        cout << left
             << setw(5) << idLP << " | "
             << setw(20) << loaiphong << " | "
             << setw(10) << giaphong << " VND" << endl;
    }
};
class ListPhong {
private:
    vector<LoaiPhong> List_LP;
    int idLonNhat;
public:
    ListPhong() : idLonNhat(0) {}

    // Đọc loại phòng từ file và cập nhật ID lớn nhất
    void docLoaiPhongTuFile(const string& fileName) {
        ifstream fileLP(fileName);
        if (!fileLP) {
            cout << "Khong the mo file: " << fileName << endl;
            return;
        }

        int id, giaPhong;
        string tenLoaiPhong;
        while (fileLP >> id >> tenLoaiPhong >> giaPhong) {
            LoaiPhong lp(id, tenLoaiPhong, giaPhong);
            List_LP.push_back(lp);

            // Cập nhật ID lớn nhất
            if (id > idLonNhat) {
                idLonNhat = id;
            }
        }

        fileLP.close();
    }

    // Ghi loại phòng vào file
    void ghiLoaiPhongVaoFile(const string& fileName) const {
        ofstream fileLP(fileName);
        if (!fileLP) {
            cout << "Khong the mo file: " << fileName << endl;
            return;
        }

        for (const auto& lp : List_LP) {
            lp.ghiVaoFile(fileLP);
        }

        fileLP.close();
    }

    // Lấy ID lớn nhất trong danh sách (để cấp phát ID mới)
    int maxid() {

        return ++idLonNhat;
    }
    void themLoaiPhong(const string loai, const int gia) {
        int idLP = maxid();
        LoaiPhong p(idLP,loai,gia);
        List_LP.push_back(p);
        cout << "Da them loai phong moi thanh cong" << endl;
    }
    const LoaiPhong* getPhong(int id) const {
        for (const auto& phong : List_LP) {
            if (phong.getId() == id) {
                return &phong; // Trả về con trỏ tới đối tượng Phong
            }
        }
        cout << "Khong tim thay phong voi ID: " << id << endl;
        return nullptr; // Trả về nullptr nếu không tìm thấy
    }

    string getLP(int idLP) const {
        const LoaiPhong* phong = getPhong(idLP);
        if (phong) {
            return phong->getLoaiPhong();
        } else {
            return "Da vuot qua tim idLP nhung khong tim thay phong???";
        }
    }
    void suaLoaiPhong(int id, string ten, int gia) {
        for (auto& phong : List_LP) {
            if (phong.getId() == id) {
                phong = LoaiPhong(id, ten, gia);
                cout << "Da sua loai phong voi ID: " << id << endl;
                return;
            }
        }
        cout << "Khong tim thay loai phong voi ID: " << id << endl;
    }
    void xoaLoaiPhong(int id) {
        for (auto it = List_LP.begin(); it != List_LP.end(); ++it) {
            if (it->getId() == id) {
                List_LP.erase(it);
                cout << "Da xoa loai phong voi ID: " << id << endl;
                return;
            }
        }
        cout << "Khong tim thay loai phong voi ID: " << id << endl;
    }

    int getGP(int idLP) const {
        const LoaiPhong* phong = getPhong(idLP);
        if (phong) {
            return phong->getGiaPhong();
        } else {
            return -1;
        }
    }

    void hienThiDanhSach() const {
        cout << left
             << setw(5) << "ID" << " | "
             << setw(20) << "Ten Loai Phong" << " | "
             << setw(10) << "Gia (VND)" << endl;
        cout << string(40, '-') << endl;
        for (const auto& lp : List_LP) {
            lp.hienThiThongTin();
        }
    }
};

class Room {

private:
    int idLP;
    int sophong;       // Số phòng
    vector<int> trangThai31Ngay;

public:
    friend class ListPhong;
    
    Room(int idLP, int sophong, vector<int>& trangthai)
        : idLP(idLP), sophong(sophong), trangThai31Ngay(trangthai) {}

    // Constructor mặc định
    //Room() : loaiphong(""), sophong(0), giaphong(0), trangThai31Ngay(31, 0) {}
    int getSoPhong() const { return sophong; }
    int getIDLP() const { return idLP;}
    const vector<int>& getTrangThai() const {
        return trangThai31Ngay;
    }

    void setTrangThai(const vector<int>& trangThai) {
        trangThai31Ngay = trangThai;
    }
    void setTrangThaiPhong(int index, int x) {
            trangThai31Ngay[index] = x;
    }
    void setLoaiPhong(int id) {
        idLP = id;
    }
    void hienThiThongTin(const ListPhong& listphong) const {


        // Display separator line
        cout << setfill('-') << setw(15) << "-" << "-+-"
             << setw(10) << "-" << "-+-"
             << setw(12) << "-" << "-+-"
             << setw(90) << "-" << setfill(' ') << endl;

        // Display room information
        cout << left
             << setw(15) << listphong.getLP(this->getIDLP()) << " | "
             << setw(10) << sophong << " | "
             << setw(12) << fixed << setprecision(2) << listphong.getGP(this->getIDLP()) << " | ";

        // Display room availability for 31 days in one row
        int count = 0; // count day room been occu
        for (const auto& trangThai : trangThai31Ngay) {
            cout << setw(2) << trangThai << " ";
            if(trangThai){++count;}
        }
        cout << " | " << count*listphong.getGP(this->getIDLP());
        cout << endl;
    }
    void ghiVaoFile(ofstream& out) const {
        out << idLP << " " << sophong << " ";
        for (const auto& trangThai : trangThai31Ngay) {
            out << trangThai << " ";
        }
        out << endl;
    }

};


class RoomManager {
private:
    vector<Room> danhSachPhong;

public:
    void docPhongTuFile(const string& fileName) {
        ifstream filePhong(fileName);
        if (!filePhong) {
            cout << "Khong the mo file: " << fileName << endl;
            return;
        }

        int idLP, sophong;
        vector<int> trangThai31Ngay(31);
        while (filePhong >> idLP >> sophong ) {
            for (int i = 0; i < 31; ++i) {
                filePhong >> trangThai31Ngay[i];
            }
            Room phong(idLP, sophong, trangThai31Ngay);
            danhSachPhong.push_back(phong);
        }

        filePhong.close();
    }
    void suaLoaiPhong(int sophong, int idLP) {
        for (auto& phong : danhSachPhong) {
            if (phong.getSoPhong() == sophong) {
                phong.setLoaiPhong(idLP);
                cout << "Da sua loai phong cua phong so " << sophong << endl;
                return;
            }
        }
        cout << "Khong tim thay phong so " << sophong << endl;
    }

    void ghiPhongVaoFile(const string& fileName) const {
        ofstream filePhong(fileName);
        for (const auto& phong : danhSachPhong) {
            phong.ghiVaoFile(filePhong);
        }
        filePhong.close();
    }
    const Room* getPhong(int sophong) const {
        for (const auto& phong : danhSachPhong) {
            if (phong.getSoPhong() == sophong) {
                return &phong;
            }
        }
        return nullptr; 
    }
    void resetPhong() {
        for (auto& phong : danhSachPhong) {
            vector<int> trangThaiMoi(31, 0); // Đặt trạng thái tất cả các ngày là 0
            phong.setTrangThai(trangThaiMoi);
        }
        //ghiPhongVaoFile("danhsachphong.txt");  // Cập nhật lại file
        cout << "Da reset trang thai phong." << endl;
    }
    void xuatTrangThaiPhong(int soPhong) const {
        const Room* phong = getPhong(soPhong);
        if(phong){
            cout << "Trang thai cua phong " << soPhong << " trong 31 ngay: ";
            for (int i = 0; i < 31; ++i) {
                cout << phong->getTrangThai()[i] << " ";
            }
            cout << endl;
            return;

        }
        cout << "Khong tim thay phong so " << soPhong << endl;
    }
    void xuatTrangThaiPhongNgay(int soPhong, int ngay) const {
        if (ngay < 1 || ngay > 31) {
            cout << "Ngay khong hop le (chi co 31 ngay)." << endl;
            return;
        }
        const Room* phong = getPhong(soPhong);
        if (phong) {
            cout << "Trang thai cua phong " << soPhong << " vao ngay " << ngay << ": ";
            cout << phong->getTrangThai()[ngay - 1] << endl;
            return;
        }
        cout << "Khong tim thay phong so " << soPhong << endl;
    }


    // Thêm phòng mới
    void themPhong(const Room& phongMoi) {
        const Room* phong = getPhong(phongMoi.getSoPhong());
        if (!phong) {
            danhSachPhong.push_back(phongMoi);
            cout << "Da them phong moi.\n";
        } else {
            cout << "So phong " << phongMoi.getSoPhong() << " da ton tai. Khong the them.\n";
        }
    }
    void hienThiDanhSachPhong(ListPhong &listphong, const vector<Room>& list_phong)  {
        cout << left 
            << setw(15) << "Loai Phong" << " | "
            << setw(10) << "So Phong" << " | "
            << setw(12) << "Gia Phong" << " | "
            << "Trang Thai 31 Ngay" << endl;
        for (const auto& phong : list_phong) {
            phong.hienThiThongTin(listphong); 
        }
    }

    void hienThiDanhSachPhong(ListPhong &listphong)  {
        hienThiDanhSachPhong(listphong, danhSachPhong);
    }


    void xoaPhong(int sophong) {
        for (auto it = danhSachPhong.begin(); it != danhSachPhong.end(); ++it) {
            if (it->getSoPhong() == sophong) {
                danhSachPhong.erase(it);
                cout << "Da xoa phong so " << sophong << endl;
                return;
            }
        }
        cout << "Phong so " << sophong << " khong ton tai." << endl;
    }
    void layDanhSachSoPhong(int danhsachphong[], int& soLuongPhong) {
        soLuongPhong = 0;  // Khởi tạo số lượng phòng bằng 0

        // Duyệt qua tất cả các phòng trong danh sách đã đọc từ file
        for (const auto& phong : danhSachPhong) {
            danhsachphong[soLuongPhong++] = phong.getSoPhong();  // Lưu số phòng vào mảng
        }

        // Sắp xếp mảng số phòng từ nhỏ tới lớn bằng Selection Sort
        for (int i = 0; i < soLuongPhong - 1; ++i) {
            int minIndex = i;  // Giả định phần tử đầu tiên là nhỏ nhất
            for (int j = i + 1; j < soLuongPhong; ++j) {
                if (danhsachphong[j] < danhsachphong[minIndex]) {
                    minIndex = j;  // Cập nhật chỉ số phần tử nhỏ nhất
                }
            }
            // Hoán đổi phần tử nhỏ nhất với phần tử ở vị trí i
            if (minIndex != i) {
                int temp = danhsachphong[i];
                danhsachphong[i] = danhsachphong[minIndex];
                danhsachphong[minIndex] = temp;
            }
        }
    }
    vector<Room> getPhong_lp(int idlp){
        vector<Room> res;
        for(auto& it: danhSachPhong){
            if(it.getIDLP() == idlp) {
                res.push_back(it);
            }
        }
        return res;
    }
    vector<Room> phongkhadung_dayin_dayout(int day_in, int day_out){
        vector<Room> res;
        for (const auto& phong : danhSachPhong) {
            bool check  = false; // co dat phong chua
            int i = day_in-1;
            while( i < day_out && !check) {
                if (phong.getTrangThai()[i] != 0)  {
                    check = true;
                }
                ++i;
            }

            if(!check) {
                res.push_back(phong);
            }
            
        }
        return res;
    }
    void setTrangthai_in_out(int day_in, int day_out, int sophong, int id){
        for (auto& phong : danhSachPhong) {// Duyệt qua danh sách phòng
            if (phong.getSoPhong() == sophong){
                for(int i =day_in-1; i<day_out;++i){ 
                    phong.setTrangThaiPhong(i, id); // Gọi hàm setTrangThaiPhong
                }
            }
        }        
    }

   vector<int> total_revenue (int s,int e, ListPhong& ListPhong){
        vector<int> res(e-s+1,0);
        for(auto& phong: danhSachPhong){
            const LoaiPhong* lp =  ListPhong.getPhong(phong.getIDLP());
            for(int i=s-1; i < e; ++i){
                if(phong.getTrangThai()[i]){
                    res[i-s+1] += lp->getGiaPhong();
                }
            }      
        }
        return res;
   }
    vector<pair_IDLP_SoLuong> getSLPhong_duocdat(int day_in, int day_out) {


        int day_in_index = day_in - 1;
        int day_out_index = day_out - 1;
        vector<pair_IDLP_SoLuong> res;

        for (auto& phong : danhSachPhong) {
            bool found = false;
            for (auto& it : res) {
                if (it.idLP == phong.getIDLP()) {
                    found = true;
                    for (int i = day_in_index; i <= day_out_index; ++i) {
                        if (phong.getTrangThai()[i]) {
                            ++it.soLuong;
                        }
                    }
                    break;
                }
            }
            if (!found) {
                pair_IDLP_SoLuong newPair;
                newPair.idLP = phong.getIDLP();
                newPair.soLuong = 0;
                for (int i = day_in_index; i <= day_out_index; ++i) {
                    if (phong.getTrangThai()[i]) {
                        ++newPair.soLuong;
                    }
                }
                res.push_back(newPair);
            }
        }
        return res;
    }
};

#endif
