#ifndef TRANSACTIONCONTROLLER_H
#define TRANSACTIONCONTROLLER_H

#include "models/logic/TransactionModel.h"
#include <string>
#include <vector>

class TransactionController {
private:
    TransactionModel& model;

public:
    TransactionController(TransactionModel& m);

    // Nhận dữ liệu giỏ hàng đã thanh toán và gọi Model để lưu
    void processNewTransaction(const std::string& phone, const std::vector<CartItem>& cart, double total, double vDiscount);
};

#endif // TRANSACTIONCONTROLLER_H