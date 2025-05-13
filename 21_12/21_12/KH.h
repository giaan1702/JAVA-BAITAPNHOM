#ifndef KH_H
#define KH_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> 
#include <cctype>    
#include "func.h"
using namespace std;
// fix function hienthithongtinPhong tu default thanh nhan tham so
//parameter: phong: all; dayS-dayE: all 
// id phong = 0 thi chay all 
string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(),
              [](unsigned char c) { return tolower(c); });
    return result;
}
enum LoaiGiayTo {
    CCCD,
    Hochieu
};

class KhachHang {
    private:
        int id;  // ID tự động cấp phát
        string hoVaTen;
        string quocTich;
        LoaiGiayTo loaiGiayTo;
        string cmnd_hochieu;
        int sdt;
        string email;

    public:
        // Constructor với tham số đầy đủ
        KhachHang(int _id, string _hoVaTen, string _quocTich, LoaiGiayTo _loaiGiayTo, string _cmnd_hochieu, int _sdt, string _email)
            : id(_id), hoVaTen(_hoVaTen), quocTich(_quocTich), loaiGiayTo(_loaiGiayTo), cmnd_hochieu(_cmnd_hochieu), sdt(_sdt), email(_email) {}

        // Getter
        int getId() const { return id; }
        string getHoVaTen() const { return hoVaTen; }
        string getQuocTich() const { return quocTich; }
        LoaiGiayTo getLoaiGiayTo() const { return loaiGiayTo; }
        string getCmndHochieu() const { return cmnd_hochieu; }
        int getSdt() const { return sdt; }
        string getEmail() const { return email; }

        // Hiển thị thông tin khách hàng
        void hienThiThongTin() const {
            cout << left
                << setw(10)  << id << " | "
                << setw(15) << hoVaTen << " | "
                << setw(15) << quocTich << " | "
                << setw(12) << (loaiGiayTo == CCCD ? "CCCD" : "Ho chieu") << " | "
                << setw(12) << cmnd_hochieu << " | "
                << setw(12) << sdt << " | "
                << setw(12) << email << endl;
        }

        // Ghi thông tin khách hàng vào file
    void ghiVaoFile(ofstream& out) const {
        out << id << "|"
            << hoVaTen << "|"
            << quocTich << "|"
            << (loaiGiayTo == CCCD ? 0 : 1) << "|"
            << cmnd_hochieu << "|"
            << sdt << "|"
            << email << '\n';
    }
};

class KhachHangManager {
private:
    vector<KhachHang> danhSachKH;
    int idLonNhat; // Biến để lưu ID lớn nhất hiện tại

public:
    KhachHangManager() : idLonNhat(100) {}

    // Đọc khách hàng từ file và tìm ID lớn nhất
    void docKHTuFile(const string& fileName) {
        ifstream fileKH(fileName);
        if (!fileKH) {
            cout << "Khong the mo file: " << fileName << endl;
            return;
        }

        string line;
        while (getline(fileKH, line)) {
            stringstream ss(line);
            string idStr, loaiGiayToStr, sdtStr;
            string hoVaTen, quocTich, cmnd_hochieu, email;

            // Tách các trường dựa trên ký tự '|'
            getline(ss, idStr, '|');
            getline(ss, hoVaTen, '|');
            getline(ss, quocTich, '|');
            getline(ss, loaiGiayToStr, '|');
            getline(ss, cmnd_hochieu, '|');
            getline(ss, sdtStr, '|');
            getline(ss, email, '|');

            // Chuyển đổi các trường số từ chuỗi sang giá trị số
            int id = stoi(idStr);
            int loaiGiayTo = stoi(loaiGiayToStr);
            int sdt = stoi(sdtStr);

            // Tạo đối tượng khách hàng
            LoaiGiayTo loaiGT = (loaiGiayTo == 0) ? CCCD : Hochieu;
            KhachHang kh(id, hoVaTen, quocTich, loaiGT, cmnd_hochieu, sdt, email);
            danhSachKH.push_back(kh);

            // Cập nhật ID lớn nhất
            if (id > idLonNhat) {
                idLonNhat = id;
            }
        }

        fileKH.close();
    }


    // Ghi khách hàng vào file
    void ghiKHVaoFile(const string& fileName) const {
        ofstream fileKH(fileName);
        if (!fileKH) {
            cout << "Khong the mo file: " << fileName << endl;
            return;
        }

        for (const auto& kh : danhSachKH) {
            kh.ghiVaoFile(fileKH);
        }

        fileKH.close();
    }

