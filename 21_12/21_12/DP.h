#ifndef DP_H
#define DP_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include "func.h"
//id booking + id guest + tor + dayin_ dayout+ id service * numbers???
// mdp  sophong kh in out
using namespace std;

class DatPhong{
    private:
        int Madatphong;
        int idPhong;
        int idKH;
        int day_in;
        int day_out;
    public:
        DatPhong(int Madatphong, int idPhong, int idKH, int day_in, int day_out)
            : Madatphong(Madatphong), idPhong(idPhong), idKH(idKH), day_in(day_in), day_out(day_out) {}

        // getter
        int getMadatphong() const { return Madatphong;}
        int getidKH() const { return idKH;}
        int getidPhong() const { return idPhong;}
        int getday_in() const {return day_in;}
        int getday_out() const {return day_out;}
        // hien thi thong tin
        // ghi vao file
            // Hiển thị thông tin đặt phòng
        void hienthithongtin() const {


            cout << left
                << setw(10) << Madatphong << " | "
                << setw(10) << idPhong << " | "
                << setw(10) << idKH << " | "
                << setw(12) << day_in  << " | "
                << setw(12) << day_out << endl;
        }



        // Ghi thông tin vào file
        void ghivaofile(ofstream &ofs) const {
            ofs << Madatphong << " "  << idPhong << " " << idKH << " " << day_in << " " << day_out << endl;
        }



};

class QLDatphong {
    private:
        vector<DatPhong> danhsachDatPhong;
        int MPD_max;
    public:
        QLDatphong() : MPD_max(0) {}
        // doc tu file vaf tim id lon nhat
        //void doc...
        //ghi vao file void...
            // Đọc dữ liệu từ file và tìm mã đặt phòng lớn nhất
        void docTuFile(const string &filename) {
            ifstream ifs(filename);
            if (!ifs.is_open()) {
                cout << "Khong mo duoc file: " << filename << endl;
                return;
            }

            danhsachDatPhong.clear();
            int Madatphong, idPhong, idKH, day_in, day_out;

            while (ifs >> Madatphong >> idPhong >> idKH >> day_in >> day_out) {
                danhsachDatPhong.emplace_back(Madatphong, idPhong, idKH, day_in, day_out);
                if (Madatphong > MPD_max) {
                    MPD_max = Madatphong;
                }
            }

            ifs.close();
            cout << "Da doc thong tin tu file: " << filename << endl;
        }

