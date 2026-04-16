#include "views/EmployeeView.h"
#include "utils/InputUtils.h"
#include "utils/StringUtils.h"
#include <iostream>
#include <iomanip>
#include <limits>

// 1. Menu quản lý nhân sự
void EmployeeView::displayPersonnelMenu() {
    std::cout << "\n==========================================";
    std::cout << "\n   [ADMIN] - QUẢN LÝ NHÂN VIÊN";
    std::cout << "\n==========================================";
    std::cout << "\n1. Danh sách nhân viên (Xem lương & Role)";
    std::cout << "\n2. Thêm nhân viên mới (Nạp đủ các thông tin)";
    std::cout << "\n3. Cập nhật Quyền / Mật khẩu";
    std::cout << "\n4. Khóa tài khoản (Cho nghỉ việc)";
    std::cout << "\n5. Mở khóa tài khoản";
    std::cout << "\n0. Quay lại Menu chính";
    std::cout << "\n------------------------------------------\n";
}

// 2. Hiển thị danh sách
void EmployeeView::displayEmployeeList(const std::vector<Employee>& employees) {
    std::cout << "\n" << StringUtils::padRight("MÃ NV", 8)
              << StringUtils::padRight("HỌ TÊN", 25)
              << StringUtils::padRight("SĐT", 15)
              << StringUtils::padRight("CHỨC VỤ", 15)
              << StringUtils::padRight("TÌNH TRẠNG", 15)
              << "LƯƠNG CƠ BẢN (VNĐ)\n";
    std::cout << std::string(95, '-') << "\n";

    for (const auto& emp : employees) {
        std::string status = emp.isActive() ? "Dang lam" : "Bi khoa";
        long long totalSalary = (long long)emp.getHourlySalary();

        std::cout << StringUtils::padRight(emp.getId(), 8)
                  << StringUtils::padRight(emp.getName().substr(0, 24), 25) 
                  << StringUtils::padRight(emp.getPhone(), 15)
                  << StringUtils::padRight(emp.getRole(), 15)
                  << StringUtils::padRight(status, 15)
                  << totalSalary << "\n";
    }
    std::cout << std::string(95, '-') << "\n";
}

// 3. Nhập liệu nhân viên mới
Employee EmployeeView::getInputForNewEmployee(std::string id) {
    std::string name, phone, pass, role;
    double salary;

    std::cout << "\n--- THÊM NHÂN VIÊN MỚI ---" << std::endl;
    std::cout << "(Gõ '-1' hoặc 'CANCEL' để hủy tiến trình)\n";

    name = InputUtils::getValidName("Họ tên: ");
    if (name == "CANCEL") return Employee("", "", "", "", "", false, 0, 0);

    phone = InputUtils::getValidPhone("Số điện thoại: ");
    if (phone == "CANCEL") return Employee("", "", "", "", "", false, 0, 0);

    pass = InputUtils::getValidString("Mật khẩu: ");
    if (pass == "CANCEL") return Employee("", "", "", "", "", false, 0, 0);

    role = StringUtils::toTitleCase(InputUtils::getValidString("Chức vụ (Admin/Staff/Purchasing): "));
    if (role == "Cancel") return Employee("", "", "", "", "", false, 0);

    return Employee(id, name, phone, pass, role, true, 0);
}

std::string EmployeeView::getInputEmployeeId() {
    return InputUtils::getValidString("Nhập mã Nhân Viên: ");
}

std::string EmployeeView::getInputNewRole() {
    return StringUtils::toTitleCase(InputUtils::getValidString("Nhập chức vụ mới (Admin/Staff/Purchasing): "));
}

std::string EmployeeView::getInputNewPassword() {
    return InputUtils::getValidString("Nhập mật khẩu mới: ");
}

void EmployeeView::displayMessage(std::string message) {
    std::cout << "=> [Thông báo]: " << message << "\n";
}