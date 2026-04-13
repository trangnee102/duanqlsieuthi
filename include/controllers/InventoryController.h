#ifndef DUANQLSIEUTHI_INVENTORYCONTROLLER_H
#define DUANQLSIEUTHI_INVENTORYCONTROLLER_H

#pragma once
#include "models/logic/InventoryModel.h"
#include "models/logic/CustomerModel.h"
#include "models/logic/CategoryModel.h"
#include "views/InventoryView.h"
#include "models/entities/Employee.h"
#include <vector> // Đảm bảo có thư viện này để dùng vector

// THÊM: Cấu trúc này để lưu thông tin từng món trong giỏ hàng
struct CartItem {
    Product product;
    int quantity;
    long long subTotal;
};

class InventoryController {
private:
    InventoryModel& model;
    InventoryView& view;
    CustomerModel& customerModel;
    CategoryModel& categoryModel;

public:
    InventoryController(InventoryModel& m, InventoryView& v, CustomerModel& cm, CategoryModel& catM);
    void run(Employee* currentUser);
};

#endif