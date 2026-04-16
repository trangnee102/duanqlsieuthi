#ifndef TRANSACTIONMODEL_H
#define TRANSACTIONMODEL_H

#pragma once
#include <string>
#include <vector>
#include "models/entities/Product.h"
#include "models/entities/Transaction.h" // <== BẮT BUỘC PHẢI CÓ DÒNG NÀY

/**
 * @brief Cấu trúc lưu thông tin món hàng trong giỏ hàng
 */
struct CartItem {
    Product product;
    int qty;
    double subTotal;
    double discountAmount;
};

class TransactionModel {
private:
    std::vector<Transaction> transactionList; // <== CÁI KÉT ĐỰNG DỮ LIỆU ĐÂY
    std::string dataPath = "data/history_transactions.csv"; // Đường dẫn file của sếp

public:
    // Constructor: Tự động nạp dữ liệu khi sếp gọi TransactionModel reportModel;
    TransactionModel() { loadTransactions(); }

    // Hàm lấy danh sách để Case 11 dùng
    std::vector<Transaction> getTransactions() const { return transactionList; }

    /**
     * @brief Nạp dữ liệu từ file CSV lên RAM
     */
    void loadTransactions();

    /**
     * @brief Thực hiện lưu hóa đơn xuống file
     */
    bool saveTransaction(const std::string& customerPhone,
                          const std::vector<CartItem>& items,
                          double totalAmount,
                          double voucherDiscount);

    /**
     * @brief Tính tổng doanh thu
     */
    double getTotalRevenue();
};

#endif // TRANSACTIONMODEL_H