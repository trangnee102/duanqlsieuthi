#ifndef DUANQLSIEUTHI_INVENTORYVIEW_H
#define DUANQLSIEUTHI_INVENTORYVIEW_H

#pragma once
#include "models/entities/Product.h"
#include "models/entities/Customer.h"
#include <vector>
#include <string>

class InventoryView {
public:
    // Menu điều khiển cho 3 Role (Admin, Staff, Purchasing)
    void displayAdminMenu();
    void displayStaffMenu();
    void displayPurchasingMenu();

    // CẬP NHẬT: Hiển thị danh sách (Có thêm bool isManager để ẩn/hiện Giá Nhập)
    void displayProductList(const std::vector<Product>& products, bool isManager = false);

    // Bắt buộc chọn ngành từ danh sách
    Product getInputForNewProduct(std::string id, const std::vector<std::string>& categories);

    int getInputForDeleteReason();

    void displayMessage(std::string message);

    // --- Tính năng Khuyến mãi cận Date ---
    void displayDiscountedProducts(const std::vector<Product>& products);
    Customer getInputForNewCustomer(std::string id); // Cập nhật tham số id
    void displayRevenueReport(long long totalRevenue, int totalItemsSold, long long totalProfit);
};

#endif