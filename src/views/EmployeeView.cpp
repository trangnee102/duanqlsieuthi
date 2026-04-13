#include "views/EmployeeView.h"
#include "utils/InputUtils.h"
#include <iostream>
#include <iomanip>
#include <limits>

// 1. Menu quản lý nhân sự
void EmployeeView::displayPersonnelMenu() {
    std::cout << "\n==========================================";
    std::cout << "\n   [ADMIN] - QUAN LY NHAN VIEN";
    std::cout << "\n==========================================";
    std::cout << "\n1. Danh sach nhan vien (Xem luong & Role)";
    std::cout << "\n2. Them nhan vien moi (Nap du cac thong tin)";
    std::cout << "\n3. Cap nhat Quyen / Mat khau";
    std::cout << "\n4. Khoa tai khoan (Cho nghi viec)";
    std::cout << "\n5. Cham cong nhan vien";
    std::cout << "\n0. Quay lai Menu chinh";
    std::cout << "\n------------------------------------------";
    std::cout << "\nLua chon cua ban: ";
}

// 2. Hiển thị danh sách: Thêm cột Giờ Công & Tổng Lương
void EmployeeView::displayEmployeeList(const std::vector<Employee>& employees) {
    std::cout << "\n" << std::left << std::setw(8) << "MA NV"
              << std::setw(18) << "HO TEN"
              << std::setw(12) << "CHUC VU"
              << std::setw(10) << "LUONG/H"
              << std::setw(8)  << "GIO"
              << std::setw(15) << "TONG LUONG"
              << std::setw(12) << "TRANG THAI" << "\n";
    std::cout << std::string(85, '-') << "\n";

    for (const auto& emp : employees) {
        std::string status = emp.isActive() ? "Dang lam" : "Da nghi";
        std::cout << std::left << std::setw(8) << emp.getId()
                  << std::setw(18) << emp.getName()
                  << std::setw(12) << emp.getRole()
                  << std::setw(10) << (long long)emp.getHourlySalary()
                  << std::setw(8)  << emp.getWorkingHours()
                  << std::setw(15) << emp.calculateTotalSalary()
                  << std::setw(12) << status << "\n";
    }
    std::cout << std::string(85, '-') << "\n";
}

// 3. Nhập liệu nhân viên mới
Employee EmployeeView::getInputForNewEmployee() {
    std::string id, name, phone, pass, role;
    double salary;

    std::cout << "\n--- THEM NHAN VIEN MOI ---" << std::endl;
    std::cout << "(Go '-1' hoac 'CANCEL' de huy tien trinh)\n";

    id = InputUtils::getValidString("Ma NV moi: ");
    if (id == "CANCEL") return Employee("", "", "", "", "", false, 0, 0);

    name = InputUtils::getValidString("Ho ten: ");
    if (name == "CANCEL") return Employee("", "", "", "", "", false, 0, 0);

    phone = InputUtils::getValidString("So dien thoai: ");
    if (phone == "CANCEL") return Employee("", "", "", "", "", false, 0, 0);

    pass = InputUtils::getValidString("Mat khau: ");
    if (pass == "CANCEL") return Employee("", "", "", "", "", false, 0, 0);

    role = InputUtils::getValidString("Chuc vu (Admin/Staff/Purchasing): ");
    if (role == "CANCEL") return Employee("", "", "", "", "", false, 0, 0);

    salary = InputUtils::getValidDouble("Muc luong moi gio (hourly rate): ", 0.0);
    if (salary < 0) return Employee("", "", "", "", "", false, 0, 0);

    return Employee(id, name, phone, pass, role, true, salary, 0);
}

std::string EmployeeView::getInputEmployeeId() {
    return InputUtils::getValidString("Nhap Ma NV can thuc hien: ");
}

std::string EmployeeView::getInputNewRole() {
    return InputUtils::getValidString("Nhap Chuc vu moi (Admin/Staff/Purchasing): ");
}

std::string EmployeeView::getInputNewPassword() {
    return InputUtils::getValidString("Nhap Mat khau moi: ");
}

void EmployeeView::displayMessage(std::string message) {
    std::cout << "=> " << message << "\n";
}