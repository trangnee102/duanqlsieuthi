#ifndef DUANQLSIEUTHI_BATCH_H
#define DUANQLSIEUTHI_BATCH_H

#pragma once
#include <string>

/**
 * @struct Batch
 * @brief Đại diện cho một lô hàng cụ thể của sản phẩm trong kho.
 * CẬP NHẬT: Thêm batchId để hỗ trợ tính lợi nhuận chính xác theo từng đợt nhập.
 */
struct Batch {
    std::string batchId;    // MÃ LÔ (Mới): Ví dụ L00002_150426_01
    std::string productId;  // Mã SP liên kết
    std::string expiryDate; // Hạn sử dụng (YYYY-MM-DD hoặc "None")
    int quantity;           // Số lượng của lô này
    std::string importDate; // Ngày nhập kho

    // 1. Constructor đầy đủ 5 tham số (Dùng cho logic mới)
    Batch(std::string bId, std::string pId, std::string exp, int qty, std::string imp)
        : batchId(bId), productId(pId), expiryDate(exp), quantity(qty), importDate(imp) {}

    // 2. Constructor 4 tham số (Dùng để nạp dữ liệu cũ từ file CSV hoặc các bản cũ)
    Batch(std::string pId, std::string exp, int qty, std::string imp)
        : batchId("N/A"), productId(pId), expiryDate(exp), quantity(qty), importDate(imp) {}
};

#endif // DUANQLSIEUTHI_BATCH_H