#include "views/InventoryView.h"
#include "utils/DateUtils.h"
#include "utils/InputUtils.h"
#include "utils/StringUtils.h"
#include <iostream>
#include <iomanip>
#include <limits>

// 1. Menu dành cho quản lý (Toàn quyền)
void InventoryView::displayAdminMenu() {
    std::cout << "\n==========================================";
    std::cout << "\n   [ADMIN] - HỆ THỐNG QUẢN LÝ KHO";
    std::cout << "\n==========================================";
    std::cout << "\n1. Xem danh sách sản phẩm đang bán";
    std::cout << "\n2. Nhập hàng mới (Tích hợp tính HSD)";
    std::cout << "\n3. Cập nhật Giá & Số lượng";
    std::cout << "\n4. Ngừng kinh doanh (Có chọn lý do)";
    std::cout << "\n5. Tìm kiếm sản phẩm (ID/Tên/Ngành)";
    std::cout << "\n6. Sắp xếp danh sách (Ngành & Mã SP)";
    std::cout << "\n7. Lọc hàng sắp hết / Hết hạn sử dụng";
    std::cout << "\n8. Kiểm tra độ tươi (Hàng tươi sống)";
    std::cout << "\n9. THANH TOÁN HÓA ĐƠN (Bán hàng)";
    std::cout << "\n10. ĐĂNG KÝ KHÁCH HÀNG MỚI (Thẻ VIP)";
    std::cout << "\n11. BÁO CÁO TÀI CHÍNH & LỢI NHUẬN";
    std::cout << "\n12. QUẢN LÝ NGÀNH HÀNG";
    std::cout << "\n0. Quay lại Menu chính";
    std::cout << "\n------------------------------------------";
    std::cout << "\nLựa chọn của bạn: ";
}

// 2. Menu dành cho nhân viên bán hàng (Staff)
void InventoryView::displayStaffMenu() {
    std::cout << "\n==========================================";
    std::cout << "\n   [STAFF] - THÔNG TIN KHO HÀNG";
    std::cout << "\n==========================================";
    std::cout << "\n1. Xem danh sách sản phẩm";
    std::cout << "\n5. Tìm kiếm sản phẩm";
    std::cout << "\n7. Xem hàng CẬN DATE (Để dán tem KM)";
    std::cout << "\n8. Kiểm tra độ tươi (Hàng ngày)";
    std::cout << "\n9. THANH TOÁN HÓA ĐƠN";
    std::cout << "\n10. ĐĂNG KÝ KHÁCH HÀNG MỚI";
    std::cout << "\n0. Quay lại Menu chính";
    std::cout << "\n------------------------------------------";
    std::cout << "\nLựa chọn của bạn: ";
}

// 3. Menu dành cho nhân viên nhập kho (Purchasing)
void InventoryView::displayPurchasingMenu() {
    std::cout << "\n==========================================";
    std::cout << "\n   [PURCHASING] - QUẢN LÝ NHẬP KHO";
    std::cout << "\n==========================================";
    std::cout << "\n1. Xem danh sách sản phẩm";
    std::cout << "\n2. Nhập hàng mới (Tự động tính HSD)";
    std::cout << "\n3. Cập nhật Giá & Số lượng (Nhập kho)";
    std::cout << "\n5. Tìm kiếm sản phẩm";
    std::cout << "\n6. Lọc hàng hết hạn / sắp hết";
    std::cout << "\n0. Quay lại Menu chính";
    std::cout << "\n------------------------------------------";
    std::cout << "\nLựa chọn của bạn: ";
}

