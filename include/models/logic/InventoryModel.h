#ifndef DUANQLSIEUTHI_INVENTORYMODEL_H
#define DUANQLSIEUTHI_INVENTORYMODEL_H

#pragma once
#include "models/entities/Product.h"
#include <vector>
#include <string>

class InventoryModel {
private:
    std::string dataPath = "../data/1_inventory/products.csv";
    std::vector<Product> productList;

public:
    InventoryModel();

    void loadProducts();
    void saveProducts();
    bool addProduct(const Product& product);
    std::vector<Product> getAllProducts();

    // CẬP NHẬT: Thêm tham số newCostPrice vào đây
    void updateProduct(std::string id, double newCostPrice, double newSellingPrice, int newQty);

    void deleteProduct(std::string id);
    std::vector<Product> searchProducts(std::string keyword);
    void sortProducts();

    bool sellProduct(std::string id, int qty);
    void deleteProductWithReason(std::string id, int reasonCode);
    std::vector<Product> getExpiredProducts();
    std::vector<Product> getFreshProductsToCheck();
    double getDiscountRate(Product& p);
    std::vector<Product> getDiscountedProducts();
};

#endif