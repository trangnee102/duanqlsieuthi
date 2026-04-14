#include "utils/InputUtils.h"
#include "utils/StringUtils.h"
#include <iostream>
#include <limits>
#include <algorithm>

// Giúp xóa sạch các ký tự lỗi bị kẹt trong cin
void clearCin() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int InputUtils::getValidInt(std::string prompt, int minVal, int maxVal) {
    int value;
    std::string input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        // Cơ chế LỐI THOÁT
        if (input == "-1" || input == "CANCEL" || input == "cancel") {
            clearCin();
            return -1;
        }

        try {
            value = std::stoi(input);
            if (value >= minVal && value <= maxVal) {
                // Xóa phần thừa (nếu người dùng gõ số kèm chữ như '12abc')
                clearCin();
                return value;
            } else {
                std::cout << "\t[Loi] Vui long nhap so tu " << minVal << " den " << maxVal << "!\n";
            }
        } catch (const std::exception& e) {
            std::cout << "\t[Loi] Sai dinh dang! Vui long nhap so nguyen hoac go '-1' de HUY.\n";
        }
        clearCin();
    }
}

double InputUtils::getValidDouble(std::string prompt, double minVal) {
    double value;
    std::string input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (input == "-1" || input == "CANCEL" || input == "cancel") {
            clearCin();
            return -1.0;
        }

        try {
            value = std::stod(input);
            if (value >= minVal) {
                clearCin();
                return value;
            } else {
                std::cout << "\t[Loi] Vui long nhap so lon hon hoac bang " << minVal << "!\n";
            }
        } catch (const std::exception& e) {
            std::cout << "\t[Loi] Sai dinh dang! Vui long nhap so hoac go '-1' de HUY.\n";
        }
        clearCin();
    }
}

std::string InputUtils::getValidString(std::string prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);

        if (value == "-1" || value == "CANCEL" || value == "cancel") {
            return "CANCEL";
        }

        if (value.empty()) {
            std::cout << "\t[Loi] Khong duoc de trong! Tiep luc hoac go '-1' de HUY.\n";
            continue;
        }

        if (value.find(',') != std::string::npos) {
            std::cout << "\t[Loi] Khong duoc phap chua dau phay ',' vi se lam hong file luu tru!\n";
            continue;
        }

        return value;
    }
}

// Hàm bổ trợ kiểm tra ký tự rác
bool containsInvalidChars(const std::string& str) {
    // Tiếng Việt UTF-8 khá phức tạp nên mình chỉ chặn các dấu nguy hiểm và các con số.
    for (char c : str) {
        if (isdigit((unsigned char)c)) return true; // Cấm số 0-9
        if (c == '!' || c == '@' || c == '#' || c == '$' || c == '%' ||
            c == '^' || c == '&' || c == '*' || c == '(' || c == ')' ||
            c == '+' || c == '=' || c == '<' || c == '>' || c == '?' ||
            c == '/' || c == '\\' || c == '|' || c == '{' || c == '}' ||
            c == '[' || c == ']' || c == '~' || c == '`' || c == ',' || c == '"') {
            return true;
        }
    }
    return false;
}

std::string InputUtils::getValidName(std::string prompt) {
    std::string value;
    while (true) {
        value = getValidString(prompt);
        if (value == "CANCEL") return "CANCEL";

        if (containsInvalidChars(value)) {
            std::cout << "\t[Lỗi] Tên không được chứa Chữ số (0-9) hay Ký tự đặc biệt! Vui lòng nhập lại.\n";
            continue;
        }
        return StringUtils::toTitleCase(value);
    }
}

std::string InputUtils::getValidPhone(std::string prompt) {
    std::string value;
    while (true) {
        value = getValidString(prompt);
        if (value == "CANCEL") return "CANCEL";

        // Check if all characters are digits
        bool isAllDigits = true;
        for (char c : value) {
            if (!isdigit((unsigned char)c)) {
                isAllDigits = false; break;
            }
        }
        if (!isAllDigits) {
            std::cout << "\t[Lỗi] Số điện thoại CHỈ được phép chứa các chữ số (0-9)!\n";
            continue;
        }
        
        // Check length and start digit
        if (value.length() < 9 || value.length() > 11) {
            std::cout << "\t[Lỗi] Số điện thoại phải có độ dài từ 9 đến 11 chữ số!\n";
            continue;
        }
        if (value[0] != '0') {
            std::cout << "\t[Lỗi] Số điện thoại phải bắt đầu bằng số 0!\n";
            continue;
        }

        return value;
    }
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

std::string InputUtils::getValidDate(std::string prompt) {
    std::string value;
    while (true) {
        value = getValidString(prompt);
        if (value == "CANCEL") return "CANCEL";

        if (value.length() != 10 || value[4] != '-' || value[7] != '-') {
            std::cout << "\t[Lỗi] Sai định dạng ngày! Yêu cầu: YYYY-MM-DD (VD: 2025-05-20)\n";
            continue;
        }

        try {
            int year = std::stoi(value.substr(0, 4));
            int month = std::stoi(value.substr(5, 2));
            int day = std::stoi(value.substr(8, 2));

            if (year < 1900 || year > 2100) {
                std::cout << "\t[Lỗi] Năm không hợp lý (Khoảng 1900 - 2100)!\n";
                continue;
            }
            if (month < 1 || month > 12) {
                std::cout << "\t[Lỗi] Tháng chỉ được nằm trong khoảng 1 đến 12!\n";
                continue;
            }

            int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
            if (isLeapYear(year)) {
                daysInMonth[1] = 29;
            }

            if (day < 1 || day > daysInMonth[month - 1]) {
                std::cout << "\t[Lỗi] Sai ngày! Tháng " << month << " năm " << year << " chỉ có " << daysInMonth[month - 1] << " ngày.\n";
                continue;
            }

            return value;
        } catch (const std::exception&) {
            std::cout << "\t[Lỗi] Ngày tháng phải là các con số hợp lệ!\n";
        }
    }
}
