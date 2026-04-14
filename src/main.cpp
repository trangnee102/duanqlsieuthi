#include <iostream>
#include <string>
#include <windows.h>
#include "models/logic/AuthModel.h"
#include "models/logic/InventoryModel.h"
#include "models/logic/CustomerModel.h" 
#include "models/logic/CategoryModel.h" // <== THÊM DÒNG NÀY
#include "views/InventoryView.h"
#include "controllers/InventoryController.h"

// module quản lý nhân sự
#include "views/EmployeeView.h"
#include "controllers/EmployeeController.h"

int main() {
    // Kích hoạt Console đọc/ghi UTF-8 Tiếng Việt
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // 1. Khởi tạo các thành phần hệ thống
    AuthModel authModel;
    InventoryModel inventoryModel;
    CustomerModel customerModel;   
    CategoryModel categoryModel; // BỘ NÃO NGÀNH HÀNG
    InventoryView inventoryView;
    EmployeeView employeeView;

    // Cập nhật Controller: Truyền thêm categoryModel
    InventoryController inventoryController(inventoryModel, inventoryView, customerModel, categoryModel);
    EmployeeController employeeController(authModel, employeeView);

    std::string user_id, password;
    Employee* currentUser = nullptr;

    std::cout << "==========================================\n";
    std::cout << "   CHÀO MỪNG ĐẾN VỚI HỆ THỐNG SIÊU THỊ    \n";
    std::cout << "==========================================\n";

    // 2. Vòng lặp đăng nhập
    while (currentUser == nullptr) {
        std::cout << "\n[ ĐĂNG NHẬP HỆ THỐNG ]\n";
        std::cout << "Mã nhân viên: "; std::cin >> user_id;
        std::cout << "Mật khẩu: ";     std::cin >> password;

        int status = authModel.login(user_id, password, currentUser);

        if (status == 1) {
            std::cout << "\n=> Đăng nhập thành công! Chào mừng "
                      << currentUser->getName() << " (" << currentUser->getRole() << ")\n";
        } else if (status == 2) {
            std::cout << "\n=> [LỖI] Tài khoản này đã bị khóa bởi Quản lý!\n";
        } else {
            std::cout << "\n=> [LỖI] Sai tài khoản hoặc mật khẩu. Vui lòng thử lại!\n";
        }
    }

    // 3. MENU TỔNG DÀNH CHO ADMIN / STAFF
    int mainChoice;
    do {
        if (currentUser->getRole() == "Admin") {
            std::cout << "\n---------- MENU CHÍNH (QUẢN LÝ) ----------\n";
            std::cout << "1. Quản lý kho hàng\n";
            std::cout << "2. Quản lý nhân viên\n";
            std::cout << "0. Đăng xuất & Thoát hệ thống\n";
            std::cout << "------------------------------------------\n";
            std::cout << "Lựa chọn của bạn: ";

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
            std::cout << "\n=> Chuyển đến giao diện quản lý kho...\n";
            inventoryController.run(currentUser);
            mainChoice = 0;
        }
    } while (mainChoice != 0);

    std::cout << "\nHệ thống đang thoát... Tạm biệt " << currentUser->getName() << "!\n";
    return 0;
}