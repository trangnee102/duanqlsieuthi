# 🧪 Kịch Bản Kiểm Thử (Test Cases) - Phiên Bản 4.0 

Bạn nhớ **Reload CMake Project** trước khi Build nhé! Ở bản này có 1 file mã nguồn mới tạo là `CategoryModel.cpp`. Dưới đây là cách thực thi ép xung hệ thống mới nhất:

## 1. Test Giao Diện Bảng Không Lệch Cột (UTF-8 True Length Pad)
**Mục tiêu:** Kiểm tra C++ in bảng tiếng Việt UTF-8 có còn dính chữ vào nhau không bằng tính năng siêu bù giờ `StringUtils::padRight`.

*   **Bước 1:** Đăng nhập `admin01`/`admin01`.
*   **Bước 2:** Bấm `2` (Quản lý nhân viên).
*   **Bước 3:** Nhấn số `1` (Xem danh sách nhân viên).
    *   ✅ **Kỳ vọng:** Bảng điều khiển in ra chữ `CHỨC VỤ` và `TÌNH TRẠNG` độc lập với nhau, có khoảng cách đúng chuẩn khoảng không 15 Textbox. Thẳng tắp giống hệt bảng Excel. Không còn hiện tượng các cột dính chùn vào nhau.
*   **Bước 4:** Thoát về Admin Menu, bấm `1` (Quản lý kho hàng). Bấm `1` (Xem danh sách sản phẩm).
    *   ✅ **Kỳ vọng:** Cột "MÃ SP", "TÊN SẢN PHẨM" cách xa nhau đúng chỉ tiêu.

## 2. Test Vòng Lặp Trùng Lặp ID (Re-Enter ID Loop)
**Mục tiêu:** Chứng minh Bug Push Out (văng luồng) do trùng mã đã bị chặn.

*   **Bước 1:** Đang ở Menu Quản lý Kho, bấm nút số `2` (Nhập hàng mới).
*   **Bước 2:** Nhập thử một mã sản phẩm đang tồn tại trong siêu thị. Ví dụ: `P01` hoặc `P02`.
    *   ✅ **Kỳ vọng:** Máy trả lời `[LỖI] Mã ID này đã tồn tại trong kho!` và **nhảy lại luôn câu hỏi** `Nhập Mã SP mới: `. Tương tự nếu bấm `CANCEL`, máy sẽ thoát nhẹ nhàng ra menu.
*   **Bước 3 (Thử tiếp với Nhân sự):** Về Menu Chính, vào "Quản lý nhân viên". Chọn `2` (Thêm nhân viên mới). Gõ mã ID là `admin01`.
    *   ✅ **Kỳ vọng:** Vẫn bị nhốt trong vòng lặp và bị chửi `[LỖI] Mã ID này đã tồn tại! Vui lòng chọn mã khác.`

## 3. Test Tính Năng Admin Category (Quản Lý Ngành Hàng Độc Lập)
**Mục tiêu:** Hệ thống đã cô lập hoàn toàn Ngành hàng, tránh rác dữ liệu.

*   **Bước 1:** Màn hình Menu Tổng bây giờ đã full Tiếng Việt (CHÀO MỪNG ĐẾN VỚI HỆ THỐNG SIÊU THỊ...). Chọn `1` (Quản lý kho).
*   **Bước 2:** Bạn sẽ thấy lệnh số **12. QUẢN LÝ NGÀNH HÀNG**. Hãy nhập số `12`!
*   **Bước 3:** Chọn số `1` (Xem danh sách).
    *   ✅ **Kỳ vọng:** In ra 3 Ngành mặc định: 1. Thuc pham, 2. Do gia dung, 3. Dien tu.
*   **Bước 4:** Bấm số `2` (Thêm ngành hàng). Nhập vào từ khó: `bánh kẹo`.
    *   ✅ **Kỳ vọng:** Hàm TitleCase tự chèn vào file và thông báo thành công. Khi bấm số `1`, màn hình in ra thêm ngành số 4 là `Bánh Kẹo`.
*   **Bước 5:** Thoát ra Menu bằng số `0`.

## 4. Test Ràng Buộc Category Lúc Nhập Hàng Mới
**Mục tiêu:** Không còn hỏi "Ngành hàng là gì (Gõ chữ)" dễ gây rác nữa.

*   **Bước 1:** Đang ở Menu Kho, bấm nút số `2` (Nhập hàng mới).
*   **Bước 2:** Nhập mã SP mới chưa tồn tại `SP999`. Tên SP: `Gói bim bim`.
*   **Bước 3:** Ngay lập tức màn hình in ra `Danh sách Ngành Hàng khả dụng: 1. Thuc pham... 4. Bánh Kẹo`. Và yêu cầu bạn `Chọn STT ngành hàng:`.
    *   ✅ **Kỳ vọng:** Bạn nhấn số `4`. Màn hình chốt đơn: `=> Ngành hàng: Bánh Kẹo`.
*   **Bước 4:** Nhập các thông tin còn lại và check xem nó đã vô CSDL chưa!
