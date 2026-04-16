#ifndef DUANQLSIEUTHI_INVENTORYVIEW_H
#define DUANQLSIEUTHI_INVENTORYVIEW_H

#pragma once
#include "models/entities/Product.h"
#include "models/entities/Customer.h"
#include <vector>
#include <string>

class InventoryView {
public:
    // --- Các Menu điều hướng hệ thống ---
    void displayAdminMenu();
    void displayStaffMenu();
    void displayPurchasingMenu();

    // --- Các hàm hiển thị dữ liệu ---
    // Hiển thị định dạng SL Lô / Tổng kho (VD: 100(250))
    void displayProductList(const std::vector<Product>& products, bool isManager, const std::vector<std::string>& qtyStrings);

    // [THÊM MỚI]: Khai báo hàm hiển thị riêng cho Kho Lưu Trữ (Hàng đã ngừng bán)
    void displayDisposedProductList(const std::vector<Product>& products, bool isManager, const std::vector<std::string>& qtyStrings);

    void displayMessage(std::string message);

    // Hiển thị hàng giảm giá kèm SL chi tiết
    void displayDiscountedProducts(const std::vector<Product>& products, const std::vector<std::string>& qtyStrings);

    void displayRevenueReport(long long totalRevenue, int totalItemsSold, long long totalProfit);

    // --- Các hàm nhập liệu từ bàn phím ---

    // [BẢN VÁ]: Nhận tên đã check trùng từ Controller
    Product getInputForNewProduct(std::string id, std::string name, const std::vector<std::string>& categories, std::string& outHsd);

    void getInputForNewBatch(const Product& p, std::string& hsd, int& qty);
    int getInputForDeleteReason();
    Customer getInputForNewCustomer(std::string id);
};

#endif // DUANQLSIEUTHI_INVENTORYVIEW_H