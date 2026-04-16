#ifndef DUANQLSIEUTHI_CUSTOMER_H
#define DUANQLSIEUTHI_CUSTOMER_H

#pragma once
#include "Person.h"
#include <string>

// Kế thừa public từ Person
class Customer : public Person {
private:
    int points;
    std::string memberLevel; // Hạng thành viên: Đồng, Bạc, Vàng

    // Hàm nội bộ tự động tính toán nâng hạng khi điểm tăng
    void updateLevel();

public:
    // Constructor (Khởi tạo khách hàng) - Truyền ID, Name, Phone lên cho Person
    Customer(std::string id, std::string name, std::string phone, int points = 0);

    // Getters riêng của Customer (Các hàm lấy ID, Name, Phone đã được kế thừa từ Person)
    int getPoints() const;
    std::string getMemberLevel() const;

    // Các hàm thay đổi thông tin (Setters / Actions)
    void addPoints(int p);
    double getDiscountRate() const;
};

#endif //DUANQLSIEUTHI_CUSTOMER_H