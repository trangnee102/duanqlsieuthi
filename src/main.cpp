#include <iostream>
#include <string>
#include <windows.h>
#include "models/logic/AuthModel.h"
#include "models/logic/InventoryModel.h"
#include "models/logic/CustomerModel.h" // <== THÊM DÒNG NÀY
#include "views/InventoryView.h"
#include "controllers/InventoryController.h"

// module quản lý nhân sự
#include "views/EmployeeView.h"
#include "controllers/EmployeeController.h"

int main() {
    // Kích hoạt Console đọc UTF-8 Tiếng Việt
    SetConsoleOutputCP(CP_UTF8);

    // 1. Khởi tạo các thành phần hệ thống
    AuthModel authModel;
    InventoryModel inventoryModel;
    CustomerModel customerModel;   // <== THÊM DÒNG NÀY (Bộ não khách hàng)
    InventoryView inventoryView;
    EmployeeView employeeView;

    // Cập nhật Controller: Truyền thêm customerModel vào cuối
    InventoryController inventoryController(inventoryModel, inventoryView, customerModel);
    EmployeeController employeeController(authModel, employeeView);

    std::string user_id, password;
    Employee* currentUser = nullptr;

    std::cout << "==========================================\n";
    std::cout << "   CHAO MUNG DEN VOI HE THONG SIEU THI    \n";
    std::cout << "==========================================\n";

    // 2. Vòng lặp đăng nhập
    while (currentUser == nullptr) {
        std::cout << "\n[ DANG NHAP HE THONG ]\n";
        std::cout << "Ma nhan vien: "; std::cin >> user_id;
        std::cout << "Mat khau: ";     std::cin >> password;

        currentUser = authModel.login(user_id, password);

        if (currentUser != nullptr) {
            std::cout << "\n=> Dang nhap thanh cong! Chao mung "
                      << currentUser->getName() << " (" << currentUser->getRole() << ")\n";
        } else {
            std::cout << "\n=> [LOI] Sai tai khoan hoac mat khau. Vui long thu lai!\n";
        }
    }

    // 3. MENU TỔNG DÀNH CHO ADMIN / STAFF
    int mainChoice;
    do {
        if (currentUser->getRole() == "Admin") {
            std::cout << "\n---------- MENU CHINH (QUAN LY) ----------\n";
            std::cout << "1. Quan ly kho hang\n";
            std::cout << "2. Quan ly nhan vien\n";
            std::cout << "0. Dang xuat & Thoat he thong\n";
            std::cout << "------------------------------------------\n";
            std::cout << "Lua chon cua ban: ";

            if (!(std::cin >> mainChoice)) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                mainChoice = -1;
                continue;
            }

            if (mainChoice == 1) {
                inventoryController.run(currentUser);
            } else if (mainChoice == 2) {
                employeeController.run(currentUser);
            }
        } else {
            // Nếu là Staff, đưa thẳng vào quản lý kho
            std::cout << "\n=> Chuyen den giao dien quan ly kho...\n";
            inventoryController.run(currentUser);
            mainChoice = 0;
        }
    } while (mainChoice != 0);

    std::cout << "\nHe thong dang thoat... Tam biet " << currentUser->getName() << "!\n";
    return 0;
}