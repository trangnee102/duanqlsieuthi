//
// Created by admin on 4/16/2026.
//

#include "controllers/TransactionController.h"
#include <iostream>

TransactionController::TransactionController(TransactionModel& m) : model(m) {}

// Hàm thực hiện chốt đơn và lưu file
void TransactionController::processNewTransaction(const std::string& phone,
                                                 const std::vector<CartItem>& cart,
                                                 double total,
                                                 double vDiscount) {
    if (cart.empty()) return;

    if (model.saveTransaction(phone, cart, total, vDiscount)) {
        std::cout << "=> [Hệ thống]: Hóa đơn đã được tự động lưu vào lịch sử giao dịch.\n";
    } else {
        std::cout << "=> [LỖI]: Không thể lưu lịch sử giao dịch. Vui lòng kiểm tra lại thư mục data/2_transactions!\n";
    }
}