        const DatPhong& getDP(int MDP) const {
            for (const auto& it : danhsachDatPhong) {
                if (it.getMadatphong() == MDP) {
                    return it;
                }
            }
    
        }
        // Ghi dữ liệu vào file
        void ghivaofile(const string &filename) const {
            ofstream ofs(filename);
            if (!ofs.is_open()) {
                cout << "Khong mo duoc file: " << filename << endl;
                return;
            }

            for (const auto &dp : danhsachDatPhong) {
                dp.ghivaofile(ofs);
            }

            ofs.close();
            cout << "Da ghi thong tin vao file: " << filename << endl;
        }
        int capPhatMDP(){
            return ++MPD_max;
        }
        // DatPhong(int Madatphong, string loaiphong,int idPhong, int idKH, int day_in, int day_out)
        //     : Madatphong(Madatphong), loaiphong(loaiphong), idPhong(idPhong), idKH(idKH), day_in(day_in), day_out(day_out) {}
        int themDatPhong( const int& idPhong, const int& id, const int& day_in, const int& day_out) {
            int new_mdp = capPhatMDP();
            DatPhong dp(new_mdp, idPhong, id, day_in, day_out);
            danhsachDatPhong.push_back(dp);
            cout << "Da tao dat phong voi ma dat phong: " << new_mdp << endl;
            return new_mdp;
        }
        // void huyDatPhong
        void huyDatPhong(int MDP) {
            if (!tim_MDP(MDP)) {
                return;
            }

            for (auto it = danhsachDatPhong.begin(); it != danhsachDatPhong.end(); ++it) {
                if (it->getMadatphong() == MDP) {
                    danhsachDatPhong.erase(it);
                    cout << "Dat phong voi ma dat phong: " << MDP << " da duoc huy." << endl;
                    return;
                }
            }
        }
        // void suaDatPhong // optional : uu tien xoa roi tao lai thi khoe hon :)))))))))
        // bool tim_MDP
        bool tim_MDP( int MDP){
            bool found = false;
            for(const auto& it : danhsachDatPhong){
                if( it.getMadatphong() == MDP){
                    found = 1;
                    break;
                }
            }
            if(!found) { cout << "Khong tim thay ma dat phong: " << MDP <<endl;}
            return found;

        }
        void suaDP(int Madatphong, RoomManager& rm, KhachHangManager& khmanager) {
            for (auto& dp : danhsachDatPhong) { 
                if (dp.getMadatphong() == Madatphong) {
                    DatPhong temp = dp;
                    // Hiển thị thông tin cũ của đặt phòng
                    cout << "Thong tin cu cua dat phong ma " << Madatphong << ":\n";
                    dp.hienthithongtin();

                    int idPhong, idKH, day_in, day_out;
                    cout << "\nNhap thong tin moi cho dat phong ma " << Madatphong << ":\n";
                    idKH = getValidatedInput<int>("Nhap ID khach hang: ");
                    rm.setTrangthai_in_out(dp.getday_in(),dp.getday_out(),dp.getidPhong(),0); // tam xoa
                    if(khmanager.getKH(idKH)){
                        do {
                            day_in = getValidatedInput<int>("Nhap ngay check-in (1-31): ");
                        } while (day_in < 1 || day_in > 31);
                        do {
                            day_out = getValidatedInput<int>("Nhap ngay check-out (1-31): ");
                        } while (day_out > 31 || day_in > day_out);
                        vector<Room> list_phong_kha_dung = rm.phongkhadung_dayin_dayout(day_in,day_out);
                        if(list_phong_kha_dung.size()){
                            cout <<"Cac phong kha dung trong thoi gian tren : \n";
                            for( auto& phong : list_phong_kha_dung) {
                                cout << phong.getSoPhong() << " ";
                            }
                            cout  << endl;
                            idPhong = getValidatedInput<int>("Nhap so phong ban muon chon: ");
                            bool check  = 0;
                            for( auto& phong : list_phong_kha_dung) {  // if phong co trong list
                                if(phong.getSoPhong()==idPhong){
                                    check = 1;
                                }
                            }
                            if(check){ // if phong co trong list
                                rm.setTrangthai_in_out(day_in,day_out,idPhong,Madatphong);
                                dp = DatPhong(Madatphong, idPhong, idKH, day_in, day_out);
                                cout << "Da cap nhat thong tin dat phong voi ma: " << Madatphong << endl;
                                dp.hienthithongtin();     
                                rm.ghiPhongVaoFile("thongtinphong.txt");
                                ghivaofile("quanlydatphong.txt");
                                return;
                            } else {
                                cout << "Phong nhap khong hop le.";
                            }

                        }
                        else {
                            cout << "Khong co phong kha dung trong thoi gian ban chon.";
                        }
                    } else {cout << "khong tim thay khach hang co id: " << idKH << endl;}
                    rm.setTrangthai_in_out(temp.getday_in(),temp.getday_out(),temp.getidPhong(),temp.getMadatphong());
                    return;
                }
            }
            cout << "Khong tim thay dat phong voi ma: " << Madatphong << endl;
        }
        // void xuat_thongtinDp        
        void xuat_thongtinDP(int MDP) {
            if (!tim_MDP(MDP)) {
                cout << "Khong tim thay ma dat phong: " << MDP << endl;
                return;
            }

            for (const auto& dp : danhsachDatPhong) {
                if (dp.getMadatphong() == MDP) {
                    dp.hienthithongtin();
                    return; // Dừng sau khi xuất thông tin của mã đặt phòng tìm thấy
                }
            }
        }
        int MDP(int id){ // 1 di tra ve nhieu mdp for( it : datphogn) (datphong.getid() == id)
            for(auto& it : danhsachDatPhong){
                if( id == it.getidKH()) {return it.getMadatphong();} // handle bug: only find first
            }
            return 0;
        }
        void xuatTieuDe() const {
            if (danhsachDatPhong.empty()) {
                cout << "Danh sach dat phong trong!" << endl;
                return;
            }

            // In tiêu đề bảng
            cout << left
                << setw(10) << "MaDP" << " | "
                << setw(10) << "So phong" << " | "
                << setw(10) << "ID KH" << " | "
                << setw(12) << "Ngay den" << " | "
                << setw(12) << "Ngay di" << endl;

            cout << setfill('-') 
                << setw(10) << "-" << "-+-"
                << setw(10) << "-" << "-+-"
                << setw(10) << "-" << "-+-"
                << setw(12) << "-" << "-+-"
                << setw(12) << "-" << setfill(' ') << endl;
        }

