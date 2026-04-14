# Kế Hoạch Cấp Độ 4: Tinh Chỉnh Chuyên Sâu Cấu Trúc Hệ Thống

Những vấn đề bạn phát hiện đều là những nút thắt UX (Trải nghiệm người dùng) kinh điển nhất của C++ Console. Dưới đây là chiến lược bóc tách và giải quyết dứt điểm:

## 1. Quản Trị Ngành Hàng Độc Lập (Category Management)
- **Vấn đề:** Tránh việc nhân viên nhập liệu lung tung ra "Bánh kẹo", "Banh keo", "Đồ Ăn Vặt" thành ra 3 ngành hàng khác nhau. Phải thống nhất Danh sách Ngành hàng, và chỉ Admin mới có quyền thêm Ngành rễ.
- **Giải pháp:**
  - Mình sẽ tạo một Danh sách Ngành hàng (Lưu vào file `data/categories.csv` hoặc quản lý thông qua `InventoryModel`).
  - **Menu Admin:** Thêm vào chức năng `Quản lý Ngành hàng` (Thêm, Xóa, Xem danh sách).
  - **Nhập Hàng Mới:** Thay vì hỏi `Ngành hàng: <Nhập text>`, view sẽ hiển thị danh sách các ID Ngành Hàng Đã Duyệt cho user `Chọn`.

## 2. Vòng Lặp Phản Viện ID (Re-enter ID Loop)
- **Vấn đề:** Khi ID tồn tại, lệnh `break;` đẩy văng Admin ra Menu ngoài cùng, gây phiền hà phải chọn lại từ số 1.
- **Giải pháp:** 
  - Tại `InventoryController` và `EmployeeController`, luồng nhập ID sẽ được bọc trong một vòng lặp `while(true)`. 
  - Nếu trùng, máy báo Lỗi và lập tức quay lại ô hỏi ID để bạn gõ liền tay mã mới (`NV100`), cho phép gõ `CANCEL` để thủ công thoát ra.

## 3. Khắc Phục Lỗi Lệch Khung Bảng Giá (UTF-8 Table Alignment)
- **Vấn đề:** Hàm thư viện `std::setw()` của C++ chỉ đếm số Byte. Vì một chữ tiếng Việt có dấu tốn tới 2-3 Bytes (VD: chữ `Ễ`), nên `setw` ngỡ rằng từ đó rất dài và nuốt luôn khoảng trắng đệm, dẫn đến việc chữ bị hút dính vào nhau như hình Screenshot của bạn.
- **Giải pháp:**
  - Viết thuật toán độ đo chiều dài thật sự (True string length) cho Tiếng Việt trong `StringUtils`.
  - Viết hàm `padRight(string, width)` tự động bù đúng khoảng trống thực tế vào đuôi chữ.
  - Thay thế toàn bộ `std::setw` cồng kềnh trong hàm in Bảng `InventoryView` và `EmployeeView`. Bảng sẽ ngay lập tức tăm tắp 100% như Word!

## 4. Việt Hóa Menu Gốc `main.cpp`
- Diệt trừ tận gốc các dấu vết "Khong dau" cuối cùng ở màn hình ngoài cùng (Menu chính đăng nhập).

---

> [!IMPORTANT]
> **Quyết Định Kiến Trúc: Lưu trữ Ngành Hàng**
> Để đảm bảo tính bền vững, mình sẽ lưu danh sách Ngành hàng thành một File TXT/CSV độc lập `data/categories.csv` để Admin khởi động luồng phần mềm vẫn giữ nguyên danh sách. Bạn có đồng tình với phương pháp lưu trữ bền vững này không? Xác nhận để mình làm luôn nhé!
