# 🧪 Kịch Bản Kiểm Thử (Test Cases) - Phiên Bản 3.0 Đầu Tiếng Việt

Bộ test case này bao gồm các trường hợp Thực chiến (Black-box Testing) rất trực quan. Bạn hãy Build (Run) phần mềm và nhập đúng nguyên văn theo bảng dưới đây để cảm nhận sự kiên cố của chương trình nhé!

## 1. Test Dữ Liệu Input Tiếng Việt & Chặn Số (Bug UTF-8)
**Mục tiêu:** Kiểm tra C++ Console đã nạp lệnh `SetConsoleCP` cho tiếng Việt dấu chưa, và `InputUtils::getValidName` đã chặn số nhưng vẫn tha cho chữ cái có dấu hay chưa.

*   **Bước 1:** Đăng nhập vào Admin `admin01`, mật khẩu `admin01`.
*   **Bước 2:** Chọn số `2` (Thêm nhân viên mới). Nhập Mã NV là `NV099`.
*   **Bước 3 (Gõ rác):** Tại phần *Họ tên*, hãy cố tình nhập: `Trần V@n 123` và ấn Enter.
    *   ✅ **Kỳ vọng:** Máy chửi ngay: `[Thông báo]: Tên không được chứa Chữ số (0-9) hay Ký tự đặc biệt!`.
*   **Bước 4 (Gõ dính dấu Tiếng Việt):** Tại phần hỏi lại *Họ tên*, hãy nhập chính xác: `Dương Quá` (Gõ Telex có dấu đàng hoàng).
    *   ✅ **Kỳ vọng:** Nhận lệnh thành công và nhảy xuống dòng chờ nhập `Số điện thoại`.

## 2. Test Format Thông Minh (Auto Title Case & Ignore Case)
**Mục tiêu:** Chứng minh `StringUtils` có thể tự tẩy rửa các trò đùa gõ Capslock loạn xạ và tìm kiếm chữ thường.

*   **Bước 1:** Đang ở luồng Thêm Nhân viên ở mục 1, ở dòng gõ *Số điện thoại*, nhập: `0901234567`.
*   **Bước 2:** Mật khẩu: `123`. Chức vụ: `Staff`. Lương cơ bản: `25000`.
*   **Bước 3 (Kiểm tra Title Case):** Nếu bạn đã lỡ gõ sai hoa thường ở bước 4 (hoặc có thể cố tình Gõ `dươNg quÁ`), bây giờ hãy ấn số `1` (Xem danh sách nhân viên).
    *   ✅ **Kỳ vọng:** Nhìn vào bảng cột Họ Tên của mã `NV099`. Dòng dữ liệu đã ép tự động thành chuẩn format danh từ riêng: **Dương Quá**. Tiếng Việt UTF-8 được chia cắt và viết hoa chữ cái đầu vô cùng mượt mà.
*   **Bước 4 (Kiểm tra Ignore Case):** Nhấn `0` quay lại. Nhấn `1` (Quản lý kho hàng). Nhấn `5` (Tìm kiếm sản phẩm).
*   **Bước 5:** Gõ vào từ khóa: `mì hảo hảo` (chữ thường toàn bộ).
    *   ✅ **Kỳ vọng:** Bảng danh sách văng ra đúng gói Hàng Hoá `Mì Hảo Hảo` (nếu có, hoặc hiển thị kết quả chứ không bị tịt vì sai hoa thường). Chức năng Search không phân biệt Case trên nền tiếng Việt!

## 3. Test Luồng Đăng Nhập Tài Khoản Bị Khóa
**Mục tiêu:** Chứng minh `AuthModel.cpp` xuất báo cáo đúng với Status (không in 2 dòng lặp).

*   **Bước 1:** Khởi động lại chương trình (hoặc Đăng xuất). Đăng nhập bằng tài khoản `admin01`.
*   **Bước 2:** Chọn `2` (Quản lý NV). Chọn `4` (Khóa tài khoản). Gõ khóa mã `NV099` (ông Dương Quá vừa làm). Máy báo thành công.
*   **Bước 3:** Bấm `0` liên tục để **Đăng xuất**.
*   **Bước 4:** Tại màn hình Đăng Nhập, nhập Mã NV: `NV099`, Mật khẩu: `123`.
    *   ✅ **Kỳ vọng:** Màn hình trả đúng **MỘT CÂU DUY NHẤT**: `=> [LỖI] Tài khoản này đã bị khóa bởi Quản lý!`. Tuyệt đối KHÔNG in thêm dòng "Sai tài khoản mật khẩu". Vòng lặp quay lại ép đăng nhập tiếp.

## 4. Test Mở Khóa Tài Khoản (Unlock)
**Mục tiêu:** Tính năng cứu lỗi nhân sự đỉnh cao. Hồi sinh 1 tài khoản đã bị Block.

*   **Bước 1:** Đăng nhập lại bằng `admin01`.
*   **Bước 2:** Chọn `2` (Quản lý NV). 
*   **Bước 3:** Nhấn số `1` để xem danh sách. Kiểm tra thấy `NV099` ở cột TÌNH TRẠNG đang hiện là `Bi khoa`.
*   **Bước 4:** Nhấn nút số `6` (Mở khóa tài khoản). Nhập mã: `NV099`.
    *   ✅ **Kỳ vọng:** Máy chủ báo: `Đã mở khóa tài khoản nhân viên NV099`.
*   **Bước 5:** Nhấn số `1` xem lại danh sách.
    *   ✅ **Kỳ vọng:** `NV099` ở cột Tình trạng sẽ nảy trở lại thành chữ `Dang lam`.
*   **Bước 6 (Bài thi khó nhất):** Đăng xuất ra. Vào lại bằng tài khoản `NV099`, pass `123`.
    *   ✅ **Kỳ vọng:** Vào lại Staff Menu mượt mà. Đăng nhập thành công!

## 5. UI Tiếng Việt & UX Bơm Test
**Mục tiêu:** Trải nghiệm giao diện.

*   **Thực thi:** Dạo quanh các màn hình `Quản lý kho`, `Thanh toán`, `Đăng ký Khách Hàng`. 
*   ✅ **Kỳ vọng:** Mọi dòng Menu, lời dặn dò, bảng Columns `MA SP`, `GHI CHU`... đều trích xuất ra giao diện chuẩn tiếng Việt UTF-8. Không còn kí tự không dấu.