    // Cấp phát ID tự động (lấy ID lớn nhất và +1)
    int capPhatId() {
        return ++idLonNhat;
    }

    // Thêm khách hàng mới
    void themKH(const string& hoVaTen, const string& quocTich, LoaiGiayTo loaiGiayTo, const string& cmnd_hochieu, int sdt, const string& email) {
        int idMoi = capPhatId(); // Tự động cấp ID
        KhachHang kh(idMoi, hoVaTen, quocTich, loaiGiayTo, cmnd_hochieu, sdt, email);
        danhSachKH.push_back(kh);
        cout << "Da them khach hang voi ID: " << idMoi << endl;
    }

    // Hiển thị danh sách khách hàng
    void hienThiTieuDeKH() const {
        // In tiêu đề bảng
        cout << left
            << setw(10)  << "ID" << " | "
            << setw(15) << "Ho va ten" << " | "
            << setw(15) << "Quoc tich" << " | "
            << setw(12) << "Loai giay to" << " | "
            << setw(12) << "So giay to" << " | "
            << setw(12) << "SDT" << " | "
            << setw(24) << "Email" << endl;

        // In đường kẻ ngang
        cout << setfill('-') << setw(10) << "-" << "-+-"
            << setw(15) << "-" << "-+-"
            << setw(15) << "-" << "-+-"
            << setw(12) << "-" << "-+-"
            << setw(12) << "-" << "-+-"
            << setw(12) << "-" << "-+-"
            << setw(24) << "-" << setfill(' ') << endl;
    }

    void hienThiDanhSachKH(const vector<KhachHang>& list) const {
        if (list.empty()) {
            cout << "Danh sach khach hang trong!" << endl;
            return;
        }

        // Gọi hàm in tiêu đề
        hienThiTieuDeKH();

        // In thông tin từng khách hàng
        for (const auto& kh : list) {
            kh.hienThiThongTin(); // Gọi phương thức hiển thị thông tin của từng khách hàng
        }
    }

    void hienThiDanhSachKH() const {
        hienThiDanhSachKH(danhSachKH); // Gọi lại hàm với danh sách mặc định
    }

    // Xóa khách hàng theo ID
    void xoaKH(int id) {
        for (auto it = danhSachKH.begin(); it != danhSachKH.end(); ++it) {
            if (it->getId() == id) {
                danhSachKH.erase(it);
                cout << "Da xoa khach hang voi ID: " << id << endl;
                return;
            }
        }
        cout << "Khong tim thay khach hang voi ID: " << id << endl;
    }

