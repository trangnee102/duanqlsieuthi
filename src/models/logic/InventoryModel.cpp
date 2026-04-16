#include "models/logic/InventoryModel.h"
#include "utils/FileHandler.h"
#include "utils/DateUtils.h"
#include "utils/StringUtils.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>

InventoryModel::InventoryModel() { loadProducts(); }

void InventoryModel::loadProducts() {
    productList.clear();

    // Hàm nạp dữ liệu từ file
    auto loadFromFile = [&](std::string path) {
        std::vector<std::string> lines = FileHandler::readLines(path);
        for (const auto& line : lines) {
            if (line.empty()) continue;
            std::vector<std::string> tokens = FileHandler::split(line, ',');
            if (tokens.size() >= 10) {
                Product p(tokens[0], tokens[1], tokens[2], tokens[3], std::stod(tokens[4]),
                          std::stod(tokens[5]), (tokens[6] == "1"), tokens[7], tokens[8], tokens[9]);
                productList.push_back(p);
            }
        }
    };

    loadFromFile(this->dataPath);
    loadFromFile(this->disposedPath);

    std::vector<std::string> bLines = FileHandler::readLines(this->batchPath);
    for (const auto& line : bLines) {
        if (line.empty()) continue;
        std::vector<std::string> tokens = FileHandler::split(line, ',');
        if (tokens.size() >= 4) {
            for (auto& p : productList) {
                if (p.getId() == tokens[0]) {
                    p.addBatch(Batch(tokens[0], tokens[1], std::stoi(tokens[2]), tokens[3]));
                    break;
                }
            }
        }
    }
}

void InventoryModel::saveProducts() {
    std::vector<std::string> pLines, bLines, dLines;
    for (const auto& p : productList) {
        std::string line = p.getId() + "," + p.getName() + "," + p.getCategory() + "," +
                           p.getUnit() + "," +
                           std::to_string((long long)p.getCostPrice()) + "," +
                           std::to_string((long long)p.getPrice()) + "," +
                           (p.isActive() ? "1" : "0") + "," + p.getProductionDate() + "," +
                           p.getLastChecked() + "," + p.getNote();

        if (p.isActive()) {
            pLines.push_back(line);
        } else {
            dLines.push_back(line);
        }

        for (const auto& b : p.getBatches()) {
            bLines.push_back(b.productId + "," + b.expiryDate + "," + std::to_string(b.quantity) + "," + b.importDate);
        }
    }
    FileHandler::writeLines(this->dataPath, pLines);
    FileHandler::writeLines(this->disposedPath, dLines);
    FileHandler::writeLines(this->batchPath, bLines);
}

bool InventoryModel::isDuplicate(std::string id, std::string name) {
    std::string lowName = StringUtils::toLowerCase(name);
    for (const auto& p : productList) {
        if (p.getId() == id || StringUtils::toLowerCase(p.getName()) == lowName) {
            return true;
        }
    }
    return false;
}

bool InventoryModel::addNewBatch(std::string id, std::string hsd, int qty, std::string& outBatchId) {
    for (auto& p : productList) {
        if (p.getId() == id && p.isActive()) {
            std::string today = DateUtils::getCurrentDate();
            std::string datePart = today.substr(8,2) + today.substr(5,2) + today.substr(2,2);
            int stt = p.getBatches().size() + 1;
            std::string sttPart = (stt < 10) ? "0" + std::to_string(stt) : std::to_string(stt);
            outBatchId = "L" + id + "_" + datePart + "_" + sttPart;

            p.addBatch(Batch(id, hsd, qty, today));
            saveProducts();
            return true;
        }
    }
    return false;
}

// [FIXED]: Sửa lại logic Khôi phục để xóa sạch dấu vết "Da khoi phuc..."
bool InventoryModel::restoreProduct(std::string id, std::string hsd, int qty, std::string& outBatchId) {
    for (auto& p : productList) {
        if (p.getId() == id && !p.isActive()) {
            p.setActive(true);

            // [CẬP NHẬT]: Tự động gán lại ghi chú chuẩn dựa trên hạn dùng mới
            if (hsd == "None" || hsd == "") {
                p.setNote("tuoi");
            } else {
                p.setNote("dong goi");
            }

            bool res = addNewBatch(id, hsd, qty, outBatchId);
            saveProducts();
            return res;
        }
    }
    return false;
}

bool InventoryModel::sellProduct(std::string id, int qty) {
    for (auto& p : productList) {
        if (p.getId() == id && p.isActive()) {
            if (p.getTotalQuantity() < qty) return false;
            auto& bList = p.getBatches();
            std::sort(bList.begin(), bList.end(), [](const Batch& a, const Batch& b) {
                if (a.expiryDate == "None") return false;
                if (b.expiryDate == "None") return true;
                return a.expiryDate < b.expiryDate;
            });
            int rem = qty;
            for (auto it = bList.begin(); it != bList.end(); ) {
                if (it->quantity <= rem) { rem -= it->quantity; it = bList.erase(it); }
                else { it->quantity -= rem; rem = 0; break; }
                if (rem <= 0) break;
            }
            saveProducts(); return true;
        }
    }
    return false;
}

