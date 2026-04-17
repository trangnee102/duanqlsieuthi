# 📑 TÀI LIỆU KẾ HOẠCH KIỂM THỬ TỔNG THỂ (MASTER TEST PLAN)
**Dự Án:** Hệ thống Quản Lý Siêu Thị C++ (Terminal POS Application)
**Phiên Bản:** 1.0 (Báo cáo Đồ án Cuối kỳ)

---

## 1. MỤC TIÊU VÀ PHẠM VI (SCOPE & OBJECTIVES)
### Mục tiêu:
* Đảm bảo toàn bộ các module chức năng (Kho hàng, Bán hàng, Báo cáo, Đăng nhập) hoạt động ở độ ổn định 100%.
* Không xảy ra sai lệch số liệu về dòng tiền và số lượng thực tế trong file CSV.
* Ngăn chặn các lỗi tràn ngập nhập liệu (Vibe coding errors, infinite loops) trên terminal.

### Phạm vi (In Scope):
1. Phân hệ Xác thực tài khoản (Auth Module).
2. Phân hệ Quản lý Kho & Lô Hàng (Inventory & Batch Module).
3. Phân hệ Thu ngân & Chiết khấu (POS & Membership Module).
4. Phân hệ Báo cáo Doanh thu đa mốc thời gian (Financial Report).

---

## 2. NHÓM KIỂM THỬ & PHÂN CÔNG (RESOURCE & ASSIGNMENT)

| Thành Viên | Vai Trò (Role) | Module Phụ Trách Kiểm Thử (Assigned Module) |
| :--- | :--- | :--- |
| **Ngọc Hà** | Test Lead / Tester | **Phân hệ Kho hàng (Inventory)**, **Hệ thống Lô Hàng (Batch)** & **Xác thực (Auth)** (Test thêm/xóa/sửa SP, thuật toán FIFO logic). |
| **Xuân Hiệp** | Tester / QA / Data Analyst | **Phân hệ Thu Ngân (POS)**, **Thẻ Thành Viên** & **Báo Cáo (Reports)** (Test giảm giá, tính tiền chuẩn, biểu đồ hiển thị đúng). |

---

## 3. KỊCH BẢN KIỂM THỬ (TEST SCENARIOS)

Dưới đây là các cụm Test Scenario (TS) cấp cao để phân rã ra các Test Case chi tiết:

*   **TS_01:** Kiểm tra luồng Đăng nhập & Xác thực phân quyền tài khoản (Admin, Staff, Purchasing).
*   **TS_02:** Kiểm tra thao tác Quản lý Sản phẩm (Thêm/Sửa giá/Ngừng kinh doanh).
*   **TS_03:** Kiểm tra thuật toán Trừ Khấu Hao Lô Hàng (FIFO) & Hạn sử dụng.
*   **TS_04:** Kiểm tra Máy tính tiền (POS) & Chính sách Thẻ Thành Viên VIP.
*   **TS_05:** Kiểm tra Báo cáo Doanh thu & Cảnh báo Tồn kho.

---

## 4. CHI TIẾT TEST CASES (TEST CASE ĐẠI DIỆN)

> *(Lưu ý: Bạn đã có các file từ `test_cases 1.md` đến `test_cases 8.md` chứa mười mấy test case cụ thể. Dưới đây là bảng tổng hợp tóm tắt để cho vào báo cáo đồ án).*

| ID Test Case | Thuộc Scenario | Mô tả (Description) | Expected Result | Tester Phụ Trách |
| :---: | :---: | :--- | :--- | :---: |
| **TC_01.1** | TS_01 | Đăng nhập với quyền Admin | Mở Menu đầy đủ 15 Chức năng. | **Ngọc Hà** |
| **TC_01.2** | TS_01 | Staff truy cập chức năng cấm (Thanh lý) | Hệ thống báo lỗi "Không có quyền". | **Ngọc Hà** |
| **TC_02.1** | TS_02 | Thêm SP mới thuộc ngành Fresh Food | Hệ thống tự gán Date = Today, bỏ qua bước hỏi HSD. | **Ngọc Hà** |
| **TC_03.1** | TS_03 | Hệ thống trừ tồn kho khi KH Mua (FIFO) | Lô hàng cũ nhất sẽ bị bào mòn số lượng về 0 trước. | **Ngọc Hà** |
| **TC_04.1** | TS_04 | Giảm giá tự động hàng cận Date | SP nào sát hạn sẽ được quét mã giảm trừ vào Bill. | **Xuân Hiệp** |
| **TC_04.2** | TS_04 | Tích điểm cho KH đăng ký Số DT mới | KH sinh mã `KHxx`, điểm sau mua tính = Total/10000. | **Xuân Hiệp** |
| **TC_05.1** | TS_05 | Biểu đồ báo cáo 7 Ngày Qua | Biểu đồ ASCII tự scale theo ngày lớn nhất, không vỡ. | **Xuân Hiệp** |

---

## 5. MA TRẬN THEO DÕI ĐỘ PHỦ (REQUIREMENTS TRACEABILITY MATRIX - RTM)

*RTM dùng để chứng minh với Giáo viên rằng: "Mỗi một tính năng yêu cầu (Requirement) đều đã có Case kiểm tra, không bỏ sót tính năng nào".*

| Mã Yêu Cầu (REQ_ID) | Tên Tính Năng (Feature Specification) | Scenario Phủ | Test Case Khớp | Trạng thái Pass/Fail Test |
| :--- | :--- | :---: | :---: | :---: |
| **REQ_AUTH** | Phân quyền 3 role (Staff, Purchasing, Admin) | TS_01 | TC_01.1, TC_01.2 | `[PASS]` |
| **REQ_INV_1** | CRUD Sản phẩm & Tự động Suggestion Mã SP | TS_02 | TC_02.1, ... | `[PASS]` |
| **REQ_BATCH** | Quản lý lô hàng dạng cây (Tree-view) và FIFO | TS_03 | TC_03.1 | `[PASS]` |
| **REQ_VIP_0** | Đăng ký chặn trùng số Điện thoại & Auto-ID | TS_04 | TC_04.2 | `[PASS]` |
| **REQ_POS_1** | Tính tiền & Chiết khấu Thành viên, Cận date | TS_04 | TC_04.1, TC_04.2 | `[PASS]` |
| **REQ_REP_1** | Trích xuất báo cáo theo Ngày/Tháng/Quý/Tuần | TS_05 | TC_05.1 | `[PASS]` |

---

## 6. MÔI TRƯỜNG KIỂM THỬ (TEST ENVIRONMENT)
*   **Hệ điều hành:** Windows 10/11 (Hoặc tương đương hỗ trợ C++).
*   **Terminal:** CMD / Powershell / Git Bash (Yêu cầu hỗ trợ UTF-8 để hiển thị Tiếng Việt).
*   **Database:** `*.csv` files nằm trong thư mục `data/`. File cần được Reset Blank Text trước khi bắt đầu Phase Test.