// 4. Hiển thị danh sách sản phẩm
void InventoryView::displayProductList(const std::vector<Product>& products, bool isManager) {
    std::cout << "\n" << StringUtils::padRight("MÃ SP", 10)
              << StringUtils::padRight("TÊN SẢN PHẨM", 25)
              << StringUtils::padRight("NGÀNH", 15);

    if (isManager) {
        std::cout << StringUtils::padRight("GIÁ GỐC", 12);
    }

    std::cout << StringUtils::padRight("GIÁ BÁN", 12)
              << StringUtils::padRight("SL", 5)
              << StringUtils::padRight("HẠN SD", 12)
              << "GHI CHÚ\n";

    int dashWidth = isManager ? 100 : 88;
    std::cout << std::string(dashWidth, '-') << "\n";

    int count = 0;
    for (const auto& p : products) {
        if (p.isActive()) {
            std::cout << StringUtils::padRight(p.getId(), 10)
                      << StringUtils::padRight(p.getName().substr(0, 24), 25)
                      << StringUtils::padRight(p.getCategory(), 15);

            if (isManager) {
                std::cout << StringUtils::padRight(std::to_string((long long)p.getCostPrice()), 12);
            }

            std::cout << StringUtils::padRight(std::to_string((long long)p.getPrice()), 12)
                      << StringUtils::padRight(std::to_string(p.getQuantity()), 5)
                      << StringUtils::padRight(p.getExpiryDate(), 12)
                      << p.getNote() << "\n";
            count++;
        }
    }
    if (count == 0) std::cout << "   (Kho trong hoac khong tim thay san pham)\n";
    std::cout << std::string(dashWidth, '-') << "\n";
}

// 5. NHẬP HÀNG MỚI - ĐÃ SỬA LỖI ĐỊNH DANH ĐỒ TƯƠI
Product InventoryView::getInputForNewProduct(std::string id, const std::vector<std::string>& categories) {
    std::string name, cat, nsx, hsd, note;
    double price, costPrice;
    int qty, opt;

    std::cout << "\n--- NHẬP HÀNG MỚI ---" << std::endl;
    std::cout << "(Gõ '-1' hoặc 'CANCEL' ở bất kỳ bước nào để Hủy bỏ)\n";

    name = InputUtils::getValidName("Tên SP: ");
    if (name == "CANCEL") return Product("", "", "", 0, 0, 0, false, "", "", "", "");

    std::cout << "\nDanh sách Ngành Hàng khả dụng:\n";
    for (size_t i = 0; i < categories.size(); i++) {
        std::cout << i + 1 << ". " << categories[i] << "\n";
    }
    int catChoice = InputUtils::getValidInt("Chọn STT ngành hàng: ", 1, categories.size());
    if (catChoice < 0) return Product("", "", "", 0, 0, 0, false, "", "", "", "");
    cat = categories[catChoice - 1];
    std::cout << "=> Ngành hàng: " << cat << "\n";

    costPrice = InputUtils::getValidDouble("Giá Nhập (Giá vốn): ", 0.0);
    if (costPrice < 0) return Product("", "", "", 0, 0, 0, false, "", "", "", "");

    price = InputUtils::getValidDouble("Giá Bán (Niêm yết): ", 0.0);
    if (price < 0) return Product("", "", "", 0, 0, 0, false, "", "", "", "");

    qty = InputUtils::getValidInt("Số lượng: ", 0, 1000000);
    if (qty < 0) return Product("", "", "", 0, 0, 0, false, "", "", "", "");

    nsx = InputUtils::getValidDate("Ngày sản xuất (YYYY-MM-DD): ");
    if (nsx == "CANCEL") return Product("", "", "", 0, 0, 0, false, "", "", "", "");

    std::cout << "Chọn kiểu Hạn sử dụng:\n";
    std::cout << "1. Nhập ngày cụ thể (YYYY-MM-DD)\n";
    std::cout << "2. Nhập số ngày sử dụng (Tự động tính)\n";
    std::cout << "3. Hàng tươi (Dùng khi còn tươi)\n";
    opt = InputUtils::getValidInt("Chon: ", 1, 3);
    if (opt < 0) return Product("", "", "", 0, 0, 0, false, "", "", "", "");

    if (opt == 1) {
        while (true) {
            hsd = InputUtils::getValidDate("Nhap Han SD: ");
            if (hsd == "CANCEL") return Product("", "", "", 0, 0, 0, false, "", "", "", "");
            if (hsd >= nsx) break;
            std::cout << "\t[Lỗi] Hạn sử dụng không được bé hơn Ngày sản xuất!\n";
        }
        note = "Hang dong goi";
    } else if (opt == 2) {
        int days = InputUtils::getValidInt("So ngay su dung ke tu NSX: ", 1, 3650);
        if (days < 0) return Product("", "", "", 0, 0, 0, false, "", "", "", "");
        hsd = DateUtils::addDays(nsx, days);
        note = "Hang che bien";
    } else {
        hsd = "None";
        // QUAN TRỌNG: Sửa từ "Su dung khi con tuoi" thành "tuoi"
        // để đồng bộ với thuật toán lọc tại InventoryModel
        note = "tuoi";
    }

    // Mẹo nhỏ: Để sản phẩm hiện ra ngay ở mục kiểm tra đồ tươi sau khi nhập,
    // Trang có thể sửa 'today' thành một ngày trong quá khứ (VD: "2000-01-01")
    // Nhưng đúng nghiệp vụ thì ngày kiểm định mới nhất chính là ngày nhập hàng hôm nay.
    std::string today = DateUtils::getCurrentDate();

    return Product(id, name, cat, costPrice, price, qty, true, nsx, hsd, today, note);
}

