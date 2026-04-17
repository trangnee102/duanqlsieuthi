# 🏆 Kịch Bản Kiểm Thử (Test Cases) - Lần 8: Hệ Thống Client Module (Thẻ Thành Viên VIP)

Tài liệu này bao gồm các kịch bản kiểm thử toàn diện dành cho **Chức năng Đăng ký và Trụ cột Thanh toán Thẻ Thành Viên (Membership)**, giúp đánh giá khả năng bảo mật SĐT và quy đổi điểm hoàn toàn tự động.

---

## 🛑 Test Case 1: Đăng ký Thẻ VIP - Chặn trùng lặp SĐT
**Mục tiêu:** Hệ thống thiết kế để SĐT là định danh duy nhất (Unique). Việc khách hàng vô tình hay cố tình đăng ký 2 thẻ trùng 1 SĐT phải bị chặn lại.
* **Người thực hiện:** Bất kỳ quyền nào (Kể cả Staff).
* **Các bước thực hiện:**
    1. Vào **Menu [10] QUẢN LÝ THÀNH VIÊN KHÁCH HÀNG (Membership)**.
    2. Cố tình nhập một Số điện thoại đã có từ trước (Hoặc có sẵn trong file `data/customers.csv`, ví dụ: `0981234567`).
* **Kết quả mong đợi:**
    * Hệ thống không cho phép nhập Tên hay tiếp tục thao tác.
    * Xuất hiện thông báo lỗi: `=> [LỖI]: SĐT 0981234567 đã được đăng ký cho KH: [Tên khách cũ] (...)!`
    * Đẩy tài khoản thoái lui về Menu chính mà không tạo ra bất cứ thẻ lặp nào.
* **Trạng thái:** `[ ] Pass` | `[ ] Fail`

---

## 🆕 Test Case 2: Đăng ký Thẻ VIP - Tự động định danh (Auto-ID)
**Mục tiêu:** Nhân viên thu ngân không được phép tự gõ ID Khách như `KH01`, hệ thống phải cấp phát ID tự động theo quy tắc tuần tự lớn nhất trong hệ thống.
* **Các bước thực hiện:**
    1. Vào **Menu [10] QUẢN LÝ THÀNH VIÊN KHÁCH HÀNG (Membership)**.
    2. Nhập một SĐT mới tinh chưa từng tồn tại: `0900111222`.
    3. Tên khách hàng: `Nguyen Van Test`.
* **Kết quả mong đợi:**
    * Hệ thống quét toàn bộ DB Khách hàng hiện tại (VD mã lớn nhất đang là `KH04`), sẽ tự động bốc và nhảy số tạo ra thẻ mới mang tên `KH05`.
    * Thông báo in ra màn hình: `=> [THÀNH CÔNG]: Đã đăng ký VIP! Mã KH của khách là: KH05`.
* **Trạng thái:** `[ ] Pass` | `[ ] Fail`

---

## 🪙 Test Case 3: Quy đổi Điểm & Hạng Thành Viên trực tiếp tại POS
**Mục tiêu:** Khách hàng quẹt thẻ đọc số điện thoại sẽ lập tức được ghi nhận và chiết khấu ngay tại bill dựa trên số điểm đã tích lũy các lần mua trước.
* **Quy tắc giả định:** Khách vãng lai (0%), Thẻ Bạc (giảm một khoản nhất định), Vàng, Kim Cương... (được code tại Customer.cpp/model.getDiscountRate).
* **Các bước thực hiện:**
    1. Giả sử Khách hàng `0900111222` vừa đăng ký ở TC2. Hiện tại điểm = 0 (Hạng Vãng lai/Thường).
    2. Vào **Menu [9] GIAO DỊCH POS**.
    3. Nhập SĐT khách hàng: `0900111222`. Hệ thống tự động catch KH này.
    4. Mua 1 sản phẩm có giá trị lớn (Ví dụ: `5,000,000 VND`). 
    5. Chốt đơn xác nhận Y.
    6. Mở file `data/customers.csv` hoặc check thông tin KH này (Qua file) để xem số điểm được cộng thêm.
* **Kết quả mong đợi:**
    * Ở hoá đơn tại khoảnh khắc bấm POS (khi điểm chưa cộng), chiết khấu VIP là `0 VND`. KH phải trả đủ `5,000,000 VND`.
    * Sau khi bill chốt thành công, hệ thống áp dụng công thức: `Điểm = Tổng bill / 10000` -> Bạn sẽ thấy khách hàng này được cộng **500 Điểm**.
* **Trạng thái:** `[ ] Pass` | `[ ] Fail`

---

## 💎 Test Case 4: Chiết Khấu Nâng Hạng (Auto-Discount for VIP)
**Mục tiêu:** Test xem số điểm 500 ở trên có cho khách hàng đặc quyền VIP ở lần POS thứ 2 hay không.
* **Các bước thực hiện:**
    1. Tiếp tục vào lại **Menu [9] GIAO DỊCH POS**.
    2. Nhập ngay lập tức Số điện thoại trên: `0900111222`.
    3. Quét một món hàng bất kỳ giá `100,000 VND`. Chốt đơn ngay để xem bill tạm tính.
* **Kết quả mong đợi:**
    * Ở dòng `Chiết khấu thành viên (...)` sẽ không còn ghi 0 VND nữa! Hệ thống sẽ dựa vào số 500 điểm tích lũy khổng lồ lúc trước để đưa KH này lên hạng VIP (VD: Platinum/Gold) và trực tiếp giảm tiền bill lần này. 
    * `[THÀNH CÔNG]` Bill trừ giá khớp và đúng cơ chế Loyalty Program.
* **Trạng thái:** `[ ] Pass` | `[ ] Fail`
