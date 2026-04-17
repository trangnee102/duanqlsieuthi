#include "views/InventoryView.h"
#include "utils/DateUtils.h"
#include "utils/InputUtils.h"
#include "utils/StringUtils.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

void InventoryView::displayAdminMenu() {
    std::cout << "\n==========================================";
    std::cout << "\n   [ADMIN] - HỆ THỐNG QUẢN LÝ KHO";
    std::cout << "\n==========================================";
    std::cout << "\n1. Xem danh mục sản phẩm (Kèm chi tiết lô)";
    std::cout << "\n2. Tạo mới SKU & Khởi tạo lô hàng";
    std::cout << "\n3. Điều chỉnh Cấu trúc Giá (Giá vốn & Giá bán)";
    std::cout << "\n4. Ngừng kinh doanh sản phẩm (Kho lưu trữ)";
    std::cout << "\n5. Tìm kiếm sản phẩm (ID/Tên/Ngành)";
    std::cout << "\n6. Sắp xếp danh sách (Ngành & Mã SP)";
    std::cout << "\n7. Kiểm soát Cận Date / Hết hạn (Thanh lý/Loại bỏ)";
    std::cout << "\n8. Rà soát Thực phẩm tươi sống (Daily Fresh)";
    std::cout << "\n9. GIAO DỊCH POS (Bán hàng & Chiết khấu)";
    std::cout << "\n10. QUẢN LÝ THÀNH VIÊN KHÁCH HÀNG (Membership)";
    std::cout << "\n11. TRÍCH XUẤT BÁO CÁO TÀI CHÍNH";
    std::cout << "\n12. QUẢN LÝ NGÀNH HÀNG";
    std::cout << "\n13. KIỂM SOÁT HÀNG TỒN (Cảnh báo nhập thêm)";
    std::cout << "\n14. NHẬP LÔ HÀNG BỔ SUNG (Restock)";
    std::cout << "\n15. KHO LƯU TRỮ (Hàng đã ngừng bán)";
    std::cout << "\n0. Quay lại Menu chính";
    std::cout << "\n------------------------------------------";
}

void InventoryView::displayStaffMenu() {
    std::cout << "\n==========================================";
    std::cout << "\n   [STAFF] - BẢNG ĐIỀU KHIỂN BÁN HÀNG";
    std::cout << "\n==========================================";
    std::cout << "\n1. Xem danh mục sản phẩm (Kèm chi tiết lô)";
    std::cout << "\n5. Tìm kiếm sản phẩm";
    std::cout << "\n7. Kiểm soát Cận Date / Hết hạn (Khuyến mãi)";
    std::cout << "\n8. Rà soát Thực phẩm tươi sống (Daily Fresh)";
    std::cout << "\n9. GIAO DỊCH POS (Bán hàng & Chiết khấu)";
    std::cout << "\n10. QUẢN LÝ THÀNH VIÊN KHÁCH HÀNG (Membership)";
    std::cout << "\n0. Quay lại Menu chính";
    std::cout << "\n------------------------------------------";
}

void InventoryView::displayPurchasingMenu() {
    std::cout << "\n==========================================";
    std::cout << "\n   [PURCHASING] - QUẢN LÝ NHẬP KHO";
    std::cout << "\n==========================================";
    std::cout << "\n1. Xem danh mục sản phẩm";
    std::cout << "\n2. Tạo mới SKU & Khởi tạo lô hàng";
    std::cout << "\n3. Điều chỉnh Cấu trúc Giá (Giá vốn & Giá bán)";
    std::cout << "\n5. Tìm kiếm sản phẩm";
    std::cout << "\n6. Lọc hàng cận hạn / Quá hạn sử dụng";
    std::cout << "\n13. Kiểm soát hàng tồn (Restock Alert)";
    std::cout << "\n14. NHẬP LÔ HÀNG BỔ SUNG (Restock)";
    std::cout << "\n0. Quay lại Menu chính";
    std::cout << "\n------------------------------------------";
}

