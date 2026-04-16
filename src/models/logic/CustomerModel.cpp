#include "models/logic/CustomerModel.h"
#include "utils/FileHandler.h"
#include <iostream>

CustomerModel::CustomerModel() {
    loadCustomers();
}

void CustomerModel::loadCustomers() {
    customerList.clear();
    std::vector<std::string> lines = FileHandler::readLines(dataPath);

    for (const auto& line : lines) {
        std::vector<std::string> tokens = FileHandler::split(line, ',');
        // File CSV khách hàng có 4 cột: ID, Tên, SĐT, Điểm
        if (tokens.size() >= 4) {
            Customer c(tokens[0], tokens[1], tokens[2], std::stoi(tokens[3]));
            customerList.push_back(c);
        }
    }
}

void CustomerModel::saveCustomers() {
    std::vector<std::string> lines;
    for (const auto& c : customerList) {
        std::string line = c.getId() + "," + c.getName() + "," +
                           c.getPhone() + "," + std::to_string(c.getPoints());
        lines.push_back(line);
    }
    FileHandler::writeLines(dataPath, lines);
}

bool CustomerModel::addCustomer(const Customer& customer) {
    for (const auto& c : customerList) {
        if (c.getId() == customer.getId() || c.getPhone() == customer.getPhone()) {
            return false; // Trùng ID hoặc trùng SĐT
        }
    }
    customerList.push_back(customer);
    saveCustomers();
    return true;
}

std::vector<Customer> CustomerModel::getAllCustomers() {
    return customerList;
}

// Hàm cực kỳ quan trọng: Tìm khách hàng khi họ đọc SĐT lúc thanh toán
Customer* CustomerModel::getCustomerByPhone(std::string phone) {
    for (auto& c : customerList) {
        if (c.getPhone() == phone) {
            return &c; // Trả về con trỏ (địa chỉ) của khách hàng đó
        }
    }
    return nullptr; // Không tìm thấy thì trả về null
}

// --- ĐÃ FIX: Dùng addPoints thay vì setPoints để khớp với Customer.h ---
void CustomerModel::updatePoints(const std::string& id, int newPoints) {
    for (auto& c : customerList) {
        if (c.getId() == id) {
            // Tính số điểm cần cộng thêm
            int currentPoints = c.getPoints();
            int pointsToAdd = newPoints - currentPoints;

            // Gọi hàm addPoints đã có sẵn trong class Customer của sếp
            c.addPoints(pointsToAdd);

            // Lưu lại vào file customers.csv
            saveCustomers();
            return;
        }
    }
}