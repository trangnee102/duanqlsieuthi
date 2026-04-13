#include "models/logic/AuthModel.h"
#include "utils/FileHandler.h"
#include <iostream>
#include <string>

AuthModel::AuthModel() {
    loadEmployees();
}

// 1. CẬP NHẬT: Đọc 8 cột từ file CSV (Thêm cột Giờ công)
void AuthModel::loadEmployees() {
    employeeList.clear();
    std::vector<std::string> lines = FileHandler::readLines(dataPath);

    if (lines.empty()) {
        std::cout << "[Auth-Debug] Khong co du lieu nhan vien!" << std::endl;
        return;
    }

    for (const auto& line : lines) {
        std::vector<std::string> tokens = FileHandler::split(line, ',');

        // KIỂM TRA: Phải có ít nhất 7 cột, nhưng ưu tiên đọc đủ 8 cột (nếu có)
        if (tokens.size() >= 7) {
            bool isActive = (tokens[5] == "1");
            double salary = std::stod(tokens[6]);

            // Nếu file có cột số 8 (giờ công) thì đọc, nếu không có thì mặc định là 0
            int hours = (tokens.size() >= 8) ? std::stoi(tokens[7]) : 0;

            // Gọi Constructor 8 tham số
            Employee emp(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], isActive, salary, hours);
            employeeList.push_back(emp);
        }
    }
}

// 2. CẬP NHẬT: Lưu đủ 8 cột xuống file CSV
void AuthModel::saveEmployees() {
    std::vector<std::string> lines;
    for (const auto& emp : employeeList) {
        std::string activeStr = emp.isActive() ? "1" : "0";
        std::string salaryStr = std::to_string((long long)emp.getHourlySalary());

        // Chuyển giờ công thành chuỗi để ghi file
        std::string hoursStr = std::to_string(emp.getWorkingHours());

        // Nối thêm cột Giờ công vào cuối cùng
        std::string line = emp.getId() + "," + emp.getName() + "," +
                           emp.getPhone() + "," + emp.getPassword() + "," +
                           emp.getRole() + "," + activeStr + "," + salaryStr + "," + hoursStr; // <== MỚI
        lines.push_back(line);
    }

    if (!FileHandler::writeLines(dataPath, lines)) {
        std::cout << "[Auth-Debug] LOI: Khong the ghi file nhan vien!" << std::endl;
    }
}

// 3. Đăng nhập
Employee* AuthModel::login(std::string id, std::string password) {
    for (auto& emp : employeeList) {
        if (emp.getId() == id && emp.getPassword() == password) {
            if (emp.isActive()) {
                return &emp;
            } else {
                std::cout << "=> [TB]: Tai khoan nay da bi khoa!" << std::endl;
                return nullptr;
            }
        }
    }
    return nullptr;
}

// --- CÁC HÀM QUẢN LÝ NHÂN SỰ ---

std::vector<Employee>& AuthModel::getAllEmployees() {
    return employeeList;
}

bool AuthModel::addEmployee(const Employee& emp) {
    for (const auto& existing : employeeList) {
        if (existing.getId() == emp.getId()) {
            return false; // Trùng lặp
        }
    }
    employeeList.push_back(emp);
    saveEmployees();
    return true;
}

void AuthModel::updateEmployee(std::string id, std::string newRole, std::string newPass) {
    for (auto& emp : employeeList) {
        if (emp.getId() == id) {
            emp.setRole(newRole);
            emp.setPassword(newPass);
            saveEmployees();
            return;
        }
    }
}

void AuthModel::deleteEmployee(std::string id) {
    for (auto& emp : employeeList) {
        if (emp.getId() == id) {
            emp.setActive(false);
            saveEmployees();
            return;
        }
    }
}

// ==========================================
// THÊM MỚI: Tính năng Chấm công & Tính Lương
// ==========================================
void AuthModel::updateWorkingHours(std::string id, int hours) {
    for (auto& emp : employeeList) {
        if (emp.getId() == id) {
            emp.addWorkingHours(hours); // Cộng dồn giờ làm thêm
            saveEmployees();            // Ghi đè file CSV ngay lập tức
            return;
        }
    }
}