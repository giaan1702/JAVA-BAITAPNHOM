#ifndef LP.h
#define LP.h

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
//#include <DP.h>
using namespace std;
class Phong {
private:
    int idLP;
    string loaiphong;
    int giaphong;
public:
    Phong(int idLP =-1, string loai = "PhongKhongTen", int gia = 0) : idLP(idLP), loaiphong(loai), giaphong(gia) {};

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
    vector<Phong> List_LP;
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
            Phong lp(id, tenLoaiPhong, giaPhong);
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
        int maxId = 0;
        for (const auto &phong : List_LP) {
            if (phong.getId() > maxId) {
                maxId = phong.getId();
            }
        }
        return maxId + 1; // Trả về ID mới (lớn hơn max hiện tại)
    }
    void themLoaiPhong(const string loai, const int gia) {
        int idLP = maxid();
        Phong p(idLP,loai,gia);
        List_LP.push_back(p);
        cout << "Da them loai phong moi thanh cong" << endl;
    }
    Phong* getPhong(int id) {
        for (auto& phong : List_LP) {
            if (phong.getId() == id) {
                return &phong; // Trả về con trỏ tới đối tượng Phong
            }
        }
        cout << "Khong tim thay phong voi ID: " << id << endl;
        return nullptr; // Trả về nullptr nếu không tìm thấy
    }

    string getLP(int idLP){
        
        if(getPhong(idLP)){
            Phong* phong = getPhong(idLP);
            return phong->getLoaiPhong();
        } else {
            return "Da vuot qua tim idLP nhung khong tim thay phong???";
        }
    }
    int getGP(int idLP){
        if(getPhong(idLP)){
            Phong* phong = getPhong(idLP);
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

#endif