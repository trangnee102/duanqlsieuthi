#include "controllers/InventoryController.h"
#include "views/InventoryView.h"
#include "models/entities/Customer.h"
#include "models/logic/TransactionModel.h"
#include "utils/FileHandler.h"
#include "utils/DateUtils.h"
#include "utils/InputUtils.h"
#include "utils/StringUtils.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>

InventoryController::InventoryController(InventoryModel& m, InventoryView& v, CustomerModel& cm, CategoryModel& catM)
    : model(m), view(v), customerModel(cm), categoryModel(catM) {}

// Dọn dẹp ký tự lạ để so sánh chuẩn
std::string cleanStr(std::string s) {
    s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
    s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
    size_t first = s.find_first_not_of(' ');
    if (std::string::npos == first) return "";
    size_t last = s.find_last_not_of(' ');
    return s.substr(first, (last - first + 1));
}

// Căn lề hóa đơn
std::string padRight(std::string text, size_t length) {
    size_t utf8_len = 0;
    for (char c : text) if ((c & 0xC0) != 0x80) utf8_len++;
    return (length > utf8_len) ? text + std::string(length - utf8_len, ' ') : text;
}

std::string padLeft(std::string text, size_t length) {
    size_t utf8_len = 0;
    for (char c : text) if ((c & 0xC0) != 0x80) utf8_len++;
    return (length > utf8_len) ? std::string(length - utf8_len, ' ') + text : text;
}

