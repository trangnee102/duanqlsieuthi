#include "models/entities/Product.h"
#include <algorithm>

// Constructor: CẬP NHẬT thêm tham số unit (Đơn vị tính)
Product::Product(std::string id, std::string name, std::string category, std::string unit, double costPrice, double price,
                 bool active, std::string nsx, std::string lastCheck, std::string note)
    : id(id), name(name), category(category), unit(unit), costPrice(costPrice), price(price),
      active(active), productionDate(nsx), lastChecked(lastCheck), note(note) {}

// --- LOGIC QUẢN LÝ LÔ HÀNG ---

int Product::getTotalQuantity() const {
    int total = 0;
    for (const auto& b : batches) {
        total += b.quantity;
    }
    return total;
}

std::string Product::getNearestExpiryDate() const {
    if (batches.empty()) return "N/A";

    std::string nearest = "";
    for (const auto& b : batches) {
        if (b.expiryDate == "None" || b.expiryDate.empty() || b.expiryDate == "N/A") continue;

        if (nearest == "" || b.expiryDate < nearest) {
            nearest = b.expiryDate;
        }
    }
    return (nearest == "") ? "None" : nearest;
}

std::vector<Batch>& Product::getBatches() {
    return batches;
}

const std::vector<Batch>& Product::getBatches() const {
    return batches;
}

void Product::addBatch(const Batch& batch) {
    batches.push_back(batch);
}

// --- Nhóm hàm Lấy thông tin (Getters) ---
std::string Product::getId() const { return id; }
std::string Product::getName() const { return name; }
std::string Product::getCategory() const { return category; }
std::string Product::getUnit() const { return unit; } // <== THÊM MỚI
double Product::getCostPrice() const { return costPrice; }
double Product::getPrice() const { return price; }
bool Product::isActive() const { return active; }
std::string Product::getProductionDate() const { return productionDate; }
std::string Product::getLastChecked() const { return lastChecked; }
std::string Product::getNote() const { return note; }

// --- Nhóm hàm Cập nhật thông tin (Setters) ---
void Product::setName(const std::string& newName) { name = newName; }
void Product::setCategory(const std::string& newCategory) { category = newCategory; }
void Product::setUnit(const std::string& newUnit) { unit = newUnit; } // <== THÊM MỚI
void Product::setCostPrice(double newCostPrice) { costPrice = newCostPrice; }
void Product::setPrice(double newPrice) { price = newPrice; }
void Product::setActive(bool status) { active = status; }
void Product::setProductionDate(const std::string& nsx) { productionDate = nsx; }
void Product::setLastChecked(const std::string& checkDate) { lastChecked = checkDate; }
void Product::setNote(const std::string& newNote) { note = newNote; }