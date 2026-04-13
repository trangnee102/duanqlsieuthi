#include "utils/InputUtils.h"
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