void InventoryView::displayProductList(const std::vector<Product>& products, bool isManager, const std::vector<std::string>& qtyStrings) {
    std::cout << "\n" << StringUtils::padRight("MÃ SP", 7)
              << StringUtils::padRight("TÊN SẢN PHẨM", 20)
              << StringUtils::padRight("ĐVT", 6)
              << StringUtils::padRight("NGÀNH", 13);

    if (isManager) std::cout << StringUtils::padRight("GIÁ NHẬP", 10);

    std::cout << StringUtils::padRight("GIÁ BÁN", 10)
              << StringUtils::padRight("SL(TỔNG)", 11)
              << StringUtils::padRight("HẠN SD", 11)
              << "GHI CHÚ\n";

    int dashWidth = isManager ? 110 : 100;
    std::cout << std::string(dashWidth, '-') << "\n";

    for (size_t i = 0; i < products.size(); i++) {
        const auto& p = products[i];

        std::string safeName = StringUtils::safeSubstr(p.getName(), 19);
        std::string safeUnit = StringUtils::safeSubstr(p.getUnit(), 5);
        std::string safeCat  = StringUtils::safeSubstr(p.getCategory(), 12);
        std::string safeNote = StringUtils::safeSubstr(p.getNote(), 22);
        if (StringUtils::utf8_length(p.getNote()) > 22) safeNote += "...";

        std::cout << StringUtils::padRight(p.getId(), 7)
                  << StringUtils::padRight(safeName, 20)
                  << StringUtils::padRight(safeUnit, 6)
                  << StringUtils::padRight(safeCat, 13);

        if (isManager) std::cout << StringUtils::padRight(std::to_string((long long)p.getCostPrice()), 10);

        std::cout << StringUtils::padRight(std::to_string((long long)p.getPrice()), 10)
                  << StringUtils::padRight(qtyStrings[i], 11)
                  << StringUtils::padRight(p.getNearestExpiryDate(), 11)
                  << safeNote << "\n";

        // Giai đoạn 1: Hiển thị chi tiết từng Lô Hàng
        const auto& batches = p.getBatches();
        if (!batches.empty()) {
            for (const auto& b : batches) {
                if (b.quantity > 0) {
                    std::cout << "   ↳ [Lô " << StringUtils::padRight(b.batchId + "]", 18)
                              << " SL: " << StringUtils::padRight(std::to_string(b.quantity), 8)
                              << " Nhập: " << StringUtils::padRight(b.importDate, 12)
                              << " HSD: " << b.expiryDate << "\n";
                }
            }
        }
    }

    if (products.empty()) std::cout << "   (Danh sách trống hoặc không tìm thấy sản phẩm)\n";
    std::cout << std::string(dashWidth, '-') << "\n";
}

// Giao diện KHO LƯU TRỮ - CHỈ HIỆN LÝ DO NGẮN GỌN
void InventoryView::displayDisposedProductList(const std::vector<Product>& products, bool isManager, const std::vector<std::string>& qtyStrings) {
    std::cout << "\n" << StringUtils::padRight("MÃ SP", 7)
              << StringUtils::padRight("TÊN SẢN PHẨM", 20)
              << StringUtils::padRight("NGÀNH", 15)
              << StringUtils::padRight("SL CÒN", 10)
              << StringUtils::padRight("HẠN SD CUỐI", 15)
              << "LÝ DO NGỪNG KINH DOANH\n";

    std::cout << std::string(85, '-') << "\n";

    for (size_t i = 0; i < products.size(); i++) {
        const auto& p = products[i];

        std::string rawNote = p.getNote();
        std::string reason = "";

        // Chỉ hiện lý do nếu Note bắt đầu bằng "NGUNG: "
        size_t pos = rawNote.find("NGUNG: ");
        if (pos != std::string::npos) {
            reason = rawNote.substr(pos + 7); // Cắt lấy phần sau "NGUNG: "
        } else {
            reason = "Ly do khac"; // Nếu là rác cũ (như dong goi) thì hiện chung là lý do khác
        }

        std::cout << StringUtils::padRight(p.getId(), 7)
                  << StringUtils::padRight(StringUtils::safeSubstr(p.getName(), 19), 20)
                  << StringUtils::padRight(StringUtils::safeSubstr(p.getCategory(), 14), 15)
                  << StringUtils::padRight(qtyStrings[i], 10)
                  << StringUtils::padRight(p.getNearestExpiryDate(), 15)
                  << StringUtils::safeSubstr(reason, 25) << "\n";
    }

    if (products.empty()) std::cout << "   (Kho lưu trữ trống)\n";
    std::cout << std::string(85, '-') << "\n";
}

