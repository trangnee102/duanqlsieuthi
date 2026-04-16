#include "models/logic/AuthModel.h"
#include "utils/FileHandler.h"
#include "utils/StringUtils.h"
#include <iostream>
#include <string>

AuthModel::AuthModel() {
    loadEmployees();
}

// 1. CẬP NHẬT: Đọc 7 cột từ file CSV
void AuthModel::loadEmployees() {
    employeeList.clear();
    std::vector<std::string> lines = FileHandler::readLines(dataPath);

    if (lines.empty()) {
        std::cout << "[Auth-Debug] Khong co du lieu nhan vien!" << std::endl;
        return;
    }

    for (const auto& line : lines) {
        std::vector<std::string> tokens = FileHandler::split(line, ',');

        if (tokens.size() >= 7) {
            bool isActive = (tokens[5] == "1");
            double salary = std::stod(tokens[6]);

            // Gọi Constructor 7 tham số
            Employee emp(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], isActive, salary);
            employeeList.push_back(emp);
        }
    }
}

// 2. CẬP NHẬT: Lưu 7 cột xuống file CSV
void AuthModel::saveEmployees() {
    std::vector<std::string> lines;
    for (const auto& emp : employeeList) {
        std::string activeStr = emp.isActive() ? "1" : "0";
        std::string salaryStr = std::to_string((long long)emp.getHourlySalary());

        // Nối 7 cột
        std::string line = emp.getId() + "," + emp.getName() + "," +
                           emp.getPhone() + "," + emp.getPassword() + "," +
                           emp.getRole() + "," + activeStr + "," + salaryStr; 
        lines.push_back(line);
    }

    if (!FileHandler::writeLines(dataPath, lines)) {
        std::cout << "[Auth-Debug] LOI: Khong the ghi file nhan vien!" << std::endl;
    }
}

// 3. Đăng nhập
int AuthModel::login(std::string id, std::string password, Employee*& userPtr) {
    for (auto& emp : employeeList) {
        if (StringUtils::toLowerCase(emp.getId()) == StringUtils::toLowerCase(id)) {
            if (emp.getPassword() == password) {
                if (emp.isActive()) {
                    userPtr = &emp;
                    return 1; // Thành công
                } else {
                    return 2; // Bị khóa
                }
            } else {
                return 0; // Sai mật khẩu
            }
        }
    }
    return 0; // Sai tài khoản
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
    
    Employee newEmp = emp;
    std::string lowerRole = StringUtils::toLowerCase(newEmp.getRole());
    if (lowerRole == "admin") newEmp.setHourlySalary(200000);
    else if (lowerRole == "purchasing") newEmp.setHourlySalary(60000);
    else newEmp.setHourlySalary(50000);

    employeeList.push_back(newEmp);
    saveEmployees();
    return true;
}

void AuthModel::updateEmployee(std::string id, std::string newRole, std::string newPass) {
    for (auto& emp : employeeList) {
        if (emp.getId() == id) {
            emp.setRole(newRole);
            emp.setPassword(newPass);
            
            std::string lowerRole = StringUtils::toLowerCase(newRole);
            if (lowerRole == "admin") emp.setHourlySalary(200000);
            else if (lowerRole == "purchasing") emp.setHourlySalary(60000);
            else emp.setHourlySalary(50000);

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

void AuthModel::unlockEmployee(std::string id) {
    for (auto& emp : employeeList) {
        if (emp.getId() == id) {
            emp.setActive(true);
            saveEmployees();
            return;
        }
    }
}
