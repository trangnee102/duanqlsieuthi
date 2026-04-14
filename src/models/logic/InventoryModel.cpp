#include "models/logic/InventoryModel.h"
#include "utils/FileHandler.h"
#include "utils/DateUtils.h"
#include "utils/StringUtils.h"
#include <iostream>
#include <algorithm>
#include <string>

// Constructor: Tự động nạp dữ liệu từ file khi khởi tạo
InventoryModel::InventoryModel() {
    loadProducts();
}

// 1. Đọc dữ liệu từ file CSV (11 CỘT)
void InventoryModel::loadProducts() {
    productList.clear();
    std::vector<std::string> lines = FileHandler::readLines(dataPath);

    for (const auto& line : lines) {
        std::vector<std::string> tokens = FileHandler::split(line, ',');
        if (tokens.size() >= 11) {
            bool isActive = (tokens[6] == "1");
            Product p(tokens[0], tokens[1], tokens[2],
                      std::stod(tokens[3]), std::stod(tokens[4]), std::stoi(tokens[5]), isActive,
                      tokens[7], tokens[8], tokens[9], tokens[10]);
            productList.push_back(p);
        }
    }
}

// 2. Lưu dữ liệu (Ghi đủ 11 cột xuống file)
void InventoryModel::saveProducts() {
    std::vector<std::string> lines;
    for (const auto& p : productList) {
        std::string activeStr = p.isActive() ? "1" : "0";
        std::string line = p.getId() + "," + p.getName() + "," + p.getCategory() + "," +
                           std::to_string((long long)p.getCostPrice()) + "," +
                           std::to_string((long long)p.getPrice()) + "," +
                           std::to_string(p.getQuantity()) + "," +
                           activeStr + "," + p.getProductionDate() + "," + p.getExpiryDate() + "," +
                           p.getLastChecked() + "," + p.getNote();
        lines.push_back(line);
    }
    FileHandler::writeLines(dataPath, lines);
}

// 3. Cập nhật: Sửa cả Giá Nhập, Giá Bán và Số lượng
void InventoryModel::updateProduct(std::string id, double newCostPrice, double newSellingPrice, int newQty) {
    for (auto& p : productList) {
        if (p.getId() == id && p.isActive()) {
            p.setCostPrice(newCostPrice);
            p.setPrice(newSellingPrice);
            p.setQuantity(newQty);
            saveProducts();
            return;
        }
    }
}

// 4. Xóa mềm (Active = false)
void InventoryModel::deleteProduct(std::string id) {
    for (auto& p : productList) {
        if (p.getId() == id) {
            p.setActive(false);
            saveProducts();
            return;
        }
    }
}

// 5. Sắp xếp danh sách theo Ngành hàng và ID
void InventoryModel::sortProducts() {
    std::sort(productList.begin(), productList.end(), [](const Product& a, const Product& b) {
        if (a.getCategory() != b.getCategory()) {
            return a.getCategory() < b.getCategory();
        }
        return a.getId() < b.getId();
    });
    saveProducts();
}

// 6. Chức năng Bán hàng (Tự động trừ kho)
bool InventoryModel::sellProduct(std::string id, int qty) {
    for (auto& p : productList) {
        if (p.getId() == id && p.isActive()) {
            if (p.getQuantity() >= qty) {
                p.setQuantity(p.getQuantity() - qty);
                saveProducts();
                return true;
            }
        }
    }
    return false;
}

// 7. Xóa hàng kèm Lý do (Lưu nhật ký tiêu hủy)
void InventoryModel::deleteProductWithReason(std::string id, int reasonCode) {
    for (auto& p : productList) {
        if (p.getId() == id) {
            std::string reason = (reasonCode == 1) ? "Het han" : (reasonCode == 2 ? "Hu hong" : "Khac");
            std::string log = id + "," + p.getName() + "," + reason + "," + DateUtils::getCurrentDate();
            FileHandler::appendLine("../data/1_inventory/disposed_products.csv", log);
            p.setActive(false);
            saveProducts();
            return;
        }
    }
}

// 8. Lọc hàng đã hết hạn sử dụng
std::vector<Product> InventoryModel::getExpiredProducts() {
    std::vector<Product> results;
    std::string today = DateUtils::getCurrentDate();
    for (const auto& p : productList) {
        if (p.isActive() && p.getExpiryDate() != "None") {
            if (DateUtils::getDaysDifference(today, p.getExpiryDate()) < 0) {
                results.push_back(p);
            }
        }
    }
    return results;
}

// =========================================================================
// 9. FIX LOGIC CHỨC NĂNG 8: Lọc hàng tươi sống (Hiện mọi thứ có nhãn "tuoi")
// =========================================================================
std::vector<Product> InventoryModel::getFreshProductsToCheck() {
    std::vector<Product> results;
    for (const auto& p : productList) {
        // Chỉ cần 2 điều kiện: Đang bán (Active) và Note có chữ "tuoi"
        // Đã bỏ điều kiện (p.getLastChecked() != today) để hiện lên ngay sau khi nhập
        if (p.isActive() && p.getNote().find("tuoi") != std::string::npos) {
            results.push_back(p);
        }
    }
    return results;
}

// 10. Logic Khuyến mãi tự động dựa trên HSD
double InventoryModel::getDiscountRate(Product& p) {
    if (p.getExpiryDate() == "None" || p.getExpiryDate().empty()) return 1.0;
    std::string today = DateUtils::getCurrentDate();
    int daysLeft = DateUtils::getDaysDifference(today, p.getExpiryDate());
    if (daysLeft < 0) return 0.0;     // Hết hạn
    if (daysLeft <= 3) return 0.5;    // Cận hạn 3 ngày giảm 50%
    if (daysLeft <= 7) return 0.8;    // Cận hạn 7 ngày giảm 20%
    return 1.0;
}

std::vector<Product> InventoryModel::getDiscountedProducts() {
    std::vector<Product> results;
    for (auto& p : productList) {
        if (p.isActive()) {
            double rate = getDiscountRate(p);
            if (rate < 1.0 && rate > 0.0) {
                results.push_back(p);
            }
        }
    }
    return results;
}

// --- Các hàm bổ trợ ---
bool InventoryModel::addProduct(const Product& product) {
    for (const auto& p : productList) {
        if (p.getId() == product.getId()) {
            return false; // Trùng mã SP
        }
    }
    productList.push_back(product);
    saveProducts();
    return true;
}

std::vector<Product> InventoryModel::searchProducts(std::string key) {
    std::vector<Product> results;
    std::string lowerKey = StringUtils::removeAccents(StringUtils::toLowerCase(key));
    for (const auto& p : productList) {
        if (!p.isActive()) continue; // Không tìm hàng đã ngưng kinh doanh
        std::string pId = StringUtils::removeAccents(StringUtils::toLowerCase(p.getId()));
        std::string pName = StringUtils::removeAccents(StringUtils::toLowerCase(p.getName()));
        std::string pCat = StringUtils::removeAccents(StringUtils::toLowerCase(p.getCategory()));

        if (pId.find(lowerKey) != std::string::npos ||
            pName.find(lowerKey) != std::string::npos ||
            pCat.find(lowerKey) != std::string::npos) {
            results.push_back(p);
        }
    }
    return results;
}

std::vector<Product> InventoryModel::getAllProducts() {
    return productList;
}