#include "models/logic/CategoryModel.h"
#include "utils/FileHandler.h"
#include "utils/StringUtils.h"
#include <iostream>
#include <algorithm>

CategoryModel::CategoryModel() {
    loadCategories();
    // Nếu file chưa có dữ liệu, khởi tạo sẵn vài ngành và lưu lại
    if (categories.empty()) {
        categories.push_back("Thuc pham");
        categories.push_back("Do gia dung");
        categories.push_back("Dien tu");
        saveCategories();
    }
}

void CategoryModel::loadCategories() {
    categories.clear();
    std::vector<std::string> lines = FileHandler::readLines(dataPath);
    for (const auto& line : lines) {
        if (!line.empty()) {
            categories.push_back(line);
        }
    }
}

void CategoryModel::saveCategories() {
    FileHandler::writeLines(dataPath, categories);
}

std::vector<std::string>& CategoryModel::getAllCategories() {
    return categories;
}

bool CategoryModel::isExist(std::string name) {
    std::string lowerName = StringUtils::toLowerCase(name);
    for (const auto& c : categories) {
        if (StringUtils::toLowerCase(c) == lowerName) {
            return true;
        }
    }
    return false;
}

bool CategoryModel::addCategory(std::string name) {
    if (isExist(name)) return false;
    // Format lại Tiếng Việt chuẩn Title Case
    categories.push_back(StringUtils::toTitleCase(name));
    saveCategories();
    return true;
}