        void xuatTatCaThongTin(const vector<DatPhong>& list) const {
            if (list.empty()) {
                cout << "Danh sach dat phong trong!" << endl;
                return;
            }

            xuatTieuDe(); // Gọi hàm in tiêu đề
            for (const auto& dp : list) {
                dp.hienthithongtin();
            }
        }

        void xuatTatCaThongTin() const {
            xuatTatCaThongTin(danhsachDatPhong); // Gọi lại phiên bản khác của hàm
        }
        void xuatHoadon(KhachHangManager& khManager, ListPhong& lp, RoomManager& rm) const{
            cout << "Danh sach hoa don: \n";
            for(const auto& dp : danhsachDatPhong){
                cout << "**********************************************************************************************************************\n";
                cout << "Thong tin khach hang\n";
                khManager.hienThiDanhSachKH({*khManager.getKH(dp.getidKH())});
                cout << "______________________________________________________________________________________________________________________\n";
                xuattieudeHD();
                int total = ((dp.getday_out() - dp.getday_in() + 1)*lp.getGP(rm.getPhong(dp.getidPhong())->getIDLP()));
                    cout << left
                << setw(10) << dp.getMadatphong() << " | "
                << setw(15) << dp.getidPhong() << " | "
                << setw(15) << lp.getLP(rm.getPhong(dp.getidPhong())->getIDLP()) << " | "
                << setw(12) << dp.getday_in() << " | "
                << setw(12) << dp.getday_out() << " | "
                << setw(12) << lp.getGP(rm.getPhong(dp.getidPhong())->getIDLP()) << " | "
                << setw(2) << lp.getGP(rm.getPhong(dp.getidPhong())->getIDLP()) << " * " << dp.getday_out() - dp.getday_in() + 1 << " = " << total << endl;
                cout << "**********************************************************************************************************************\n";
                    }
        }
        void xuattieudeHD() const {
            cout << left
                << setw(10) << "MaDP" << " | "
                << setw(15) << "So phong" << " | "
                << setw(15) << "Loai phong" << " | "
                << setw(12) << "Ngay den" << " | "
                << setw(12) << "Ngay di" << " | "
                << setw(12) << "Don gia" << " | "
                << setw(24) << "Tong tien" << endl;

            cout << setfill('-')
                << setw(10) << "-" << "-+-"
                << setw(15) << "-" << "-+-"
                << setw(15) << "-" << "-+-"
                << setw(12) << "-" << "-+-"
                << setw(12) << "-" << "-+-"
                << setw(12) << "-" << "-+-"
                << setw(24) << "-" << setfill(' ') << endl;

        }


        vector<DatPhong> list_MDP(int idKH){ // tra ve list dat phong cua id
            vector<DatPhong> res;
            for(const auto& it : danhsachDatPhong){
                if(it.getidKH()==idKH){
                    res.push_back(it);
                }
            }
            return res;
        }



};
#endif

