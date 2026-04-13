#include "controllers/EmployeeController.h"
#include "utils/InputUtils.h"
#include <iostream>
#include <string>

// 1. Constructor: Nhận tham chiếu để dùng chung dữ liệu với AuthModel tổng
EmployeeController::EmployeeController(AuthModel& m, EmployeeView& v)
    : model(m), view(v) {}

// 2. Vòng lặp điều hướng chính
void EmployeeController::run() {
    int choice;
    do {
        view.displayPersonnelMenu(); // Hiện Menu quản lý nhân viên
        choice = InputUtils::getValidInt("", 0, 5);

        switch (choice) {
            case 1: // Xem danh sách
                view.displayEmployeeList(model.getAllEmployees());
                break;

            case 2: // Thêm nhân viên mới
            {
                Employee newEmp = view.getInputForNewEmployee();
                if (newEmp.getId() == "") {
                    view.displayMessage("Da huy them nhan vien!");
                    break;
                }
                if (model.addEmployee(newEmp)) {
                    view.displayMessage("Da them nhan vien moi vao he thong!");
                } else {
                    view.displayMessage("LOI: Ma Nhan Vien da ton tai!");
                }
                break;
            }

            case 3: { // Cập nhật Quyền / Mật khẩu
                std::string id = view.getInputEmployeeId();
                if (id == "CANCEL") break;

                // --- FIX LỖI NHÂN VIÊN MA ---
                bool found = false;
                for (const auto& emp : model.getAllEmployees()) {
                    if (emp.getId() == id) { found = true; break; }
                }

                if (!found) {
                    view.displayMessage("LOI: Khong tim thay nhan vien ma " + id);
                    break; // Dừng luôn, không cho nhập linh tinh nữa
                }
                // ----------------------------

                std::string role = view.getInputNewRole();
                if (role == "CANCEL") break;
                std::string pass = view.getInputNewPassword();
                if (pass == "CANCEL") break;

                model.updateEmployee(id, role, pass);
                view.displayMessage("Da cap nhat thong tin nhan vien " + id);
                break;
            }

            case 4: { // Khóa tài khoản (Xóa mềm)
                std::string id = view.getInputEmployeeId();
                if (id == "CANCEL") break;

                // --- FIX LỖI NHÂN VIÊN MA ---
                bool found = false;
                for (const auto& emp : model.getAllEmployees()) {
                    if (emp.getId() == id) { found = true; break; }
                }

                if (!found) {
                    view.displayMessage("LOI: Khong tim thay nhan vien ma " + id);
                    break;
                }
                // ----------------------------

                model.deleteEmployee(id);
                view.displayMessage("Da khoa tai khoan nhan vien " + id);
                break;
            }

            // === THÊM MỚI: PHÍM 5 - CHẤM CÔNG NHÂN VIÊN ===
            case 5: {
                std::cout << "\n--- CHAM CONG NHAN VIEN ---\n";
                std::string id = InputUtils::getValidString("Nhap Ma NV: ");
                if (id == "CANCEL") break;

                // Kiểm tra xem NV có tồn tại không
                bool found = false;
                for (const auto& emp : model.getAllEmployees()) {
                    if (emp.getId() == id) { found = true; break; }
                }

                if (!found) {
                    view.displayMessage("LOI: Khong tim thay nhan vien ma " + id);
                } else {
                    int hours = InputUtils::getValidInt("Nhap so gio lam them: ", 0, 1000);
                    if (hours < 0) break;

                    // Gọi hàm cập nhật giờ công từ Bộ não
                    model.updateWorkingHours(id, hours);
                    view.displayMessage("Cham cong thanh cong! Da cong them " + std::to_string(hours) + " gio.");
                }
                break;
            }

            case 0:
                view.displayMessage("Dang quay lai Menu chinh...");
                break;

            default:
                view.displayMessage("Lua chon khong hop le!");
                break;
        }
    } while (choice != 0);
}