void InventoryModel::fixProductDates(std::string id, std::string newNSX, std::string newHSD) {
    for (auto& p : productList) {
        if (p.getId() == id) {
            p.setProductionDate(newNSX);
            auto& batches = p.getBatches();
            if (!batches.empty()) batches[0].expiryDate = newHSD;
            saveProducts(); return;
        }
    }
}

double InventoryModel::getDiscountRate(Product& p) {
    std::string today = DateUtils::getCurrentDate();
    std::string hsd = p.getNearestExpiryDate();
    if (p.getCategory() == "Đồ ăn trong ngày") {
        time_t now = time(0); tm *ltm = localtime(&now);
        if (hsd != "None" && hsd < today) return 0.0;
        if (ltm->tm_hour > 18 || (ltm->tm_hour == 18 && ltm->tm_min >= 45)) return 0.5;
    }
    if (hsd == "None" || hsd == "N/A") return 1.0;
    int days = DateUtils::getDaysDifference(today, hsd);
    if (days < 0) return 0.0;
    if (days <= 3) return 0.5;
    if (days <= 7) return 0.8;
    return 1.0;
}

std::vector<Product> InventoryModel::getAllProducts() { return productList; }

bool InventoryModel::addProduct(const Product& product) {
    if (isDuplicate(product.getId(), product.getName())) return false;
    productList.push_back(product);
    saveProducts(); return true;
}

void InventoryModel::updateProduct(std::string id, double cp, double sp) {
    for (auto& p : productList) { if (p.getId() == id) { p.setCostPrice(cp); p.setPrice(sp); saveProducts(); return; } }
}

std::vector<Product> InventoryModel::searchProducts(std::string k) {
    std::vector<Product> res;
    std::string key = StringUtils::toLowerCase(k);
    for (auto& p : productList) {
        if (p.isActive() && (StringUtils::toLowerCase(p.getName()).find(key) != std::string::npos || p.getId().find(key) != std::string::npos))
            res.push_back(p);
    }
    return res;
}

double InventoryModel::checkVoucher(std::string c) {
    std::string code = StringUtils::toLowerCase(c);
    if (code == "trangvip") return 0.5;
    if (code == "cmc2026") return 0.15;
    return 0.0;
}

std::vector<Product> InventoryModel::getLowStockProducts(int t) {
    std::vector<Product> res;
    for (auto& p : productList) { if (p.isActive() && p.getTotalQuantity() < t) res.push_back(p); }
    return res;
}

std::vector<Product> InventoryModel::getExpiredProducts() {
    std::vector<Product> res;
    for (auto& p : productList) { if (p.isActive() && getDiscountRate(p) == 0.0) res.push_back(p); }
    return res;
}

std::vector<Product> InventoryModel::getDiscountedProducts() {
    std::vector<Product> res;
    for (auto& p : productList) {
        double r = getDiscountRate(p);
        if (p.isActive() && r < 1.0 && r > 0.0) res.push_back(p);
    }
    return res;
}

std::vector<Product> InventoryModel::getFreshProductsToCheck() {
    std::vector<Product> res;
    for (auto& p : productList) {
        if (p.isActive() && p.getNote().find("tuoi") != std::string::npos) res.push_back(p);
    }
    return res;
}

std::vector<Product> InventoryModel::getDisposedProducts() {
    std::vector<Product> res;
    for (const auto& p : productList) {
        if (!p.isActive()) res.push_back(p);
    }
    return res;
}

void InventoryModel::deleteProduct(std::string id) {
    for (auto& p : productList) { if (p.getId() == id) { p.setActive(false); saveProducts(); return; } }
}

void InventoryModel::deleteProductWithReason(std::string id, int reasonCode) {
    std::string reasonStr;
    switch (reasonCode) {
        case 1: reasonStr = "NGUNG: Het han su dung"; break;
        case 2: reasonStr = "NGUNG: Hu hong/Vo nat"; break;
        case 3: reasonStr = "NGUNG: Ly do khac"; break;
        default: reasonStr = "NGUNG: Khong xac dinh"; break;
    }
    for (auto& p : productList) {
        if (p.getId() == id) {
            p.setActive(false);
            p.setNote(reasonStr);
            saveProducts();
            return;
        }
    }
}

void InventoryModel::sortProducts() {
    std::sort(productList.begin(), productList.end(), [](const Product& a, const Product& b) {
        if (a.getCategory() != b.getCategory()) return a.getCategory() < b.getCategory();
        return a.getId() < b.getId();
    });
    saveProducts();
}

int InventoryModel::getFirstBatchQuantity(std::string id) {
    for (auto& p : productList) {
        if (p.getId() == id) {
            auto batches = p.getBatches();
            if (batches.empty()) return 0;
            std::sort(batches.begin(), batches.end(), [](const Batch& a, const Batch& b) {
                if (a.expiryDate == "None") return false;
                if (b.expiryDate == "None") return true;
                return a.expiryDate < b.expiryDate;
            });
            return batches[0].quantity;
        }
    }
    return 0;
}