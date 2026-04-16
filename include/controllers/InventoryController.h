#ifndef DUANQLSIEUTHI_INVENTORYCONTROLLER_H
#define DUANQLSIEUTHI_INVENTORYCONTROLLER_H

#pragma once
#include <vector>
#include <string>
#include "models/entities/Employee.h"
#include "models/logic/InventoryModel.h"
#include "models/logic/CustomerModel.h"
#include "models/logic/CategoryModel.h"
#include "models/logic/TransactionModel.h" // Cực kỳ quan trọng: Để dùng chung struct CartItem từ đây
#include "views/InventoryView.h"

// Forward declaration: Giúp trình biên dịch nhận diện class nhanh hơn
class InventoryView;

class InventoryController {
private:
    // Các thành phần logic và giao diện (Thiết kế theo mô hình MVC)
    InventoryModel& model;
    InventoryView& view;
    CustomerModel& customerModel;
    CategoryModel& categoryModel;

public:
    /**
     * @brief Constructor khởi tạo bộ điều phối quản lý kho và bán hàng
     * @param m InventoryModel - Xử lý nghiệp vụ kho
     * @param v InventoryView - Hiển thị giao diện điều khiển
     * @param cm CustomerModel - Quản lý hội viên VIP
     * @param catM CategoryModel - Quản lý các ngành hàng
     */
    InventoryController(InventoryModel& m, InventoryView& v, CustomerModel& cm, CategoryModel& catM);

    /**
     * @brief Hàm chạy vòng lặp chính của hệ thống quản lý siêu thị
     * @param currentUser Nhân viên đang đăng nhập để kiểm soát quyền hạn (Admin/Staff)
     */
    void run(Employee* currentUser);
};

#endif // DUANQLSIEUTHI_INVENTORYCONTROLLER_H