Product InventoryView::getInputForNewProduct(std::string id, std::string name, const std::vector<std::string>& categories, std::string& outHsd) {
    std::string cat, unit, nsx, note, today = DateUtils::getCurrentDate();
    double price, costPrice;

    std::cout << "\n--- HOÀN TẤT THÔNG TIN SẢN PHẨM MỚI ---\n";
    std::cout << "Mã SP: " << id << " | Tên SP: " << name << "\n";

    unit = InputUtils::getValidString("Đơn vị tính (kg/tui/hop...): ");

    std::cout << "\nDanh sách Ngành Hàng khả dụng:\n";
    for (size_t i = 0; i < categories.size(); i++) {
        std::cout << i + 1 << ". " << categories[i] << "\n";
    }
    int catChoice = InputUtils::getValidInt("Chọn STT ngành hàng: ", 1, (int)categories.size());
    cat = categories[catChoice - 1];

    costPrice = InputUtils::getValidDouble("Giá Nhập: ", 0.0);
    price = InputUtils::getValidDouble("Giá Bán: ", 0.0);

    if (cat == "Đồ ăn trong ngày") {
        nsx = today; outHsd = today; note = "tuoi - Dung trong ngay";
    } else {
        nsx = InputUtils::getValidDate("Ngày sản xuất (YYYY-MM-DD): ");
        std::cout << "Kiểu Hạn sử dụng (1: Ngày cụ thể, 2: Số ngày, 3: Hàng tươi): ";
        int opt = InputUtils::getValidInt("", 1, 3);
        if (opt == 1) outHsd = InputUtils::getValidDate("Nhập Hạn SD (YYYY-MM-DD): ");
        else if (opt == 2) outHsd = DateUtils::addDays(nsx, InputUtils::getValidInt("Số ngày sử dụng: ", 1));
        else outHsd = "None";
        note = (outHsd == "None") ? "tuoi" : "dong goi";
    }

    return Product(id, name, cat, unit, costPrice, price, true, nsx, today, note);
}

void InventoryView::getInputForNewBatch(const Product& p, std::string& hsd, int& qty) {
    std::string today = DateUtils::getCurrentDate();
    std::cout << "\n--- NHẬP THÊM LÔ HÀNG [" << p.getName() << "] ---" << std::endl;
    qty = InputUtils::getValidInt("Số lượng nhập thêm: ", 1);

    if (p.getCategory() == "Đồ ăn trong ngày") hsd = today;
    else hsd = InputUtils::getValidDate("Hạn sử dụng của lô mới (YYYY-MM-DD): ");
}

void InventoryView::displayDiscountedProducts(const std::vector<Product>& products, const std::vector<std::string>& qtyStrings) {
    std::cout << "\n--- DANH SÁCH HÀNG CẬN DATE (KHUYẾN MÃI) ---\n";
    std::cout << StringUtils::padRight("MÃ SP", 10)
              << StringUtils::padRight("TÊN SẢN PHẨM", 25)
              << StringUtils::padRight("SL LÔ CŨ(TỔNG)", 18)
              << "MỨC GIẢM\n";
    std::cout << std::string(75, '-') << "\n";

    for (size_t i = 0; i < products.size(); i++) {
        std::cout << StringUtils::padRight(products[i].getId(), 10)
                  << StringUtils::padRight(StringUtils::safeSubstr(products[i].getName(), 24), 25)
                  << StringUtils::padRight(qtyStrings[i], 18)
                  << "- 20%\n";
    }
    std::cout << std::string(75, '-') << "\n";
}

int InventoryView::getInputForDeleteReason() {
    std::cout << "Lý do ngừng kinh doanh (1: Hết hạn, 2: Hư hỏng, 3: Khác): ";
    return InputUtils::getValidInt("", 1, 3);
}

void InventoryView::displayMessage(std::string message) {
    std::cout << "=> [Thông báo]: " << message << "\n";
}

Customer InventoryView::getInputForNewCustomer(std::string id) {
    std::string name = InputUtils::getValidName("Họ tên: ");
    std::string phone = InputUtils::getValidPhone("SĐT: ");
    return Customer(id, name, phone, 0);
}

void InventoryView::displayRevenueReport(long long tr, int ti, long long tp) {
    std::cout << "\nTổng doanh thu: " << tr << " VND | Lợi nhuận: " << tp << " VND\n";
}