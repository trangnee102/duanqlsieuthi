#ifndef TRANSACTIONMODEL_H
#define TRANSACTIONMODEL_H

#pragma once
#include <string>
#include <vector>
#include "../entities/Product.h"

/**
 * @brief Cấu trúc lưu thông tin món hàng trong giỏ hàng
 */
struct CartItem {
    Product product;
    int qty;
    double subTotal;
    double discountAmount;
};

struct Transaction {
    std::string date;
    std::string customer;
    std::string itemsStr;
    double voucher;
    double total;
};

class TransactionModel {
private:
    std::vector<Transaction> transactionList;
    std::string dataPath = "data/history_transactions.csv"; // Đường dẫn file của sếp

public:
    // Constructor
    TransactionModel() { loadTransactions(); }

    std::vector<Transaction>& getAllTransactions() { return transactionList; }
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