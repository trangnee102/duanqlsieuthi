# 🧪 Kịch Bản Kiểm Thử (Test Cases) - Lần cập nhật 14/04/2026

Dưới đây là các kịch bản kiểm thử (Test Cases) thủ công để đội ngũ phát triển (hoặc tester) có thể tự chạy lại trên giao diện Console và xác minh rằng 4 lỗi khẩn cấp (High Priority Bugs) đã hoàn toàn được khắc phục.

---

## 🟢 TC01: Kiểm tra mở Menu Quản lý Ngành Hàng (Mục 12)

**Mục đích:** Đảm bảo Admin có thể truy cập tính năng "Quản lý ngành hàng" từ Menu Chính mà không bị chặn bởi bộ lọc input.
*   **Tiền điều kiện:** Đăng nhập thành công với một tài khoản mang quyền `Admin`.
*   **Các bước thực hiện:**
    1. Quan sát màn hình Console hiển thị "MENU CHÍNH (QUẢN LÝ)". Chọn phím `1` để vào Menu Kho Hàng.
    2. Quan sát Menu Quản lý kho, thấy có hiển thị mục `12. QUẢN LÝ NGÀNH HÀNG`.
    3. Nhập `12` và nhấn Enter.
*   **Kết quả mong đợi:** 
    * Hệ thống KHÔNG CÒN hiển thị lỗi _"Lỗi, vui lòng nhập lại từ 0 đến 11"_.
    * Màn hình chuyển sang giao diện `--- QUẢN LÝ NGÀNH HÀNG ---` bao gồm các mục (1. Xem danh sách, 2. Thêm ngành hàng...). 

---

## 🟢 TC02: Kiểm tra chuẩn hoá Quyền (Role) chuẩn Title Case

**Mục đích:** Xác minh người dùng khi tạo mới hoặc cập nhật nhân viên, hễ gõ role (chức vụ) chữ thường/chữ in hoa lộn xộn đều phải được quy chuẩn về đúng định dạng (Ví dụ: `admin` -> `Admin`).
*   **Tiền điều kiện:** Đăng nhập thành công với quyền `Admin`.
*   **Các bước thực hiện:**
    1. Tại Menu Chính, chọn `2` để vào "Quản lý nhân viên".
    2. Chọn `2` (Thêm nhân viên mới).
    3. Điền các trường Họ tên, SĐT, ID, Mật khẩu bình thường.
    4. Tại mục _"Chức vụ (Admin/Staff/Purchasing)"_, cố tình nhập: `admin` (hoặc `aDmin`, `ADMIN`).
    5. Sau khi tạo xong, trở lại menu và chọn `1` (Xem danh sách nhân viên).
*   **Kết quả mong đợi:**
    * Tại bảng danh sách, cột "CHỨC VỤ" của nhân viên vừa tạo phải hiển thị chính xác là `Admin` (chữ A viết hoa, còn lại viết thường).
    * Khi dùng nhân viên này đăng nhập thử, hệ thống sẽ mở đúng Menu dành cho Quản lý chứ không bị nhầm xuống Purchasing.

---

## 🟢 TC03: Kiểm tra Lỗi Trùng Lặp ID (Không phân biệt Hoa/Thường)

**Mục đích:** Xác minh không có chuyện `NV01` và `nv01` có thể cùng lúc tồn tại gây nhầm lẫn trên hệ thống.
*   **Tiền điều kiện:** Đăng nhập thành công với quyền `Admin`. Trong DB đã tồn tại một nhân viên (hoặc tài khoản hiện tại) có ID là `ADMIN01` (Viết hoa toàn bộ).
*   **Các bước thực hiện (Tạo mới):**
    1. Chọn thêm nhân viên mới.
    2. Tại mục nhập mã NV (ID), cố tình nhập `admin01` (Viết thường toàn bộ).
*   **Kết quả mong đợi (Tạo mới):** 
    * Hệ thống từ chối cho đi tiếp và in ra cảnh báo: `[LỖI] Mã ID này đã tồn tại! Vui lòng chọn mã khác.`
*   **Các bước thực hiện (Đăng nhập):**
    1. Thoát hệ thống ra màn hình đăng nhập.
    2. Tại phần nhập Mã nhân viên, nhập `aDmIn01` cùng với mật khẩu đúng của tài khoản `ADMIN01`.
*   **Kết quả mong đợi (Đăng nhập):**
    * Hệ thống cho phép đăng nhập thành công vào tài khoản `ADMIN01`, bất chấp việc ghi sai chuẩn hoa/thường ở màn hình Login.

---

## 🟢 TC04: Kiểm tra Tìm Kiếm Tiếng Việt "Không Dấu"

**Mục đích:** Đảm bảo hệ thống xoá được dấu tiếng Việt của từ khoá và bộ nhớ đệm trước khi so khớp, giúp tìm kiếm thuận tiện hơn.
*   **Tiền điều kiện:** Đăng nhập thành công. Trong kho hàng phải có sẵn ít nhất 1 sản phẩm có tiếng Việt có dấu (Ví dụ: Tên SP `Sữa chua Lộc Phát`, ID `SC01`).
*   **Các bước thực hiện:**
    1. Tại Menu kho hàng, chọn phím `5` để mở tính năng (Tìm kiếm sản phẩm).
    2. Tại dòng _"Tu khoa thong tin san pham:"_, cố tình gõ không dấu chữ thường: `sua chua` (hoặc `loc phat`).
*   **Kết quả mong đợi:**
    * Bảng in ra kết quả phải bắt dính sản phẩm `Sữa chua Lộc Phát`.
    * Dù từ khoá là không dấu (`sua chua`) nhưng hệ thống vẫn nhận diện được nó tương đương với chuỗi có dấu (`Sữa chua`) và hiển thị đúng record.
