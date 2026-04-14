#include "controllers/InventoryController.h"
#include "utils/FileHandler.h"
#include "utils/DateUtils.h"
#include "utils/InputUtils.h"
#include <iostream>
#include <string>
#include <iomanip>

InventoryController::InventoryController(InventoryModel& m, InventoryView& v, CustomerModel& cm, CategoryModel& catM)
    : model(m), view(v), customerModel(cm), categoryModel(catM) {}

void InventoryController::run(Employee* currentUser) {
    if (currentUser == nullptr) return;

    int choice;
    std::string role = currentUser->getRole();
    // Chìa khóa bảo mật: Chỉ Admin và Purchasing mới thấy được Giá Nhập
    bool isManager = (role == "Admin" || role == "Purchasing");

    do {
        if (role == "Admin") view.displayAdminMenu();
        else if (role == "Purchasing") view.displayPurchasingMenu();
        else view.displayStaffMenu();

        choice = InputUtils::getValidInt("", 0, 12);

        switch (choice) {
            case 1: view.displayProductList(model.getAllProducts(), isManager); break;
            case 2:
            {
                if (role == "Staff") { view.displayMessage("Không có quyền!"); break; }

                std::string id;
                while (true) {
                    id = InputUtils::getValidString("Nhập Mã SP mới: ");
                    if (id == "CANCEL") break;

                    auto results = model.searchProducts(id);
                    bool isExist = false;
                    for (const auto& prod : results) {
                        if (prod.getId() == id) { isExist = true; break; }
                    }

                    if (isExist) {
                        view.displayMessage("\t[LỖI] Mã ID này đã tồn tại trong kho! Vui lòng kiểm tra lại.");
                        continue;
                    }
                    break;
                }
                if (id == "CANCEL") break;

                Product newP = view.getInputForNewProduct(id, categoryModel.getAllCategories());
                if (newP.getName() == "") {
                    view.displayMessage("Da huy them san pham.");
                    break;
                }

                // CHẶN BUG BÁN LỖ
                if (newP.getPrice() < newP.getCostPrice()) {
                    view.displayMessage("\t[CẢNH BÁO] Phá sản! Giá bán không thể nhỏ hơn Giá nhập được!");
                    break;
                }

                model.addProduct(newP);
                view.displayMessage("Da them san pham moi!");
                break;
            }

            case 3: { // CẬP NHẬT GIA & SO LUONG
                if (role == "Staff") { view.displayMessage("Khong co quyen!"); break; }

                std::cout << "\n--- CAP NHAT THONG TIN SAN PHAM ---\n";
                std::string id = InputUtils::getValidString("Nhap Ma SP can sua: ");
                if (id == "CANCEL") break;

                // Kiểm tra sự tồn tại của sản phẩm
                auto results = model.searchProducts(id);
                bool found = false;
                for(const auto& res : results) {
                    if(res.getId() == id) { found = true; break; }
                }

                if (!found) {
                    view.displayMessage("Khong tim thay Ma SP nay!");
                } else {
                    double costP = InputUtils::getValidDouble("Gia NHAP moi (Gia von): ");
                    if (costP < 0) break;
                    
                    double sellP;
                    while (true) {
                        sellP = InputUtils::getValidDouble("Gia BAN moi (Niem yet): ");
                        if (sellP < 0) break;
                        
                        // CHẶN BUG BÁN LỖ KHI CẬP NHẬT
                        if (sellP < costP) {
                            view.displayMessage("\t[LỖI] Phá sản! Giá bán phải lớn hơn hoặc bằng Giá nhập!");
                            continue;
                        }
                        break;
                    }
                    if (sellP < 0) break; // Thoát nếu gõ CANCEL lúc vòng lặp hỏi Giá bán

                    int q = InputUtils::getValidInt("So luong ton kho moi: ");
                    if (q < 0) break;

                    // Gọi hàm update với 4 tham số
                    model.updateProduct(id, costP, sellP, q);
                    view.displayMessage("Cap nhat gia va kho hang thanh cong!");
                }
                break;
            }

            case 4: {
                if (role == "Admin") {
                    std::string id = InputUtils::getValidString("Ma SP can xoa: ");
                    if (id == "CANCEL") break;
                    int reason = view.getInputForDeleteReason();
                    if (reason < 0) break;
                    model.deleteProductWithReason(id, reason);
                    view.displayMessage("Da xu ly xoa san pham.");
                } else if (role == "Purchasing") {
                    model.sortProducts();
                    view.displayMessage("Da sap xep kho!");
                }
                break;
            }
            case 5: {
                std::string key = InputUtils::getValidString("Tu khoa thong tin san pham: ");
                if (key == "CANCEL") break;
                view.displayProductList(model.searchProducts(key), isManager);
                break;
            }
            case 6:
                if (role == "Admin") { model.sortProducts(); view.displayMessage("Da sap xep danh sach!"); }
                else if (role == "Purchasing") { view.displayProductList(model.getExpiredProducts(), isManager); }
                break;
            case 7:
                if (role == "Staff") view.displayDiscountedProducts(model.getDiscountedProducts());
                else if (role == "Admin") {
                    view.displayMessage("--- HANG DA HET HAN (CAN TIEU HUY) ---");
                    view.displayProductList(model.getExpiredProducts(), isManager);
                    view.displayDiscountedProducts(model.getDiscountedProducts());
                }
                break;
            case 8: view.displayProductList(model.getFreshProductsToCheck(), isManager); break;

            case 9: { // THANH TOÁN & IN HÓA ĐƠN
                if (role == "Purchasing") { view.displayMessage("Khong co quyen!"); break; }

                std::vector<CartItem> cart;
                std::string phone, id;
                long long grandTotal = 0;

                std::cout << "\n--- POS - QUAY THANH TOAN ---\n";
                std::cout << "SDT Khach hang (Enter de bo qua): ";
                std::cin.ignore();
                std::getline(std::cin, phone);

                Customer* customer = (phone.empty()) ? nullptr : customerModel.getCustomerByPhone(phone);
                if (customer) std::cout << "=> Chao " << customer->getName() << " [" << customer->getMemberLevel() << "]\n";

                while (true) {
                    std::cout << "\nNhap Ma SP (Go '0' de chot don): ";
                    std::string id = InputUtils::getValidString("");
                    if (id == "0") break;
                    if (id == "CANCEL") {
                        view.displayMessage("Da huy ban hang ngang chung.");
                        cart.clear(); // Hủy giỏ hàng
                        break;
                    }

                    auto results = model.searchProducts(id);
                    if (!results.empty() && results[0].getId() == id && results[0].isActive()) {
                        Product& p = results[0];
                        double rate = model.getDiscountRate(p);

                        if (rate == 0) {
                            std::cout << "=> [LOI]: San pham '" << p.getName() << "' da het han!\n";
                        } else {
                            int qty = InputUtils::getValidInt("So luong cho '" + p.getName() + "': ", 1, 100000);
                            if (qty < 0) continue; // Hủy mua món này

                            if (model.sellProduct(id, qty)) {
                                long long itemTotal = (long long)(p.getPrice() * rate * qty);
                                cart.push_back({p, qty, itemTotal});
                                grandTotal += itemTotal;
                                std::cout << "=> Da them " << qty << " " << p.getName() << " vao gio.\n";
                            } else {
                                std::cout << "=> [LOI]: Kho chi con " << p.getQuantity() << " san pham!\n";
                            }
                        }
                    } else {
                        std::cout << "=> [LOI]: Khong tim thay ma SP nay!\n";
                    }
                }

                if (!cart.empty()) {
                    std::cout << "\n\n";
                    std::cout << "        ====================================\n";
                    std::cout << "                CMC MART - HANOI            \n";
                    std::cout << "          DC: He thong Quan ly Sieu thi     \n";
                    std::cout << "        ====================================\n";
                    std::cout << "                 HOA DON BAN LE             \n";
                    std::cout << "        ------------------------------------\n";
                    std::cout << " Khach hang: " << (customer ? customer->getName() : "Khach vang lai") << "\n";
                    std::cout << " Ngay ban  : " << DateUtils::getCurrentDate() << "\n";
                    std::cout << " Thu ngan  : " << currentUser->getName() << "\n";
                    std::cout << "        ------------------------------------\n";

                    std::cout << " " << std::left << std::setw(18) << "TEN SP"
                              << std::setw(5) << "SL"
                              << std::right << std::setw(12) << "T.TIEN" << "\n";
                    std::cout << " " << std::string(35, '-') << "\n";

                    for (const auto& item : cart) {
                        std::string dName = item.product.getName();
                        if (dName.length() > 17) dName = dName.substr(0, 14) + "...";

                        std::cout << " " << std::left << std::setw(18) << dName
                                  << std::setw(5) << item.quantity
                                  << std::right << std::setw(12) << item.subTotal << "\n";

                        long long tCost = (long long)(item.product.getCostPrice() * item.quantity);
                        std::string log = item.product.getId() + "," + std::to_string(item.quantity) + "," +
                                          std::to_string(item.subTotal) + "," + std::to_string(tCost) + "," +
                                          DateUtils::getCurrentDate();
                        FileHandler::appendLine("../data/5_sales/sales_log.csv", log);
                    }

                    std::cout << "        ------------------------------------\n";
                    std::cout << " " << std::left << std::setw(23) << "TONG CONG:"
                              << std::right << std::setw(12) << grandTotal << " VND\n";

                    if (customer) {
                        int pts = (int)(grandTotal / 1000);
                        customer->addPoints(pts);
                        customerModel.saveCustomers();
                        std::cout << " " << std::left << std::setw(23) << "DIEM CONG MOI:"
                                  << std::right << std::setw(11) << "+" << pts << " pts\n";
                        std::cout << " " << std::left << std::setw(23) << "TONG DIEM:"
                                  << std::right << std::setw(12) << customer->getPoints() << " pts\n";
                    }

                    std::cout << "        ====================================\n";
                    std::cout << "             CAM ON & HEN GAP LAI!          \n";
                    std::cout << "        ====================================\n\n";

                    view.displayMessage("THANH TOAN HOAN TAT!");
                } else {
                    view.displayMessage("Don hang trong, da huy!");
                }
                break;
            }

            case 10: {
                if (role == "Purchasing") { view.displayMessage("Khong co quyen!"); break; }
                
                std::string id = InputUtils::getValidString("Ma khach hang moi (VD: KH02): ");
                if (id == "CANCEL") break;

                // CHECK ID KHÁCH HÀNG (Cả ID lẫn SĐT sẽ được check bên CustomerModel nhưng ID check trước cho tiện)
                bool isExist = false;
                for (const auto& c : customerModel.getAllCustomers()) {
                    if (c.getId() == id) { isExist = true; break;}
                }
                if (isExist) {
                    view.displayMessage("\t[LỖI] Mã Khách hàng này đã tồn tại!");
                    break;
                }

                Customer newC = view.getInputForNewCustomer(id);
                if (newC.getName() == "") {
                    view.displayMessage("Da huy dang ky khach hang.");
                    break;
                }

                if (customerModel.addCustomer(newC)) {
                    view.displayMessage("Dang ky khach hang thanh cong!");
                } else {
                    view.displayMessage("\t[LỖI] Số điện thoại đã được đăng ký cho Khách hàng khác!");
                }
                break;
            }

            case 11: { // BÁO CÁO LỢI NHUẬN
                if (role != "Admin") { view.displayMessage("Chi Admin moi xem duoc!"); break; }

                std::vector<std::string> lines = FileHandler::readLines("../data/5_sales/sales_log.csv");
                long long totalRev = 0;
                long long totalProfit = 0;
                int totalItems = 0;

                for (const auto& line : lines) {
                    auto tokens = FileHandler::split(line, ',');
                    if (tokens.size() >= 4) {
                        long long rev = std::stoll(tokens[2]);
                        long long cost = std::stoll(tokens[3]);
                        totalRev += rev;
                        totalProfit += (rev - cost);
                        totalItems += std::stoi(tokens[1]);
                    }
                }
                view.displayRevenueReport(totalRev, totalItems, totalProfit);
                break;
            }

            case 12: { // QUẢN LÝ NGÀNH HÀNG
                if (role != "Admin") { view.displayMessage("Không có quyền!"); break; }
                std::cout << "\n--- QUẢN LÝ NGÀNH HÀNG ---\n";
                int choiceCat;
                do {
                    std::cout << "1. Xem danh sách ngành hàng\n";
                    std::cout << "2. Thêm ngành hàng mới\n";
                    std::cout << "0. Thoát\n";
                    choiceCat = InputUtils::getValidInt("Lựa chọn: ", 0, 2);

                    if (choiceCat == 1) {
                        const auto& cats = categoryModel.getAllCategories();
                        std::cout << "\nDanh sách ngành hàng hiện tại:\n";
                        for (size_t i = 0; i < cats.size(); i++) {
                            std::cout << i + 1 << ". " << cats[i] << "\n";
                        }
                        std::cout << "\n";
                    } else if (choiceCat == 2) {
                        std::string name = InputUtils::getValidName("Tên ngành mới: ");
                        if (name == "CANCEL") continue;
                        if (categoryModel.addCategory(name)) {
                            std::cout << "=> Đã thêm ngành hàng thành công!\n\n";
                        } else {
                            std::cout << "=> [LỖI]: Ngành hàng đã tồn tại.\n\n";
                        }
                    }
                } while (choiceCat != 0);
                break;
            }

            case 0: break;
            default: view.displayMessage("Lua chon sai!"); break;
        }
    } while (choice != 0);
}