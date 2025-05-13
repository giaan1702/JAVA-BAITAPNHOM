#ifndef User_H
#define User_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include "func.h"
#define default_password "abcxyz"
using namespace std;


class USER {
    private:
        int id_user;
        string username;
        string password;
        int role; //1 admin, 0 user

    public:
        USER(int id, const string& username, const string& password, int role)
            : id_user(id), username(username), password(password), role(role) {}
        void hienthiThongTin() const {
            cout << left
                << setw(5) << id_user << " | "
                << setw(20) << username << " | "
                << setw(15) << password << " | "
                << setw(15) << role << endl;
        }
        int getId() const { return id_user; }
        int getRole() const { return role; }
        string getPassword() const { return password; }
        string getUsername() const { return username; }
        void setPassword(const string& newPassword) {
            password = newPassword;
        }
        void ghivaofile(ofstream& ofs) const {
            ofs << id_user << " | " << username << " | " << password << " | " << role << endl;
        }

        void setRole(int newRole) {
            role = newRole;
        }

};
class USER_MANAGER{
    private:
        
        int idLonNhat; // Biến để lưu ID lớn nhất hiện tại
    public:
        vector<USER> list_user;
        USER_MANAGER() {
            idLonNhat = 0;
        }
    void docUserTuFile(const string& fileName) {
        ifstream fileUser(fileName);
        if (!fileUser) {
            cout << "Khong the mo file: " << fileName << endl;
            return;
        }

        string line;
        while (getline(fileUser, line)) {
            if (line.empty()) {
                continue; // Skip empty lines
            }

            stringstream ss(line);
            string idStr, roleStr;
            string username, password;

            // Tách các trường dựa trên ký tự '|'
            getline(ss, idStr, '|');
            getline(ss, username, '|');
            getline(ss, password, '|');
            getline(ss, roleStr, '|');

            if (idStr.empty() || username.empty() || password.empty() || roleStr.empty()) {
                cout << "Loi: Du lieu khong hop le trong file." << endl;
                continue;
            }

            try {
                // Chuyển đổi các trường số từ chuỗi sang giá trị số
                int id = stoi(idStr);
                int role = stoi(roleStr);
                if (id > idLonNhat) {
                    idLonNhat = id;
                }

                // Tạo đối tượng khách hàng
                USER user(id, username, password, role);
                list_user.push_back(user);
            } catch (const invalid_argument& e) {
                cout << "Loi: Khong the chuyen doi chuoi sang so. Du lieu khong hop le trong file." << endl;
            } catch (const out_of_range& e) {
                cout << "Loi: Gia tri so nam ngoai pham vi hop le." << endl;
            }
        }


        fileUser.close();
    }

        int capPhatID() {
            return ++idLonNhat;
        }

        USER* getUSER(int id) {
            for ( auto& user : list_user) {
                if (user.getId() == id) {
                    return &user;
                }
            }
            return new USER(-1, "", "", -1);
        }
        void ghiUserVaoFile(const string& fileName) {
            ofstream fileUser(fileName);
            if (!fileUser) {
                cout << "Khong the mo file: " << fileName << endl;
                return;
            }

            for (const auto& user : list_user) {
                fileUser << user.getId() << "|"
                         << user.getUsername() << "|"
                         << user.getPassword() << "|"
                         << user.getRole() << '\n';
            }

            fileUser.close();
        }
        void themUser(const USER& user) {
            int id = user.getId();
            list_user.push_back(user);
        }
        void xoaUser(int id) {
            for (auto it = list_user.begin(); it != list_user.end(); ++it) {
                if (it->getId() == id && it->getId()!=1) { // khong the xoa admin
                    list_user.erase(it);
                    cout << "Da xoa user voi ID: " << id << endl;
                    return;
                }
            }
            cout << "Khong tim thay user voi ID: " << id << endl;
        }
        USER login() {
            string username, password;
            cout << "Nhap username: "; cin >> username;
            cout << "Nhap password: "; cin >> password;
            for (const auto& user : list_user) {
                if (user.getUsername() == username && user.getPassword() == password) {
                    cout << "Dang nhap thanh cong.\n";
                    if(user.getRole() == 1) {
                        cout << "Ban la admin.\n";
                    } else {
                        cout << "Ban la user.\n";
                    }
                    return user;
                }
            }
            cout << "Dang nhap that bai. Vui long kiem tra lai username va password.\n";
            return USER(-1, "", "", -1);
        }
        void hienthiDanhSachUser() const {
            cout << left
                << setw(5) << "ID" << " | "
                << setw(20) << "Username" << " | "
                << setw(15) << "Password" << " | "
                << setw(15) << "Role" << endl;

            cout << setfill('-')
                << setw(5) << "-" << "-+-"
                << setw(20) << "-" << "-+-"
                << setw(15) << "-" << "-+-"
                << setw(15) << "-" << setfill(' ') << endl;

            for (const auto& user : list_user) {
                user.hienthiThongTin();
            }
        }
        void dangKy() {
            string username, password;
            cout << "Nhap username: "; cin >> username;
            cout << "Nhap password: "; cin >> password;
            if(username == "" || password == "") {
                cout << "Username hoac password khong duoc de trong.\n";
                return;
            }
            bool checkUsername = false;
            for (const auto& user : list_user) {
                if (user.getUsername() == username) {
                    checkUsername = true;
                    break;
                }
            }
            if (checkUsername) {
                cout << "Username da ton tai. Vui long chon username khac.\n";
                return;
            }
            USER user(capPhatID(), username, password, 0);
            themUser(user);
            cout << "Dang ky thanh cong.\n";
        }
    void thayDoi() {
        cout << "1. Thay doi quyen" << endl;
        cout << "2. Thay doi password" << endl;
        cout << "3. Xoa user" << endl;
        cout << "4. Hien thi danh sach user" << endl;
        cout << "0. Tro ve\n";
        
        int choice = getValidatedInput<int>("Nhap lua chon: ");
        if (choice == 0) {
            return;
        }

        if (choice != 4) {
            hienthiDanhSachUser();
            int id = getValidatedInput<int>("Nhap ID user: ");
            if (id == 1) {
                cout << "Khong the thay doi thong tin admin." << endl;
                return;
            }

            USER* user = getUSER(id);
            if (user == nullptr || user->getId() == -1) {
                cout << "Khong tim thay user voi ID: " << id << endl;
                return;
            }

            switch (choice) {
                case 1: {
                    int role;
                    cout << "1. Admin\n";
                    cout << "0. User\n";
                    role = getValidatedInput<int>("Nhap quyen moi: ");
                    if (role != 0 && role != 1) {
                        cout << "Lua chon khong hop le. Vui long chon lai." << endl;
                    } else {
                        user->setRole(role);
                        cout << "Da cap nhat quyen cho user voi ID: " << id << endl;
                    }
                    break;
                }
                case 2: {
                    string password;
                    cout << "Nhap password moi: ";
                    cin >> password;
                    user->setPassword(password);
                    cout << "Da cap nhat password cho user voi ID: " << id << endl;
                    break;
                }
                case 3: {
                    int choice2 = getValidatedInput<int>("Ban co chac chan muon xoa user nay khong? (1: Co, 0: Khong): ");
                    if (choice2 == 1) {
                        xoaUser(id);
                        cout << "Da xoa user voi ID: " << id << endl;
                    } else {
                        cout << "Huy xoa user." << endl;
                    }
                    break;
                }
                default:
                    cout << "Lua chon khong hop le. Vui long chon lai." << endl;
                    break;
            }
        } else {
            hienthiDanhSachUser();
        }
    }

};
#endif 