// 6. Các hàm hỗ trợ khác
int InventoryView::getInputForDeleteReason() {
    std::cout << "\n--- LÝ DO NGỪNG KINH DOANH ---" << std::endl;
    std::cout << "1. Sản phẩm hết hạn sử dụng\n";
    std::cout << "2. Hàng bị hư hỏng, vỡ nát\n";
    std::cout << "3. Lý do khác (Đổi mẫu mã/Ngừng nhập)\n";
    return InputUtils::getValidInt("Lựa chọn: ", 1, 3);
}

void InventoryView::displayMessage(std::string message) {
    std::cout << "=> [Thông báo]: " << message << "\n";
}

void InventoryView::displayDiscountedProducts(const std::vector<Product>& products) {
    std::cout << "\n--- DANH SACH HANG CAN DATE (DI DAN TEM KHUYEN MAI) ---\n";
    std::cout << StringUtils::padRight("MÃ SP", 10)
              << StringUtils::padRight("TÊN SẢN PHẨM", 25)
              << StringUtils::padRight("GIÁ BÁN", 12)
              << StringUtils::padRight("HẠN SỬ DỤNG", 15)
              << "LOẠI TEM CẦN DÁN\n";
    std::cout << std::string(85, '-') << "\n";

    int count = 0;
    std::string today = DateUtils::getCurrentDate();

    for (const auto& p : products) {
        int daysLeft = DateUtils::getDaysDifference(today, p.getExpiryDate());
        std::string discountTag;

        if (daysLeft <= 3) discountTag = "[GIẢM 50% - MUA 1 TẶNG 1]";
        else if (daysLeft <= 7) discountTag = "[GIẢM 20%]";
        else discountTag = "[GIẢM GIÁ]";

        std::cout << StringUtils::padRight(p.getId(), 10)
                  << StringUtils::padRight(p.getName().substr(0, 24), 25)
                  << StringUtils::padRight(std::to_string((long long)p.getPrice()), 12)
                  << StringUtils::padRight(p.getExpiryDate(), 15)
                  << discountTag << "\n";
        count++;
    }

    if (count == 0) std::cout << "   (Tuyệt vời! Không có sản phẩm nào cần phải dán tem)\n";
    std::cout << std::string(85, '-') << "\n";
}

Customer InventoryView::getInputForNewCustomer(std::string id) {
    std::string name, phone;
    std::cout << "\n--- ĐĂNG KÝ KHÁCH HÀNG THÀNH VIẾN ---" << std::endl;

    name = InputUtils::getValidName("Họ tên khách hàng: ");
    if (name == "CANCEL") return Customer("", "", "", 0);

    phone = InputUtils::getValidPhone("Số điện thoại: ");
    if (phone == "CANCEL") return Customer("", "", "", 0);

    return Customer(id, name, phone, 0);
}

void InventoryView::displayRevenueReport(long long totalRevenue, int totalItemsSold, long long totalProfit) {
    std::cout << "\n==========================================";
    std::cout << "\n      BÁO CÁO TÀI CHÍNH SIÊU THỊ";
    std::cout << "\n==========================================";
    std::cout << "\nTổng sản phẩm đã bán: " << totalItemsSold;
    std::cout << "\nTổng doanh thu bán  : " << totalRevenue << " VND";
    std::cout << "\nTỔNG LỢI NHUẬN      : " << totalProfit << " VND";
    std::cout << "\n==========================================\n";
    std::cout << "Nhấn Enter để tiếp tục...";
    std::cin.ignore();
    std::cin.get();
}