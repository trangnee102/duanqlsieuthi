# 📊 Kịch Bản Kiểm Thử (Test Cases) - Lần 7: Hệ Thống Báo Cáo Tài Chính Đa Dạng Mốc Thời Gian

Tài liệu này cung cấp các kịch bản kiểm thử để đánh giá tính chính xác của **Giai đoạn 2: Cải tiến Báo cáo Tài Chính đa dạng (Tất cả / Ngày / Tuần / Tháng / Quý) kèm Biểu đồ**.

Hãy chạy chương trình và làm theo các bước bên dưới.

---

## 📈 Test Case 1: Kiểm thử cấu trúc Menu & Báo Cáo Ngày / Tháng
**Mục tiêu:** Xác nhận các phím điều hướng mới trong Menu Số 11 hoạt động đúng và bộ lọc thời gian cắt được dữ liệu chuẩn xác.
* **Người thực hiện:** Admin / Trưởng ca
* **Dữ liệu chuẩn bị:** (Dựa trên lịch sử file `history_transactions.csv`). Giả sử hôm nay là ngày thực trên máy tính của bạn (VD: 16/04/2026).
* **Các bước thực hiện:**
    1. Vào hệ thống với tài khoản Quản lý.
    2. Chọn **Menu [11] Báo cáo tài chính & lợi nhuận**.
    3. Kiểm tra xem màn hình Menu con đã hiện ra 5 dòng lựa chọn chưa: `1. Tất cả | 2. Hôm Nay | 3. 7 Ngày Qua | 4. Tháng Này | 5. Quý Này`.
    4. Bấm phím `2` (Hôm nay). Ghi nhớ con số **Tổng Doanh Thu**.
    5. Nhấn Enter quay lại, lại vào Menu 11 bấm phím `4` (Tháng Này).
* **Kết quả mong đợi:**
    * Menu con hiển thị đầy đủ 5 tuỳ chọn.
    * Khi chọn **Hôm Nay (2)**: Danh sách báo cáo liệt kê tất cả các hoá đơn có ngày phát sinh trùng khớp ký tự với ngày hôm nay `YYYY-MM-DD`. Những giao dịch cũ của hôm qua sẽ không hiện. 
    * Khi chọn **Tháng Này (4)**: Doanh thu hiển thị chắc chắn phải **Lớn hơn hoặc Bằng (>=)** mức doanh thu của Hôm Nay. Nếu bằng 0 thì Fail.
* **Trạng thái:** `[ ] Pass` | `[ ] Fail`

---

## 📅 Test Case 2: Kiểm thử Báo cáo Quý (Quarterly Report)
**Mục tiêu:** Đảm bảo hệ thống gom chính xác các tháng thành từng Quý (Q1, Q2, Q3, Q4).
* **Tư duy Logic:** Quý 1 (tháng 1,2,3), Quý 2 (tháng 4,5,6), Quý 3 (tháng 7,8,9), Quý 4 (tháng 10,11,12).
* **Các bước thực hiện:**
    1. Bạn thực hiện mua giả lập (Menu 9) 1 đơn hàng giá `50,000 VND` vào ngày hôm nay. (Giả sử đang ở Tháng 4 - tức Quý 2).
    2. Truy cập **Menu [11] Báo cáo tài chính & lợi nhuận**.
    3. Chọn phím `5` (Quý Này).
* **Kết quả mong đợi:**
    * Kết quả lọc phải bắt được hoá đơn `50,000 VND` vừa tạo, và hiển thị kèm với các hoá đơn thuộc cùng các tháng trong nhánh (ví dụ: Tháng 4, 5, 6 chung 1 Quý).
    * Tổng số lượng đơn hàng có lý.
* **Trạng thái:** `[ ] Pass` | `[ ] Fail`

---

## 💹 Test Case 3: Trình tạo Biểu Đồ Thanh (ASCII Bar Chart) 7 Ngày
**Mục tiêu:** Đảm bảo đồ thị cột hiển thị đúng tỷ lệ tương đối giữa các ngày, kể cả khi có ngày doanh thu = 0.
* **Các bước thực hiện:**
    1. Truy cập **Menu [11] Báo cáo tài chính & lợi nhuận**.
    2. Chọn phím `3` (7 Ngày Qua).
* **Kết quả mong đợi:**
    * Màn hình liệt kê từng dòng giao dịch của 7 ngày qua.
    * Ở góc dưới màn hình vẽ ra một bảng `--- BIỂU ĐỒ DOANH THU 7 NGÀY QUA ---` chứa đúng 7 cột (tương ứng 7 ngày gần nhất, đếm ngược từ hôm nay).
    * Ngày nào có doanh thu `0 VND`, phần độ dài của chuỗi hashtag `#` sẽ hoàn toàn rỗng.
    * Ngày nào có doanh thu **Lớn nhất**, chiều dài cột `#` sẽ full thanh biểu đồ (tối đa ~40 ký tự `#`).
    * Ngày nào có doanh thu ở mức 0 nhưng rớt vào vài nghìn (vẫn > 0 nhưng cực kỳ bé so với tổng), cột vẫn phải nhú lên `1 dấu #` để chứng minh là "có phát sinh giao dịch", không được phép lặn mất tăm như `0 VND`.
* **Trạng thái:** `[ ] Pass` | `[ ] Fail`

---

## 💰 Test Case 4: Kiểm thử Sự liên kết dòng tiền (Độ chính xác của Data)
**Mục tiêu:** Đảm bảo số liệu thanh toán bị trừ khuyến mãi, thẻ VIP đều được ghi nhận đúng vào hệ thống thay vì ghi khống.
* **Các bước thực hiện:**
    1. Vào **Menu [9] Thanh toán**, tạo 1 đơn hàng cho Khách VIP được giảm 5%. 
    2. Tổng bill ban đầu là `100,000 VND`, chiết khấu thành viên trừ `5,000 VND`. Bạn bấm xuất bill thành công với giá chốt `95,000 VND`.
    3. Vào **Menu [11]**, truy cập mục `2` (Hôm nay).
* **Kết quả mong đợi:**
    * Hoá đơn vừa bán phải ghi nhận doanh thu cột cuối nằm ở con số `95000` thay vì `100000`. Hệ thống ăn khớp hoàn hảo giữa module này với module kia.
* **Trạng thái:** `[ ] Pass` | `[ ] Fail`
