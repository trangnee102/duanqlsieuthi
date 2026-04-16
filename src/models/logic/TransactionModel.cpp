//
// Created by admin on 4/16/2026.
//

#include "models/logic/TransactionModel.h"
#include "utils/FileHandler.h"
#include "utils/DateUtils.h"
#include <iostream>
#include <sstream>

// Hàm lưu hóa đơn vào file CSV
bool TransactionModel::saveTransaction(const std::string& customerPhone,
                                      const std::vector<CartItem>& items,
                                      double totalAmount,
                                      double voucherDiscount) {

    std::string path = "../data/2_transactions/history_transactions.csv";
    std::string today = DateUtils::getCurrentDate();

    // Tạo chuỗi danh sách sản phẩm để lưu vào 1 ô (ngăn cách bằng dấu |)
    // Định dạng: MãSP:SốLượng:Giá:GiảmGiá
    std::stringstream ssItems;
    for (size_t i = 0; i < items.size(); ++i) {
        ssItems << items[i].product.getId() << ":"
                << items[i].qty << ":"
                << (long long)items[i].product.getPrice() << ":"
                << (long long)items[i].discountAmount;
        if (i < items.size() - 1) ssItems << "|";
    }

    // Tạo dòng dữ liệu CSV
    // Cột: Ngày, SĐT_Khách, Danh_Sách_Món, Voucher_Giảm, Tổng_Cuối_Cùng
    std::string line = today + ","
                     + (customerPhone == "0" ? "Khach vang lai" : customerPhone) + ","
                     + ssItems.str() + ","
                     + std::to_string((long long)voucherDiscount) + ","
                     + std::to_string((long long)totalAmount);

    return FileHandler::appendLine(path, line);
}

// Hàm lấy tổng doanh thu (phục vụ Case 11 sau này)
double TransactionModel::getTotalRevenue() {
    std::string path = "../data/2_transactions/history_transactions.csv";
    std::vector<std::string> lines = FileHandler::readLines(path);
    double total = 0;
    for (const auto& line : lines) {
        if (line.empty()) continue;
        std::vector<std::string> tokens = FileHandler::split(line, ',');
        if (tokens.size() >= 5) {
            total += std::stod(tokens[4]); // Cột tổng tiền cuối cùng
        }
    }
    return total;
}