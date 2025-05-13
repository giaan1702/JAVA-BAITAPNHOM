// utils.h
#ifndef func_h
#define func_h

#include <iostream>
#include <limits>
#include <string>

using namespace std;

template <typename T>
T getValidatedInput(const string& prompt) {
    T input;
    while (true) {
        cout << prompt;
        cin >> input;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any extra input
            return input;
        }
    }
}
// string toLower(const string& str) {
//     string lowerStr;
//     for (char c : str) {
//         if (isalpha(c)) { // Kiểm tra nếu là chữ cái
//             lowerStr += tolower(c);
//         } else {
//             lowerStr += c; // Giữ nguyên các ký tự khác
//         }
//     }
//     return lowerStr;
// }
#endif
