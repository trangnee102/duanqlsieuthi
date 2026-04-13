#ifndef DUANQLSIEUTHI_AUTHMODEL_H
#define DUANQLSIEUTHI_AUTHMODEL_H

#pragma once
#include "models/entities/Employee.h"
#include <vector>
#include <string>

class AuthModel {
private:
    std::string dataPath = "../data/6_admin/employees.csv"; // Sửa lại đường dẫn cho đúng nếu cần
    std::vector<Employee> employeeList;

public:
    AuthModel();

    // Quản lý dữ liệu file
    void loadEmployees();
    void saveEmployees();

    // Chức năng Đăng nhập
    Employee* login(std::string id, std::string password);

    // === CÁC TÍNH NĂNG QUẢN LÝ NHÂN VIÊN MỚI ===
    std::vector<Employee>& getAllEmployees();
    bool addEmployee(const Employee& emp);
    void updateEmployee(std::string id, std::string newRole, std::string newPass);
    void deleteEmployee(std::string id);

    // ==========================================
    // THÊM MỚI: Tính năng Chấm công
    // ==========================================
    void updateWorkingHours(std::string id, int hours); // <== DÒNG MÀ MÁY TÍNH ĐANG ĐÒI NÈ
};

#endif //DUANQLSIEUTHI_AUTHMODEL_H