#ifndef DUANQLSIEUTHI_EMPLOYEE_H
#define DUANQLSIEUTHI_EMPLOYEE_H

#pragma once
#include "models/entities/Person.h"
#include <string>

// Employee kế thừa từ Person (lấy ID, Name, Phone)
class Employee : public Person {
private:
    std::string password;
    std::string role;       // Admin, Staff, hoặc Purchasing
    bool active;            // Trạng thái tài khoản (true: đang làm)
    double hourlySalary;    // Lương

public:
    // CẬP NHẬT: Constructor nạp đủ 7 tham số
    Employee(std::string id, std::string name, std::string phone,
             std::string password, std::string role, bool active, double salary);

    // Nhóm hàm lấy thông tin (Getters)
    std::string getPassword() const;
    std::string getRole() const;
    bool isActive() const;
    double getHourlySalary() const;

    // Nhóm hàm cập nhật (Setters)
    void setPassword(const std::string& pass);
    void setRole(const std::string& newRole);
    void setActive(bool status);
    void setHourlySalary(double salary);



#endif