#ifndef DUANQLSIEUTHI_INVENTORYMODEL_H
#define DUANQLSIEUTHI_INVENTORYMODEL_H

#pragma once
#include <vector>
#include <string>
#include "models/entities/Product.h"

class InventoryModel {
private:
    std::string dataPath = "../data/1_inventory/products.csv";
    std::string batchPath = "../data/1_inventory/batches.csv";
    // Thêm đường dẫn file kho lưu trữ
    std::string disposedPath = "../data/1_inventory/disposed_products.csv";
    std::vector<Product> productList;

public:
    InventoryModel();

    // --- Hệ thống nạp/lưu dữ liệu ---
    void loadProducts();
    void saveProducts();
    bool addProduct(const Product& product);
    std::vector<Product> getAllProducts();

    // Kiểm tra trùng Mã hoặc Tên (Check cả hàng Active và Inactive)
    bool isDuplicate(std::string id, std::string name);

    // --- Quản lý Lô hàng (Batches) ---
    void fixProductDates(std::string id, std::string newNSX, std::string newHSD);
    bool addNewBatch(std::string id, std::string hsd, int qty, std::string& outBatchId);
    int getFirstBatchQuantity(std::string id);

    // --- Nghiệp vụ kho ---
    void updateProduct(std::string id, double newCostPrice, double newSellingPrice);
    void deleteProduct(std::string id);
    void deleteProductWithReason(std::string id, int reasonCode);

    // Hồi sinh sản phẩm đã xóa mềm
    bool restoreProduct(std::string id, std::string hsd, int qty, std::string& outBatchId);

    std::vector<Product> searchProducts(std::string keyword);
    void sortProducts();

    // --- Bán hàng & Khuyến mãi ---
    bool sellProduct(std::string id, int qty);
    double checkVoucher(std::string code);

    // --- Lọc & Cảnh báo ---
    std::vector<Product> getExpiredProducts();
    std::vector<Product> getLowStockProducts(int threshold = 10);
    std::vector<Product> getFreshProductsToCheck();

    // Lấy danh sách hàng đã ngừng kinh doanh
    std::vector<Product> getDisposedProducts();

    double getDiscountRate(Product& p);
    std::vector<Product> getDiscountedProducts();
};

#endif // DUANQLSIEUTHI_INVENTORYMODEL_H