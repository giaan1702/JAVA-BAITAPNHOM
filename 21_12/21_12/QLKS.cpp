#include "KS.h"
#include "KH.h"
#include "DP.h"
#include "USER.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm> // std::max_element
#include <limits>
USER_MANAGER userManager;
ListPhong lp;
RoomManager roomManager;
KhachHangManager khManager;
QLDatphong dpManager;


using namespace std;

void xuatHD(vector<DatPhong> &list_dp, ListPhong& lp ,RoomManager& rm){
    dpManager.xuattieudeHD();
    for (const auto& dp : list_dp) {
        int total = ((dp.getday_out() - dp.getday_in() + 1)*lp.getGP(rm.getPhong(dp.getidPhong())->getIDLP()));
            cout << left
         << setw(10) << dp.getMadatphong() << " | "
         << setw(15) << dp.getidPhong() << " | "
         << setw(15) << lp.getLP(rm.getPhong(dp.getidPhong())->getIDLP()) << " | "
         << setw(12) << dp.getday_in() << " | "
         << setw(12) << dp.getday_out() << " | "
         << setw(12) << lp.getGP(rm.getPhong(dp.getidPhong())->getIDLP()) << " | "
         << setw(2) << lp.getGP(rm.getPhong(dp.getidPhong())->getIDLP()) << " * " << dp.getday_out() - dp.getday_in() + 1 << " = " << total << endl;
    }

}

void drawPlot_revenue(vector<int>& vec, int day_in, int day_out) {

    const int maxValue = 25;             // Giá trị tối đa sau khi scale
    const int width = vec.size();        // Số lượng phần tử vector
    // for(int i=0; i< width; ++i){
    //     cout << vec[i] << " ";
    // }
    // cout << endl;

    // Tìm giá trị lớn nhất trong vector
    int maxVectorValue = *max_element(vec.begin(), vec.end());
    if (maxVectorValue == 0) {
        cout << "Khong co gi de ve :D\n";
        return;
    }

    // Scale giá trị trong vector
    vector<int> scaledVec(width);
    for (int i = 0; i < width; ++i) {
        scaledVec[i] = static_cast<int>((static_cast<double>(vec[i]) / maxVectorValue) * maxValue + 0.5);
    }

    // Vẽ biểu đồ dạng cột dọc
    for (int i = maxValue; i >= 1; --i) { // Duyệt từ giá trị maxValue về 1
        cout << setw(4) << i*4 << "   ";   // Cột giá trị phần trăm // " |  "
        for (int j = 0; j < width; ++j) {
            if (scaledVec[j] >= i) {
                cout << setw(5) << "  |  ";  // Hiển thị cột nếu giá trị >= i
            } else {
                cout << setw(5) << "     ";  // Khoảng trống nếu giá trị < i
            }
        }
        cout << '\n';
    }

    // Đường kẻ ngang ở trục x
    cout << "     +";
    for (int i = 0; i < width; ++i) {
        cout << "-----";
    }
    cout << '\n';

    // Hiển thị nhãn các ngày (ngày 1, ngày 2, ...)
    cout << "     ";
    for (int i = 0; i < width; ++i) {
        cout << setw(5) << day_in + i;
    }
    cout << '\n';
    int total_revenue = 0;
    // Hiển thị doanh thu ( VND)
    cout << "Doanh thu:\n       ";
    for (int i = 0; i < width; ++i) {
        cout << setw(5) << double(vec[i]) / 1000000;
        total_revenue += vec[i];
    }
    cout << "\nTong doanh thu trong thoi gian tren: " << double(total_revenue) / 1000000 << " trieu VND" << endl;
    cout << '\n';
    cout << '\n';
    cout << '\n';
}
void drawPlot_room_booked(vector<pair_IDLP_SoLuong> room_booked, ListPhong ListPhong){ // drawplot of room booked
    const int maxValue = 25;             // Giá trị tối đa sau khi scale
    const int width = room_booked.size();        // Số lượng phần tử vector

    int maxVectorValue = room_booked[0].soLuong;
    for(int i = 1; i < width; ++i){
        if(room_booked[i].soLuong > maxVectorValue){
            maxVectorValue = room_booked[i].soLuong;
        }
    }
    if (maxVectorValue == 0) {
        cout << "Khong co gi de ve :D\n";
        return;
    }

    // Scale giá trị trong vector
    vector<int> scaledVec(width);
    for (int i = 0; i < width; ++i) {
        scaledVec[i] = static_cast<int>((static_cast<double>(room_booked[i].soLuong) / maxVectorValue) * maxValue + 0.5);
    }

    // Vẽ biểu đồ dạng cột dọc
    for (int i = maxValue; i >= 1; --i) { // Duyệt từ giá trị maxValue về 1
        cout << setw(4) << i*4 << "   ";   // Cột giá trị phần trăm " | "
        for (int j = 0; j < width; ++j) {
            if (scaledVec[j] >= i) {
                cout << setw(15) << "  |  ";  // Hiển thị cột nếu giá trị >= i
            } else {
                cout << setw(15) << "     ";  // Khoảng trống nếu giá trị < i
            }
        }
        cout << '\n';
    }

    // Đường kẻ ngang ở trục x
    int sum=0;
    cout << "     +";
    for (int i = 0; i < width; ++i) {
        cout << setw(15) << room_booked[i].soLuong;
        sum+=room_booked[i].soLuong;
    }
    cout << '\n';
    cout << "Loai phong: "; // show loai phong
    for (int i = 0; i < width; ++i) {
        cout << setw(15) << ListPhong.getLP(room_booked[i].idLP);
    }
    cout << "\nTong so phong duoc su dung trong thoi gian tren: " << sum << endl;
    cout << '\n';

    

}




