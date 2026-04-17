# 🧪 Kịch Bản Kiểm Thử (Test Cases) - Lần 6: Quản Lý Lô Hàng (Batch Management)

Tài liệu này cung cấp các kịch bản kiểm thử (Test Cases) để bạn (hoặc giáo viên) có thể đánh giá tính đúng đắn của **Giai đoạn 1: Quản lý Lô hàng (Batch), hiển thị chi tiết và xuất xuất theo quy tắc FIFO.** 

Hãy chạy chương trình và làm theo từng bước mô tả bên dưới để xác nhận xem kết quả có đúng mong đợi hay không.

---

## 🥝 Test Case 1: Tự động gán hạn sử dụng cho Thực Phẩm Tươi Sống
**Mục tiêu:** Kiểm tra xem khi tạo mới sản phẩm thuộc nhóm "Thực phẩm hoặc đồ ăn trong ngày", hệ thống có tự động lấy hạn sử dụng là ngày sinh ra giao dịch (Today) hay không.
* **Người thực hiện:** Admin / Purchasing
* **Các bước thực hiện:**
    1. Đăng nhập hệ thống với quyền tài khoản nhập hàng.
    2. Chọn **Menu [2] Nhập hàng mới**.
    3. Nhập ID: `RAU01` (hoặc mã chưa từng tồn tại).
    4. Tên SP: `Rau Xà Lách`.
    5. Đơn vị tính: `bo`.
    6. Ngành Hàng: Chọn số tương ứng với mục `Đồ ăn trong ngày` (hoặc tên nhóm tươi sống).
    7. Điền giá nhập: `5000` / giá bán: `10000`.
    8. Số lượng: `20`.
    9. Chọn vào Menu [1] Xem danh sách sản phẩm đang bán.
* **Kết quả mong đợi:**
    * Hệ thống **KHÔNG** hề hỏi "Hạn sử dụng là bao nhiêu?".
    * Khi xem danh sách tại menu 1, `RAU01` hiện HSD trùng đúng với ngày hiện tại của máy tính, có chữ "tuoi".
    * Dòng chi tiết Lô hàng ở dưới sẽ xuất hiện dạng: `↳ [Lô LRAU01_xxxxx]  SL: 20   Nhập: Ngày hôm nay  HSD: Ngày hôm nay`.
* **Trạng thái:** `[ ] Pass` | `[ ] Fail`

---

## 🗃️ Test Case 2: Hiển thị Tree-View chi tiết các Lô hàng 
**Mục tiêu:** Kiểm tra cập nhật UI cho việc hiển thị Lô hàng bên dưới mục hàng hoá chính.
* **Người thực hiện:** Admin / Purchasing / Staff
* **Các bước thực hiện:**
    1. Chọn **Menu [14] Nhập thêm Lô hàng bổ sung**.
    2. Nhập mã ID của 1 sản phẩm đã tồn tại (Ví dụ: `SP01` - Sữa chua Vinamilk).
    3. HSD mới: Cách ngày hiện tại tầm 1 tháng. (Vd: `2026-05-20`). Số lượng: `50`.
    4. Trở ra Menu, bấm phím `1` để xem "Danh sách sản phẩm đang bán".
* **Kết quả mong đợi:**
    * Tại sản phẩm `SP01`, cột SL(Tổng) hiện số lượng tăng thêm 50.
    * Có **hai dòng** chi tiết nằm bên dưới sản phẩm `SP01`:
      - 1 dòng chi tiết của Lô đầu tiên mang số lượng và HSD cũ.
      - 1 dòng chi tiết của Lô mới nhập vừa tạo (`↳ [Lô LSP01_xxxx] SL: 50...HSD: 2026-05-20`).
* **Trạng thái:** `[ ] Pass` | `[ ] Fail`

---

## 🛒 Test Case 3: Thuật toán Bán hàng FIFO (First In First Out)
**Mục tiêu:** Tại quầy Thanh Toán (POS), khi khách hàng mua đúng sản phẩm có nhiều lô kết hợp, hệ thống phải tự động bào mòn số lượng của lô cũ/hạn gần nhất trước.
* **Người thực hiện:** Staff / Admin
* **Dữ liệu chuẩn bị:** 
    * Sản phẩm có 2 Lô hàng:
      * Lô A: SL `10` chiếc (HSD gần nhất/cũ nhất).
      * Lô B: SL `50` chiếc (HSD nằm xa hơn).
    * Tổng SL của sản phẩm: `60`.
* **Các bước thực hiện:**
    1. Vào **Menu [9] Thanh toán hóa đơn**.
    2. Nhập SĐT Vãng lai: `0`.
    3. Quét mã ID của sản phẩm trên. Nhập số lượng mua là **`15`** chiếc.
    4. Gõ `0` chốt đơn rồi bấm `Y` (Xác nhận xuất hóa đơn).
    5. Quay lại Menu, bấm `1` để xem Danh sách Sản phẩm.
* **Kết quả mong đợi:**
    * Khách hàng chi trả thành công và số lượng hóa đơn phản ánh đúng giá trị 15 chiếc.
    * Khi xem ở bảng Danh sách: Tổng Số lượng phải còn `45` chiếc.
    * **Quan trọng:** Ở dòng hiển thị chi tiết (Tree-View):
      - `Lô A`: Số lượng bị trừ thành `0` và biến mất (hoặc còn lại 0).
      - `Lô B`: Số lượng bị trừ bớt 5 cái, còn lại đúng `45` chiếc.
* **Trạng thái:** `[ ] Pass` | `[ ] Fail`

---

## 🚫 Test Case 4: Cảnh báo Tồn Kho tự tính tổng tất cả các lô
**Mục tiêu:** Tính năng Tồn Kho (Low Stock) không nhầm lẫn giữa Lô phụ và Tồn Kho Tổng.
* **Các bước thực hiện:**
    1. Giả sử hệ thống thiết lập cảnh báo tồn kho nếu TỔNG số lượng dưới 15 cái.
    2. Trong kho: Sp A có Lô 1 (SL 10), Lô 2 (SL 6). 
    3. Bấm **Menu [13] Xem cảnh báo tồn kho**.
* **Kết quả mong đợi:**
    * Tổng cộng SP A là 16. Phải **KHÔNG** xuất hiện trong danh sách sắp hết nếu ngưỡng là < 15. Hệ thống hoàn toàn thông minh.
* **Trạng thái:** `[ ] Pass` | `[ ] Fail`