    // Sửa thông tin khách hàng theo ID
    void suaKH(int id) {
        for (auto& kh : danhSachKH) {
            if (kh.getId() == id) {
                kh.hienThiThongTin();
                string hoVaTen, quocTich, cmnd_hochieu, email;
                int sdt, loaiGiayTo;

                cout << "Ho va ten: "; getline(cin >> ws, hoVaTen);
                cout << "Quoc tich: "; getline(cin >> ws, quocTich);
                do {
                    loaiGiayTo = getValidatedInput<int>("Loai giay to (0: CCCD, 1: Ho chieu): ");
                } while (cin.fail() || (loaiGiayTo != 0 && loaiGiayTo != 1));

                cout << "So giay to: "; getline(cin >> ws, cmnd_hochieu);
                do {
                    sdt = getValidatedInput<int>("So dien thoai: ");
                } while (cin.fail() || sdt < 0);
                cout << "Email: "; getline(cin >> ws, email);


                // Cập nhật thông tin
                kh = KhachHang(id, hoVaTen, quocTich, static_cast<LoaiGiayTo>(loaiGiayTo), cmnd_hochieu, sdt, email);
                cout << "Da cap nhat thong tin khach hang voi ID: " << id << endl;
                return;
            }
        }
        cout << "Khong tim thay khach hang voi ID: " << id << endl;
    }
    vector<KhachHang> timKiemKH() {
        vector<KhachHang> res;
        cout << "Chon kieu tim kiem:\n";
        cout << "1. Tim theo ID\n";
        cout << "2. Tim theo ten\n";
        cout << "3. Tim theo quoc tich\n";
        cout << "4. Tim theo so giay to\n";
        cout << "5. Tim theo SDT\n";
        cout << "6. Tim theo Email\n";
        cout << "0. Tro ve\n";
        int option = getValidatedInput<int>("Lua chon: ");

        switch (option) {
            case 1: { // tim theo ID
                int id = getValidatedInput<int>("Nhap ID: ");
                bool found = false;
                for (const auto& kh : danhSachKH) {
                    if (kh.getId() == id) {
                        res.push_back(kh);
                        found = true;
                    }
                }
                if (!found) {
                    cout << "Khong tim thay khach hang co ID: " << id << endl;
                }
                break;
            }
            case 2: { // tim theo ten
                string ten;
                while (true) {
                    cout << "Nhap ten: ";
                    getline(cin, ten);

                    if (!ten.empty()) { // Kiểm tra nếu chuỗi không rỗng
                        break; 
                    } else {
                        cout << "Loi: Vui long khong nhan Enter ma hay nhap ten!" << endl;
                    }
                }

                ten = toLower(ten);

                bool found = false;
                for (const auto& kh : danhSachKH) {
                    string tenKHLower = toLower(kh.getHoVaTen());
                    if (tenKHLower.find(ten) != string::npos) {
                        res.push_back(kh);
                        found = true;
                    }
                }

                if (!found) {
                    cout << "Khong tim thay khach hang co ten: " << ten << endl;
                }
                break;
            }
            case 3: {
                string quocTich;
                while (true) {
                    cout << "Nhap quoc tich: ";
                    getline(cin, quocTich);

                    if (!quocTich.empty()) { // Kiểm tra nếu chuỗi không rỗng
                        break; 
                    } else {
                        cout << "Loi: Vui long khong nhan Enter ma hay nhap quoc tich!" << endl;
                    }
                }

                quocTich= toLower(quocTich);
                bool found = false;
                for (const auto& kh : danhSachKH) {
                    string qtKH = toLower(kh.getQuocTich());
                    if (qtKH.find(quocTich) != string::npos) {
                        res.push_back(kh);
                        found = true;
                    }
                }
                if (!found) {
                    cout << "Khong tim thay khach hang co quoc tich: " << quocTich << endl;
                }
                break;
            }
            case 4: {
                string cmnd; 
                while(true) {
                    cout << "Nhap so giay to: ";
                    getline(cin, cmnd);
                    if (!cmnd.empty()) { // Kiểm tra nếu chuỗi không rỗng
                        break; 
                    } else {
                        cout << "Loi: Vui long khong nhan Enter ma hay nhap so giay to!" << endl;
                    }
                }

                cmnd = toLower(cmnd);
                bool found = false;
                for (const auto& kh : danhSachKH) {
                    string cmmndKH = toLower(kh.getCmndHochieu());
                    if (cmmndKH.find(cmnd) != string::npos) {
                        res.push_back(kh);
                        found = true;
                    }
                }
                if (!found) {
                    cout << "Khong tim thay khach hang co so giay to: " << cmnd << endl;
                }
                break;
            }
            case 5: {
                string sdt; // tim theo string
                while(true) {
                    cout << "Nhap SDT: ";
                    getline(cin, sdt);
                    if (!sdt.empty()) { // Kiểm tra nếu chuỗi không rỗng
                        break; 
                    } else {
                        cout << "Loi: Vui long khong nhan Enter ma hay nhap SDT!" << endl;
                    }
                }
                bool found = false;
                for (const auto& kh : danhSachKH) {
                    string sdtkh = toLower(to_string(kh.getSdt()));
                    if (sdtkh.find(sdt) != string::npos) {
                        res.push_back(kh);
                        found = true;
                    }
                }
                if (!found) {
                    cout << "Khong tim thay khach hang co SDT: " << sdt << endl;
                }
                break;
            }
            case 6: {
                string email;
                while(true) {
                    cout << "Nhap Email: ";
                    getline(cin, email);
                    if (!email.empty()) { // Kiểm tra nếu chuỗi không rỗng
                        break; 
                    } else {
                        cout << "Loi: Vui long khong nhan Enter ma hay nhap Email!" << endl;
                    }
                }
                email = toLower(email);
                bool found = false;
                for (const auto& kh : danhSachKH) {
                    string xxx = toLower(kh.getEmail());
                    if (xxx.find(email) != string::npos) {
                        res.push_back(kh);
                        found = true;
                    }
                }
                if (!found) {
                    cout << "Khong tim thay khach hang co Email: " << email << endl;
                }
                break;
            }
            default:
                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
                break;
            case 0:
                break;
        }
        return res;
    }

    void xuatKH_id(int id){
        for (const auto& kh : danhSachKH) { // Consider renaming danhSachKH to customerList
            if (kh.getId() == id) {
                kh.hienThiThongTin(); // Ensure hienThiThongTin doesn't modify kh
            }
        }
    }
    KhachHang* getKH(int id){
        for(auto& kh : danhSachKH){
            if(kh.getId()==id){
                return &kh;
            }
        }
        return nullptr;
    }
};
#endif