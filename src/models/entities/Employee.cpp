#include "models/entities/Employee.h"

// 1. Cập nhật Constructor
Employee::Employee(std::string id, std::string name, std::string phone,
                   std::string password, std::string role, bool active, double salary)
    : Person(id, name, phone), password(password), role(role), active(active), hourlySalary(salary) {
    // Person(id, name, phone) gọi hàm khởi tạo của lớp cha
}

// --- Các hàm lấy thông tin (Getters) ---
std::string Employee::getPassword() const { return password; }
std::string Employee::getRole() const { return role; }
bool Employee::isActive() const { return active; }
double Employee::getHourlySalary() const { return hourlySalary; }

// --- Các hàm cập nhật thông tin (Setters) ---
void Employee::setPassword(const std::string& pass) { this->password = pass; }
void Employee::setRole(const std::string& role) { this->role = role; }
void Employee::setActive(bool status) { this->active = status; }
void Employee::setHourlySalary(double salary) { this->hourlySalary = salary; }
