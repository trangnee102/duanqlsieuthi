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
    std::cout << "\n1. Xem danh sách sản phẩm đang bán";
    std::cout << "\n2. Nhập hàng mới (Tạo SP & Lô đầu)";
    std::cout << "\n3. Cập nhật Giá bán & Giá vốn";
    std::cout << "\n4. Ngừng kinh doanh (Có chọn lý do)";
    std::cout << "\n5. Tìm kiếm sản phẩm (ID/Tên/Ngành)";
    std::cout << "\n6. Sắp xếp danh sách (Ngành & Mã SP)";
    std::cout << "\n7. Lọc hàng sắp hết / Hết hạn sử dụng";
    std::cout << "\n8. Kiểm tra độ tươi (Hàng tươi sống)";
    std::cout << "\n9. THANH TOÁN HÓA ĐƠN (Bán hàng)";
    std::cout << "\n10. ĐĂNG KÝ KHÁCH HÀNG MỚI (Thẻ VIP)";
    std::cout << "\n11. BÁO CÁO TÀI CHÍNH & LỢI NHUẬN";
    std::cout << "\n12. QUẢN LÝ NGÀNH HÀNG";
    std::cout << "\n13. XEM CẢNH BÁO TỒN KHO (Hàng sắp hết)";
    std::cout << "\n14. NHẬP THÊM LÔ HÀNG BỔ SUNG";
    std::cout << "\n15. KHO LƯU TRỮ (Hàng đã ngừng bán)";
    std::cout << "\n0. Quay lại Menu chính";
    std::cout << "\n------------------------------------------";
}

void InventoryView::displayStaffMenu() {
    std::cout << "\n==========================================";
    std::cout << "\n   [STAFF] - THÔNG TIN KHO HÀNG";
    std::cout << "\n==========================================";
    std::cout << "\n1. Xem danh sách sản phẩm";
    std::cout << "\n5. Tìm kiếm sản phẩm";
    std::cout << "\n7. Xem hàng CẬN DATE (KM)";
    std::cout << "\n8. Kiểm tra độ tươi (Hàng ngày)";
    std::cout << "\n9. THANH TOÁN HÓA ĐƠN";
    std::cout << "\n10. ĐĂNG KÝ KHÁCH HÀNG MỚI";
    std::cout << "\n0. Quay lại Menu chính";
    std::cout << "\n------------------------------------------";
}

void InventoryView::displayPurchasingMenu() {
    std::cout << "\n==========================================";
    std::cout << "\n   [PURCHASING] - QUẢN LÝ NHẬP KHO";
    std::cout << "\n==========================================";
    std::cout << "\n1. Xem danh sách sản phẩm";
    std::cout << "\n2. Nhập hàng mới";
    std::cout << "\n3. Cập nhật Giá nhập/Giá bán";
    std::cout << "\n5. Tìm kiếm sản phẩm";
    std::cout << "\n6. Lọc hàng hết hạn / sắp hết";
    std::cout << "\n13. Xem cảnh báo tồn kho";
    std::cout << "\n14. NHẬP THÊM LÔ HÀNG BỔ SUNG";
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
    }

    if (products.empty()) std::cout << "   (Danh sách trống hoặc không tìm thấy sản phẩm)\n";
    std::cout << std::string(dashWidth, '-') << "\n";
}

// [CẬP NHẬT]: Giao diện KHO LƯU TRỮ - CHỈ HIỆN LÝ DO NGẮN GỌN
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

        // [LOGIC MỚI]: Chỉ hiện lý do nếu Note bắt đầu bằng "NGUNG: "
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