void InventoryController::run(Employee* currentUser) {
    if (currentUser == nullptr) return;
    int choice;
    std::string role = currentUser->getRole();
    bool isManager = (role == "Admin" || role == "Purchasing");

    do {
        if (role == "Admin") view.displayAdminMenu();
        else if (role == "Purchasing") view.displayPurchasingMenu();
        else view.displayStaffMenu();

        choice = InputUtils::getValidInt("\nLựa chọn của bạn: ", 0, 16);

        switch (choice) {
            case 1: { // XEM DANH SÁCH SẢN PHẨM ĐANG BÁN
                auto products = model.getAllProducts();
                std::vector<Product> activeProds;
                std::vector<std::string> qtyStrings;
                for (const auto& p : products) {
                    if (p.isActive()) {
                        activeProds.push_back(p);
                        qtyStrings.push_back(std::to_string(model.getFirstBatchQuantity(p.getId())) + "(" + std::to_string(p.getTotalQuantity()) + ")");
                    }
                }
                if (activeProds.empty()) view.displayMessage("Kho hàng hiện tại đang trống!");
                else view.displayProductList(activeProds, isManager, qtyStrings);
                break;
            }

            case 2: { // NHẬP HÀNG MỚI (TẠO SP & LÔ ĐẦU)
                if (!isManager) { view.displayMessage("LỖI: Bạn không có quyền nhập hàng!"); break; }
                std::string id = InputUtils::getValidString("Nhập Mã SP mới: ");
                std::string name = InputUtils::getValidName("Tên SP: ");
                if (model.isDuplicate(id, name)) { view.displayMessage("LỖI: Trùng mã/tên!"); break; }
                std::string hsd;
                Product tempP = view.getInputForNewProduct(id, name, categoryModel.getAllCategories(), hsd);
                int q = InputUtils::getValidInt("Số lượng lô đầu: ", 1);
                if (model.addProduct(tempP)) {
                    std::string b; model.addNewBatch(id, hsd, q, b);
                    view.displayMessage("Đã thêm sản phẩm và tạo lô thành công!");
                }
                break;
            }

            case 3: { // CẬP NHẬT GIÁ BÁN & GIÁ VỐN (CHI TIẾT)
                if (!isManager) { view.displayMessage("LỖI: Chỉ Quản lý mới được sửa giá!"); break; }
                std::string id = InputUtils::getValidString("Nhập Mã SP: ");
                auto res = model.searchProducts(id);
                Product* target = nullptr;
                for (auto& p : res) if (p.getId() == id) { target = &p; break; }

                if (target == nullptr) {
                    view.displayMessage("LỖI: Không tìm thấy mã sản phẩm này!");
                } else {
                    std::cout << "\n--- ĐANG CẬP NHẬT: " << target->getName() << " ---\n";
                    std::cout << "Giá VỐN hiện tại: " << (long long)target->getCostPrice() << " VND\n";
                    std::cout << "Giá BÁN hiện tại: " << (long long)target->getPrice() << " VND\n";
                    std::cout << "------------------------------------------\n";

                    double cp = InputUtils::getValidDouble("Nhập Giá VỐN mới (0 giữ cũ): ");
                    double sp = InputUtils::getValidDouble("Nhập Giá BÁN mới (0 giữ cũ): ");

                    double fCP = (cp > 0) ? cp : target->getCostPrice();
                    double fSP = (sp > 0) ? sp : target->getPrice();

                    model.updateProduct(id, fCP, fSP);
                    std::cout << "=> [THÀNH CÔNG]: Đã cập nhật giá mới cho " << target->getName() << "\n";
                }
                break;
            }

            case 4: { // NGỪNG KINH DOANH
                if (!isManager) { view.displayMessage("LỖI: Không có quyền!"); break; }
                std::string id = InputUtils::getValidString("Mã SP cần ngừng: ");
                int r = view.getInputForDeleteReason();
                model.deleteProductWithReason(id, r);
                view.displayMessage("Đã chuyển vào Kho lưu trữ.");
                break;
            }

            case 5: { // TÌM KIẾM SẢN PHẨM
                std::string key = InputUtils::getValidString("Từ khóa (ID/Tên/Ngành): ");
                auto res = model.searchProducts(key);
                std::vector<std::string> qStr;
                for (const auto& p : res) qStr.push_back(std::to_string(p.getTotalQuantity()));
                view.displayProductList(res, isManager, qStr);
                break;
            }

            case 6: { // SẮP XẾP DANH SÁCH
                model.sortProducts();
                view.displayMessage("Đã sắp xếp theo Ngành hàng và Mã SP.");
                break;
            }

            case 7: { // LỌC HÀNG HẾT HẠN SỬ DỤNG
                auto expired = model.getExpiredProducts();
                std::vector<std::string> qStr;
                for (const auto& p : expired) qStr.push_back(std::to_string(p.getTotalQuantity()));
                view.displayProductList(expired, isManager, qStr);
                break;
            }

            case 8: { // KIỂM TRA ĐỘ TƯƠI
                auto fresh = model.getFreshProductsToCheck();
                std::vector<std::string> qStr;
                for (const auto& p : fresh) qStr.push_back(std::to_string(p.getTotalQuantity()));
                view.displayProductList(fresh, isManager, qStr);
                break;
            }

            case 9: { // THANH TOÁN POS - BẢN FIX LỖI BUILD & CHẶN CÁ THU TUYỆT ĐỐI
                std::cout << "\n" << std::string(80, '=') << "\n";
                std::cout << padLeft("HỆ THỐNG POS CMC - KIỂM SOÁT DAILY FRESH", 60) << "\n";
                std::cout << std::string(80, '=') << "\n";

                std::string today = "2026-04-16"; // Chốt ngày hôm nay

                // 1. Nhận diện VIP
                std::string phone = InputUtils::getValidString("Nhập SĐT khách (0 = Vãng lai): ");
                Customer* currentCustomer = customerModel.getCustomerByPhone(phone);

                // 2. Quét hàng
                std::vector<CartItem> cart;
                while (true) {
                    std::string id = InputUtils::getValidString("\nQuét Mã SP (0 = Chốt đơn): ");
                    if (id == "0") break;

                    auto res = model.searchProducts(id);
                    if (res.empty()) { std::cout << "=> Không thấy SP!\n"; continue; }

                    Product& p = res[0];
                    std::string hsd = p.getNearestExpiryDate();
                    std::string cat = p.getCategory();

                    // --- CHỐT CHẶN TẠI CHỖ ---
                    bool isFresh = (cat.find("Hải Sản") != std::string::npos || cat.find("Thịt") != std::string::npos ||
                                    cat.find("Đồ Ăn") != std::string::npos || cat.find("Rau Củ") != std::string::npos);

                    double overrideRate = -1.0;

                    if (hsd != "None") {
                        if (isFresh) {
                            if (hsd < today) {
                                std::cout << "=> [LỖI] SẢN PHẨM TƯƠI ĐÃ QUÁ HẠN SỬ DỤNG!\n";
                                continue;
                            } else if (hsd == today) {
                                time_t now = time(0); tm *ltm = localtime(&now);
                                if (ltm->tm_hour >= 22) {
                                    std::cout << "=> [LỖI] ĐÃ QUÁ 22H! ĐỒ TƯƠI BÁN TRONG NGÀY ĐÃ HẾT HẠN!\n";
                                    continue;
                                } else if (ltm->tm_hour >= 19) {
                                    overrideRate = 0.5; // Giảm 50%
                                    std::cout << "=> (Khuyến mãi hàng tươi sau 19H: Giảm 50%)\n";
                                }
                            }
                        } else {
                            if (hsd <= today) {
                                std::cout << "=> [LỖI] SẢN PHẨM KHÔ NÀY ĐÃ HẾT HẠN SỬ DỤNG!\n";
                                continue;
                            }
                        }
                    }

                    int qty = InputUtils::getValidInt("Số lượng mua: ", 1);
                    if (qty > p.getTotalQuantity()) { std::cout << "=> Kho không đủ!\n"; continue; }

                    double rate = (overrideRate >= 0.0) ? overrideRate : model.getDiscountRate(p);
                    if (rate < 0) rate = 0;

                    double sub = p.getPrice() * qty;
                    // rate ở đây là hệ số giá bán (ví dụ 1.0 là giá gốc, 0.5 là nửa giá)
                    // Vậy số tiền được giảm = sub * (1.0 - rate)
                    double dAmt = sub * (1.0 - rate);

                    cart.push_back({p, qty, sub, dAmt});
                    std::cout << "=> Đã thêm: " << p.getName() << "\n";
                }

                // 3. Thanh toán và lưu (Đảm bảo ghi vào file để Case 11 thấy)
                if (!cart.empty()) {
                    double baseTotal = 0;
                    for (auto& item : cart) baseTotal += (item.subTotal - item.discountAmount);

                    double customerDiscount = 0;
                    if (currentCustomer) {
                        customerDiscount = currentCustomer->getDiscountRate() * baseTotal;
                    }
                    double finalTotal = baseTotal - customerDiscount;

                    std::cout << "\n--- HÓA ĐƠN TẠM TÍNH ---\n";
                    std::cout << "Tổng tiền hàng: " << (long long)baseTotal << " VND\n";
                    if (currentCustomer && currentCustomer->getDiscountRate() > 0) {
                        std::cout << "Chiết khấu thành viên (" << currentCustomer->getMemberLevel() << "): -" << (long long)customerDiscount << " VND\n";
                    }
                    std::cout << "\n=> TỔNG PHẢI THANH TOÁN: " << (long long)finalTotal << " VND\n";
                    
                    std::string cf = InputUtils::getValidString("Xác nhận in hóa đơn? (Y/N): ");

                    if (cf == "Y" || cf == "y") {
                        for (auto& item : cart) model.sellProduct(item.product.getId(), item.qty);

                        // LƯU GIAO DỊCH: Khởi tạo xong gọi save luôn, không gọi load nữa
                        TransactionModel().saveTransaction(phone, cart, finalTotal, 0);

                        if (currentCustomer) {
                            customerModel.updatePoints(currentCustomer->getId(), currentCustomer->getPoints() + (int)(finalTotal/10000));
                        }
                        std::cout << "=> [THÀNH CÔNG]: Đã lưu hóa đơn!\n";
                    }
                }
                break;
            }
            case 10: { // ĐĂNG KÝ VIP (BẢN FIX CHỐT: TỰ TẠO MÃ KH & CHẶN TRÙNG SĐT)
                std::string p = InputUtils::getValidString("SĐT khách hàng: ");

                // 1. Kiểm tra xem SĐT này đã có ai dùng chưa
                bool isDup = false;
                for (const auto& c : customerModel.getAllCustomers()) {
                    if (c.getPhone() == p) {
                        std::cout << "=> [LỖI]: SĐT " << p << " đã được đăng ký cho KH: " << c.getName() << " (" << c.getId() << ")!\n";
                        isDup = true;
                        break;
                    }
                }
                if (isDup) break; // Đá văng ra menu nếu trùng

                std::string n = InputUtils::getValidName("Tên khách hàng: ");

                // 2. Tự động sinh mã KH tiếp theo (KH01, KH02...)
                int maxId = 0;
                for (const auto& c : customerModel.getAllCustomers()) {
                    std::string id = c.getId();
                    if (id.length() > 2 && id.substr(0, 2) == "KH") {
                        try {
                            int num = std::stoi(id.substr(2));
                            if (num > maxId) maxId = num;
                        } catch (...) {}
                    }
                }
                int nextNum = maxId + 1;
                std::string newId = "KH" + std::string(nextNum < 10 ? "0" : "") + std::to_string(nextNum);

                // 3. Lưu vào hệ thống
                customerModel.addCustomer(Customer(newId, n, p));
                std::cout << "=> [THÀNH CÔNG]: Đã đăng ký VIP! Mã KH của khách là: " << newId << "\n";
                break;
            }

            case 11: { // BÁO CÁO TÀI CHÍNH & LỢI NHUẬN - BẢN FIX 0 VND
                std::cout << "\n" << std::string(80, '=') << "\n";
                std::cout << padLeft("HỆ THỐNG BÁO CÁO DOANH THU - CMC SIÊU THỊ", 60) << "\n";
                std::cout << std::string(80, '=') << "\n";

                // --- BƯỚC QUAN TRỌNG: Khởi tạo lại để nạp đơn hàng mới nhất từ file CSV ---
                TransactionModel reportModel;
                auto allTrans = reportModel.getAllTransactions();
                std::string today = DateUtils::getCurrentDate(); // "2026-04-16"

                std::cout << "1. Tất cả | 2. Theo Tháng | 3. Theo Ngày\n";
                int subCh = InputUtils::getValidInt("Lựa chọn của bạn: ", 1, 3);

                double totalRevenue = 0;
                int count = 0;

                std::cout << "\n" << padRight("Ngày", 15) << padRight("Khách hàng", 25) << padLeft("Doanh thu (VND)", 20) << "\n";
                std::cout << std::string(80, '-') << "\n";

                if (subCh == 1) { // TẤT CẢ
                    for (const auto& t : allTrans) {
                        totalRevenue += t.totalAmount;
                        count++;
                        std::cout << padRight(t.date, 15) << padRight(t.customerPhone, 25) << padLeft(std::to_string((long long)t.totalAmount), 20) << "\n";
                    }
                }
                else if (subCh == 2) { // THEO THÁNG
                    std::string targetMonth = today.substr(0, 7); // Lấy "2026-04"
                    for (const auto& t : allTrans) {
                        if (t.date.substr(0, 7) == targetMonth) {
                            totalRevenue += t.totalAmount;
                            count++;
                            std::cout << padRight(t.date, 15) << padRight(t.customerPhone, 25) << padLeft(std::to_string((long long)t.totalAmount), 20) << "\n";
                        }
                    }
                }
                else if (subCh == 3) { // THEO NGÀY
                    for (const auto& t : allTrans) {
                        // So khớp chính xác 10 ký tự YYYY-MM-DD
                        if (t.date.substr(0, 10) == today) {
                            totalRevenue += t.totalAmount;
                            count++;
                            std::cout << padRight(t.date, 15) << padRight(t.customerPhone, 25) << padLeft(std::to_string((long long)t.totalAmount), 20) << "\n";
                        }
                    }
                }

                std::cout << std::string(80, '=') << "\n";
                std::cout << "=> TỔNG CỘNG: " << count << " đơn hàng thành công.\n";
                std::cout << "=> TỔNG DOANH THU: " << (long long)totalRevenue << " VND\n";
                std::cout << std::string(80, '=') << "\n";

                InputUtils::getValidString("\nNhấn Enter để quay lại...");
                break;
            }
            case 12: { // QUẢN LÝ NGÀNH HÀNG
                auto cats = categoryModel.getAllCategories();
                for (size_t i = 0; i < cats.size(); ++i) std::cout << i + 1 << ". " << cats[i] << "\n";
                break;
            }

            case 13: { // XEM CẢNH BÁO TỒN KHO
                auto low = model.getLowStockProducts(15);
                std::vector<std::string> qStr;
                for (const auto& p : low) qStr.push_back(std::to_string(p.getTotalQuantity()));
                view.displayProductList(low, isManager, qStr);
                break;
            }

            case 14: { // NHẬP THÊM LÔ HÀNG BỔ SUNG
                if (role == "Staff") break;
                std::string id = InputUtils::getValidString("Mã SP: ");
                
                auto res = model.searchProducts(id);
                Product* target = nullptr;
                for (auto& p : res) if (p.getId() == id) { target = &p; break; }

                if (target == nullptr) {
                    view.displayMessage("LỖI: Không tìm thấy sản phẩm này!");
                    break;
                }
                
                std::cout << "=> Tên sản phẩm: " << target->getName() << "\n";
                // Nhập HSD trước, sau đó Số lượng như yêu cầu logic
                std::string h = InputUtils::getValidDate("Hạn sử dụng (YYYY-MM-DD / None): ");
                int q = InputUtils::getValidInt("Số lượng lô hàng mới: ", 1);
                
                std::string b; 
                model.addNewBatch(id, h, q, b);
                view.displayMessage("Đã nhập lô hàng bổ sung thành công! Mã lô: " + b);
                break;
            }

            case 15: { // KHO LƯU TRỮ
                if (role != "Admin") break;
                view.displayDisposedProductList(model.getDisposedProducts(), isManager, {});
                break;
            }

            case 16: { // XỬ LÝ NHANH HÀNG HẾT HẠN HÔM NAY
                if (role != "Admin") { view.displayMessage("LỖI: Chỉ Admin mới có quyền!"); break; }
                std::string today = DateUtils::getCurrentDate();
                auto all = model.getAllProducts();
                int cnt = 0;
                for (auto& p : all) {
                    if (p.isActive() && p.getNearestExpiryDate() == today) {
                        model.deleteProductWithReason(p.getId(), 1);
                        cnt++;
                    }
                }
                view.displayMessage("Đã xử lý xong " + std::to_string(cnt) + " mặt hàng hết hạn hôm nay.");
                break;
            }

            case 0: break;
        }
    } while (choice != 0);
}