void quanlycosovatchat(RoomManager &roomManager, ListPhong &ListPhong){
        while (true) {
        cout << "**********Quan ly khach san**********" << endl;
        cout << "\nChon thao tac:\n";
        cout << "1. Them phong\n"; //tam on
        cout << "2. Sua/Xoa phong\n";
        cout << "3. Hien thi danh sach phong\n";
        cout << "4. Them loai phong \n";
        cout << "5. Sua/xoa loai phong\n";
        cout << "6. Hien thi danh sach loai phong\n";
        cout << "0. Luu va Thoat\n";

        int choice = getValidatedInput<int>("Lua chon: ");

        if (choice == 1) { // them phong
            ListPhong.hienThiDanhSach();
            int idLP, soPhong;
            idLP = getValidatedInput<int>("Chon loai phong(id): ");
            // them dk o day
            const LoaiPhong* xxx = ListPhong.getPhong(idLP);
            if(xxx){
                soPhong = getValidatedInput<int>("Nhap so phong: ");
                if (!roomManager.getPhong(soPhong)){// dk kiem tra so phong ton tai chua
                    vector<int> trangThaiMoi(31, 0);  // Khởi tạo mặc định trạng thái 31 ngày là 0
                    Room phongMoi(xxx->getId(), soPhong,  trangThaiMoi);
                    
                    // Hỏi người dùng có muốn lưu vào file không
                    char saveChoice;
                    cout << "Ban co muon luu thong tin vao file? (y/n): ";
                    cin >> saveChoice;

                    if (saveChoice == 'y') {
                        roomManager.themPhong(phongMoi);
                        roomManager.ghiPhongVaoFile("thongtinphong.txt");
                    } else {
                        cout << "Phong khong duoc them vao bo nho. Phong da duoc xoa" << endl;
                        // free mấy cái trên
                    }
                } else cout <<"So phong da ton tai."<< endl;
                


            }
            else cout << "Khong tim thay loai phong voi id: " << idLP << endl;


        } else if (choice == 2) { // sua/xoa phong
            cout << "\nDanh sach phong:\n";
            roomManager.hienThiDanhSachPhong(ListPhong);
            int soPhong = getValidatedInput<int>("Nhap so phong ban muon sua/xoa: ");
            const Room* r = roomManager.getPhong(soPhong);
            if ( r){
                int c2 =getValidatedInput<int>("1. Sua doi loai phong\n2. Xoa phong\n0. Tro ve\n");
                cout << "Thong tin phong:";
                r->hienThiThongTin(ListPhong);
                if(c2==1){
                    ListPhong.hienThiDanhSach();
                    int idLP = getValidatedInput<int>("Nhap id loai phong moi: ");
                    const LoaiPhong* xxx = ListPhong.getPhong(idLP);
                    if(xxx){
                        roomManager.suaLoaiPhong(soPhong, idLP);
                        roomManager.ghiPhongVaoFile("thongtinphong.txt");
                    } else cout << "Khong tim thay loai phong voi id: " << idLP << endl;
                } else if(c2==2){

                    bool check = false;
                    for(int i=0; i<31; i++){
                        if(r->getTrangThai()[i]) {check = true;break;}
                    }
                    if(check) {
                        cout <<"Phong chua trong(co dat phong). Vui long xoa hoac di chuyen cac dat phong truoc khi xoa phong.\n";
                    }
                    else {
                        char saveChoice;
                        cout << "Ban co muon luu thong tin vao file? (y/n): ";
                        cin >> saveChoice;
                        if (saveChoice == 'y') {
                            roomManager.xoaPhong(soPhong);
                            roomManager.ghiPhongVaoFile("thongtinphong.txt");
                        }
                    }
                }
            } else cout << "Khong tim thay phong voi so phong: " << soPhong << endl;
        } else if (choice == 3) {
            cout << "\nDanh sach phong:\n";
            roomManager.hienThiDanhSachPhong(ListPhong);
        } else if(choice ==4){ // them loai phong
            string loai; int gia;
            cout << "Nhap ten loai phong: "; getline(cin >> ws, loai);
            cout << "Nhap gia phong: "; cin >> gia;
            if(gia <= 0) {cout << "Gia phong khong hop le." << endl; continue;}
            else ListPhong.themLoaiPhong(loai, gia);
            ListPhong.ghiLoaiPhongVaoFile("loai_phong.txt");
        } else if(choice ==5){ // sua/xoa loai phong
            
            ListPhong.hienThiDanhSach();
            int idLP = getValidatedInput<int>("Nhap id loai phong ban muon sua/xoa: ");
            const LoaiPhong* lp = ListPhong.getPhong(idLP);
            if(lp){
                while(true){
                    cout << "1. Sua loai phong\n";
                    cout << "2. Xoa loai phong\n";
                    cout << "0. Tro ve\n";
                    int c2 = getValidatedInput<int>("Nhap lua chon: ");
                    if(c2==2){
                        vector<Room> list_phong_lp = roomManager.getPhong_lp(idLP); // kiem tra con phong nao thuoc loai phong do k
                        if(list_phong_lp.size()){ // con phong k xoa dc
                            cout << "Ton tai cac phong sau thuoc loai phong voi id_loai_phong:  " << idLP << " :" ;
                            for(auto& it : list_phong_lp){
                                cout << it.getSoPhong() << " ";
                            }
                            cout << endl;
                            cout << "Khong the xoa loai phong voi id: " << idLP << endl;
                            break;
                        }
                        else { 
                            ListPhong.xoaLoaiPhong(idLP);
                            break;
                        }

                    }
                    if(c2==1){ // sua dat phong
                        string tenphong; int giaphong;
                        cout << "Thong tin loai phong ban muon sua: " << endl;
                        ListPhong.getPhong(idLP)->hienThiThongTin();
                        cout << "Nhap ten phong moi: " << endl;
                        getline(cin >> ws, tenphong);
                        giaphong = getValidatedInput<int>("Nhap gia phong moi: ");
                        ListPhong.suaLoaiPhong(idLP, tenphong, giaphong);
                        ListPhong.ghiLoaiPhongVaoFile("loai_phong.txt");
                        break;

                    }
                    if(!c2){
                        break;
                    }
                }

            } else {cout << "khong tim thay loai phong voi id: " << idLP << endl;}
            ListPhong.ghiLoaiPhongVaoFile("loai_phong.txt");

            
        } else if(choice ==6 ){ //hien thi danh sach loai phong
            ListPhong.hienThiDanhSach();
        }else if (choice == 0) {
            cout << "Thoat chuong trinh." << endl;

            int danhsachphong[100], soluongphong;
            roomManager.layDanhSachSoPhong(danhsachphong, soluongphong);
            roomManager.ghiPhongVaoFile("thongtinphong.txt");  // Lưu thông tin phòng vào file
            ListPhong.ghiLoaiPhongVaoFile("loai_phong.txt");
            break;

        } else {
            cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    }

}
void quanlydatphong(KhachHangManager &khManager, RoomManager &roomManager, QLDatphong& dpManager,ListPhong &ListPhong){
        while (true) {
        cout << "\nChon thao tac:\n";
        cout << "1. Tao dat phong moi\n"; //ok
        cout << "2. Sua/xoa dat phong\n"; 
        cout << "3. In hoa don\n";
        cout << "4. Tim thong tin khach hang\n";
        cout << "5. Sua/xoa thong tin khach hang\n";
        cout << "6. Hien thi danh sach khach hang\n";
        cout << "7. Hien thi danh sach phong\n";
        cout << "8. Thong ke\n";
        cout << "0. Luu va Thoat\n";
        int choice = getValidatedInput<int>("Lua chon: ");

        if (choice == 1) {
            while (true) {
                cout << "1. Khach hang moi" << endl;
                cout << "2. Khach hang cu" << endl;
                cout << "0. Tro ve\n";
                int c2 = getValidatedInput<int>("Nhap lua chon: ");

                if (c2 == 0) {
                    break;
                }

                if (c2 == 1) {
                    string hoVaTen, quocTich, cmnd_hochieu, email;
                    int loaiGiayTo, sdt;

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

                    khManager.themKH(hoVaTen, quocTich, static_cast<LoaiGiayTo>(loaiGiayTo), cmnd_hochieu, sdt, email);
                    khManager.ghiKHVaoFile("thongtinkhachhang.txt");
                    cout << "Them khach hang moi thanh cong.\n";
                    break;
                }

                if (c2 == 2) {
                    khManager.hienThiDanhSachKH();
                    int id, day_in, day_out;
                    id = getValidatedInput<int>("Nhap ID khach hang: ");

                    if (khManager.getKH(id)) {
                        cout << "Thong tin khach dat phong: " << endl;
                        khManager.xuatKH_id(id);

                        do {
                            day_in = getValidatedInput<int>("Nhap ngay check-in (1-31): ");
                        } while (day_in < 1 || day_in > 31);

                        do {
                            day_out = getValidatedInput<int>("Nhap ngay check-out (1-31): ");
                        } while (day_out > 31 || day_in > day_out);

                        vector<Room> listphong_khadung = roomManager.phongkhadung_dayin_dayout(day_in, day_out); // ham tu -1 index
                        if (!listphong_khadung.empty()) {
                            cout << "Cac phong kha dung: \n";
                            roomManager.hienThiDanhSachPhong(ListPhong,listphong_khadung);

                            cout << endl;

                            int c3;
                            do {
                                c3 = getValidatedInput<int>("Nhap so phong ban muon chon: ");
                            } while (!roomManager.getPhong(c3));

                            int mdp = dpManager.themDatPhong(c3, id, day_in, day_out); // day real
                            roomManager.setTrangthai_in_out(day_in, day_out, c3, mdp); // day - 1 index
                            cout << "Tao dat phong thanh cong." << endl;
                            roomManager.ghiPhongVaoFile("thongtinphong.txt");
                            dpManager.ghivaofile("quanlydatphong.txt");
                        } else {
                            cout << "Khong con phong tu ngay " << day_in << " den ngay " << day_out << endl;
                        }
                    } else {
                        cout << "Khong tim thay khach hang voi id: " << id << endl;
                    }
                    break;
                }

                cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            }
        } else if (choice == 2) { //sua xoa datphong
            int mdp = getValidatedInput<int>("Nhap ma dat phong: ");
            if(dpManager.tim_MDP(mdp)){
                // hien thi thong tin cua mdp do
                dpManager.xuatTatCaThongTin({dpManager.getDP(mdp)});
                cout << "1.Sua dat phong\n";
                cout << "2.Xoa dat phong\n";
                cout << "0.Tro ve\n";
                int c2 = getValidatedInput<int>("Nhap lua chon: ");
                switch (c2)
                {
                case 0:
                    break;
                case 1: // sua dat phong
                    dpManager.suaDP(mdp, roomManager, khManager); // da bao gom thay doi trong room
                    break;
                case 2: // xoa dat phong
                    roomManager.setTrangthai_in_out(dpManager.getDP(mdp).getday_in(),dpManager.getDP(mdp).getday_out(),dpManager.getDP(mdp).getidPhong(),0);
                    dpManager.huyDatPhong(mdp);

                    roomManager.ghiPhongVaoFile("thongtinphong.txt");
                    dpManager.ghivaofile("quanlydatphong.txt");
                    break;
                default:
                    break;
                }

            }
            else {cout << "Khong tim thay ma dat phong\n.";}

    
        }else if (choice == 3) { //in hoa don
            cout << "1.Xuat toan bo hoa don\n";
            cout << "2.Xuat hoa don theo id KH\n";
            cout << "0.Tro ve\n";
            int c2 = getValidatedInput<int>("Nhap lua chon: ");
            if(c2==0) break;
            if(c2==2) {
                khManager.hienThiDanhSachKH();
                int idKH = getValidatedInput<int>("Nhap ID khach hang: ");
                vector<DatPhong> list_mdp = dpManager.list_MDP(idKH);// tra ve list dat phong cua id
                if(list_mdp.empty()){
                    cout << "Khach hang chua co dat phong.\n";
                    continue;
                }
                dpManager.xuatTatCaThongTin(list_mdp);
                cout << "0. Xuat toan bo hoa don cua khach: \n";
                int mdp = getValidatedInput<int>("Hoac Nhap ma dat phong: ");
                // tim mdp co trong list khong
                if( mdp != 0 && !dpManager.tim_MDP(mdp)){
                    cout << "Khong tim thay ma dat phong: " << mdp << endl;
                    continue;
                }
                if(mdp==0){
                    cout <<"TOAN BO HOA CUA CUA KHACH HANG: \n";
                    khManager.hienThiDanhSachKH({*khManager.getKH(idKH)});
                    cout << "Thong tin hoa don: \n";
                    xuatHD(list_mdp, ListPhong,roomManager);

                } else {
                    bool check = 0;
                    for( auto&  it : list_mdp){
                        if(it.getMadatphong()==mdp){
                            check = 1;
                            khManager.hienThiDanhSachKH({*khManager.getKH(idKH)});
                            cout << "Thong tin hoa don: \n";
                            vector<DatPhong> res = {it};
                            xuatHD(res, ListPhong,roomManager);
                        }
                    }
                    if(!check){
                        cout << "Khong tim thay mdp: " << mdp <<" cua khach hang co id: " << idKH << endl;
                    }
                }
            }
            if(c2==1){// xuat toan bo hoa don
                dpManager.xuatHoadon(khManager, ListPhong, roomManager);

            }

        } else if (choice ==4){
            khManager.hienThiDanhSachKH(khManager.timKiemKH());
        } else if (choice == 5) {
            khManager.hienThiDanhSachKH();
            int id = getValidatedInput<int>("Nhap ID khach hang ban muon sua/xoa: ");
            khManager.suaKH(id);
            khManager.ghiKHVaoFile("thongtinkhachhang.txt");

        } else if (choice == 6) {
            cout << " Danh sach khach hang" << endl;
            khManager.hienThiDanhSachKH();
        } else if(choice == 7){
            cout << " Danh sach phong" << endl;
            roomManager.hienThiDanhSachPhong(ListPhong);
        }else if(choice == 8){
            cout <<" Thong ke: " << endl;
            int day_in, day_out;
            do {
                day_in = getValidatedInput<int>("Nhap ngay bat dau (1-31): ");
            } while (day_in < 1 || day_in > 31);
            do {
                day_out = getValidatedInput<int>("Nhap ngay ket thuc (1-31): ");
            } while (day_out > 31 || day_in > day_out);
            vector<int> total_revenu = roomManager.total_revenue(day_in,day_out, ListPhong);
            drawPlot_revenue(total_revenu, day_in, day_out); // sua lai voi dayin dayout
            vector<pair_IDLP_SoLuong> room_booked = roomManager.getSLPhong_duocdat(day_in,day_out);
            drawPlot_room_booked(room_booked, ListPhong);
        } else if (choice == 0) {
            khManager.ghiKHVaoFile("thongtinkhachhang.txt");
            // room + dp
            cout << "Da luu. Thoat chuong trinh.\n";
            break;
        }
    }
}
int main() {
    userManager.docUserTuFile("user.txt");
    lp.docLoaiPhongTuFile("loai_phong.txt");
    roomManager.docPhongTuFile("thongtinphong.txt");
    khManager.docKHTuFile("thongtinkhachhang.txt");
    dpManager.docTuFile("quanlydatphong.txt");
    if(userManager.list_user.empty()){ // them admin neu chua co user nao
        USER admin(0, "admin", "admin", 1);
        userManager.themUser(admin);
    }
    int role = -1;
    USER user = USER(-1, "", "", -1);

    do {
        cout << "1. Dang nhap\n";
        cout << "0. Thoat\n";
        int ccc = getValidatedInput<int>("Nhap lua chon: ");
        switch (ccc) {
        case 1:     
            user = userManager.login();
            role = user.getRole();
            break;
        case 0:
            cout << "Thoat chuong trinh.\n";
            return 0;
        default:
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            break;
        }
    } while (role == -1);


    if (role == 0) {
        while (true) {
            cout << "1. Quan ly dat phong" << endl;
            cout << "0. Thoat" << endl;
            int c = getValidatedInput<int>("Nhap lua chon: ");
            if (c == 0) {
                cout << "Thoat chuong trinh." << endl;
                break;
            }
            switch (c) {
                case 1:
                    quanlydatphong(khManager, roomManager, dpManager, lp);
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
                    break;
            }
        }
    } else if (role == 1) { // admin
        while (true) {
            cout << "1. Quan ly co so vat chat" << endl;
            cout << "2. Quan ly dat phong" << endl;
            cout << "3. Quan ly thong tin user" << endl;
            cout << "4. Dang ky user" << endl;
            cout << "0. Thoat" << endl;
            int c = getValidatedInput<int>("Nhap lua chon: ");
            switch (c) {
                case 1:
                    quanlycosovatchat(roomManager, lp);
                    break;
                case 2:
                    quanlydatphong(khManager, roomManager, dpManager, lp);
                    break;
                case 3:
                    userManager.thayDoi();
                    userManager.ghiUserVaoFile("user.txt");
                    break;
                case 4:
                    userManager.dangKy();
                    userManager.ghiUserVaoFile("user.txt");
                    break;
                case 0:
                    cout << "Thoat chuong trinh." << endl;
                    return 0; // Exit the program
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
                    break;
            }
        }
    }

    return 0;
}
