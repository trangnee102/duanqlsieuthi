#ifndef DUANQLSIEUTHI_CATEGORYMODEL_H
#define DUANQLSIEUTHI_CATEGORYMODEL_H

#pragma once
#include <vector>
#include <string>

class CategoryModel {
private:
    std::string dataPath = "../data/1_inventory/categories.csv";
    std::vector<std::string> categories;

public:
    CategoryModel();

    void loadCategories();
    void saveCategories();
    std::vector<std::string>& getAllCategories();
    bool isExist(std::string name);
    bool addCategory(std::string name);
};

#endif // DUANQLSIEUTHI_CATEGORYMODEL_H
