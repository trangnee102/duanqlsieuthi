#ifndef DUANQLSIEUTHI_CUSTOMERMODEL_H
#define DUANQLSIEUTHI_CUSTOMERMODEL_H

#pragma once
#include "models/entities/Customer.h"
#include <vector>
#include <string>

class CustomerModel {
private:
    // Đường dẫn tới file lưu thông tin khách hàng
    std::string dataPath = "../data/4_customer/customers.csv";
    std::vector<Customer> customerList;

public:
    CustomerModel();

    // --- Quản lý dữ liệu file ---
    void loadCustomers();
    void saveCustomers();
    void updatePoints(const std::string& id, int newPoints);

    // --- Các thao tác cơ bản ---
    bool addCustomer(const Customer& customer);
    std::vector<Customer> getAllCustomers();

    // Tìm khách hàng bằng Số điện thoại (Khi thanh toán thu ngân thường hỏi SĐT)
    Customer* getCustomerByPhone(std::string phone);
};

#endif //DUANQLSIEUTHI_CUSTOMERMODEL_H