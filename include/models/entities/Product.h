#ifndef DUANQLSIEUTHI_PRODUCT_H
#define DUANQLSIEUTHI_PRODUCT_H

#pragma once
#include <string>
#include <vector>
#include "Batch.h"

class Product {
private:
    std::string id;
    std::string name;
    std::string category;
    std::string unit; // <== THÊM MỚI: Đơn vị tính (kg, túi, hộp...)
    double costPrice;
    double price;
    bool active;

    std::vector<Batch> batches;

    std::string productionDate;
    std::string lastChecked;
    std::string note;

public:
    // Cập nhật Constructor thêm tham số unit
    Product(std::string id, std::string name, std::string category, std::string unit, double costPrice, double price,
            bool active, std::string nsx, std::string lastCheck, std::string note);

    // --- Nhóm Getters ---
    std::string getId() const;
    std::string getName() const;
    std::string getCategory() const;
    std::string getUnit() const; // <== THÊM MỚI
    double getCostPrice() const;
    double getPrice() const;
    bool isActive() const;
    std::string getProductionDate() const;
    std::string getLastChecked() const;
    std::string getNote() const;

    // --- LOGIC QUẢN LÝ LÔ HÀNG ---
    int getTotalQuantity() const;
    std::string getNearestExpiryDate() const;
    std::vector<Batch>& getBatches();
    const std::vector<Batch>& getBatches() const;
    void addBatch(const Batch& batch);

    // --- Nhóm Setters ---
    void setName(const std::string& newName);
    void setCategory(const std::string& newCategory);
    void setUnit(const std::string& newUnit); // <== THÊM MỚI
    void setCostPrice(double newCostPrice);
    void setPrice(double newPrice);
    void setActive(bool status);
    void setProductionDate(const std::string& nsx);
    void setLastChecked(const std::string& checkDate);
    void setNote(const std::string& newNote);
};

#endif //DUANQLSIEUTHI_PRODUCT_H