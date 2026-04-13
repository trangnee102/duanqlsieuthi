//
// Created by admin on 4/10/2026.
//

#ifndef DUANQLSIEUTHI_EMPLOYEEVIEW_H
#define DUANQLSIEUTHI_EMPLOYEEVIEW_H

#pragma once
#include "models/entities/Employee.h"
#include <vector>
#include <string>

class EmployeeView {
public:
    // 1. Hiển thị Menu quản lý nhân sự
    void displayPersonnelMenu();

    // 2. Hiển thị bảng danh sách nhân viên
    void displayEmployeeList(const std::vector<Employee>& employees);

    // 3. Lấy thông tin để tạo nhân viên mới
    Employee getInputForNewEmployee(std::string id);

    // 4. Các hàm lấy thông tin đơn lẻ để sửa/xóa
    std::string getInputEmployeeId();
    std::string getInputNewRole();
    std::string getInputNewPassword();

    // 5. Thông báo
    void displayMessage(std::string message);
};

#endif //DUANQLSIEUTHI_EMPLOYEEVIEW_H