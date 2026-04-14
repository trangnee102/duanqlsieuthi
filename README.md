# 🛒 Hệ Thống Quản Lý Siêu Thị (Supermarket Management System)

Một ứng dụng quản lý siêu thị xuất sắc hoạt động trực tiếp trên nền tảng **C++ Console (Terminal)**, được kiến trúc hóa bằng mô hình **MVC (Model-View-Controller)** và tuân thủ các nguyên lý **OOP (Lập trình Hướng đối tượng)** khắt khe. 

Dự án nhấn mạnh vào tính năng an toàn dữ liệu, chống lỗi crash từ phía người dùng, và trải nghiệm mượt mà với **Tiếng Việt 100%**.

---

## 🌟 ĐỘT PHÁ & TÍNH NĂNG NỔI BẬT

### 1. Bức tường Thành "Chống Sập" Hệ Thống (Exception Binding)
- Không bao giờ crash chương trình cho dù người gõ vô tình (hoặc cố ý) nhập text (chữ) vào trường yêu cầu số. Hệ thống tiện ích `InputUtils` sẽ làm sạch bộ nhớ tự động và mềm mỏng bắt ép nhập lại.
- **Escape Hatch (Lối thoát khẩn cấp):** Tại *bất kỳ* bước nhập liệu nào, rủi chừng người dùng nghĩ lại, bạn chỉ việc gõ gõ `-1` (với số) hoặc `CANCEL` (với chữ) để huỷ lệnh đột xuất và lùi ngay về Menu trước đó mà không sinh rác dữ liệu Object rỗng!

### 2. Tiếng Việt & Hiển Thị Bảng Siêu Chuẩn (`StringUtils`)
- Chế độ hook mã hoá Unicode `CP_UTF8`, Terminal không còn xuất hiện lỗi font chữ kỳ dị. Tiếng Việt có dấu hiển thị hoàn hảo.
- **AI Formatting (`StringUtils`):** 
    - Thuật toán *Title Case* tự động tìm và viết hoa các danh từ riêng (Ví dụ tự chỉnh `ngUYỄn vĂN A` thành `Nguyễn Văn A`).
- Hệ quy chiếu đếm số ký tự Byte thực `utf8_length` và thuật toán căn lề `padRight` giúp các File báo cáo và Danh sách luôn thẳng tắp như trên giao diện Web Frontend, không còn hiện tượng lệch cột.

### 3. Tìm Khoản Diễu Sinh & Matcher Siêu Nhạy (Smart Search)
- **Zero-Duplicate ID:** Ngăn chặn tuyệt đối tình trạng hai tài khoản hoặc mặt hàng có chung một ID. Ràng buộc bảo mật ngay từ lúc bấm enter (Hệ thống thông minh check chéo không phân biệt chữ hoa/thường: `A01` và `a01` tính là trùng lặp).
- **Tìm kiếm Tiếng Việt Không Dấu:** Quên đi việc phải gõ đúng từng cái dấu huyền/sắc. Bạn muốn tìm "Sữa Tươi"? Cứ việc gõ thẳng "sua tuoi", hệ thống tự động loại bỏ Accent, tra lại file CSV đồ sộ và xuất ra kết quả tương ứng.

---

## 🎯 CÁC MODULE CHÍNH TRONG HỆ THỐNG

### 🔐 Phân Quyền Quản Trị Hệ Thống (RBAC)
Hệ thống cấp 3 quyền rạch ròi, với thuật toán đọc vai trò (Role) Case-Insensitive không bắt bẻ viết hoa:
1. **Admin (Quản trị viên):** Quyền năng bao quát tối thượng. Khóa/Mở khoá tài khoản nhân viên (Trừ chính mình). Theo dõi doanh thu lợi nhuận. Chạm vào mọi Menu.
2. **Purchasing (Quản lý Kho/Nhập hàng):** Uỷ quyền làm việc độc lập tại kho. Cập nhật tồn kho, sắp xếp date, theo dõi hàng hoá, nhưng không được phép dính líu đến máy thu ngân.
3. **Staff (Hỗ trợ bán hàng):** Thu ngân túc trực tại quầy POS. Cầm quyền lập bill, tính sổ, thanh toán và in hóa đơn cho khách.

### 📦 Quản lý Kho Hàng (Inventory)
- **Thực thi An toàn Tài chính:** Chặn không cho phép điền giá Âm (`< 0`) và không cho phép Set Giá bán bé hơn `<` Giá nhập gốc. (Tránh lỗ vốn vì ngáo giá).
- **Thư viện Ngành Hàng Độc Lập:** Admin được cấp quyền tạo Ngành hàng (Category). Nhân sự kho lúc quy nạp sản phẩm chỉ được phép lựa chọn các ngành đã có sẵn trong cơ sở dữ liệu để chống chế rác dữ liệu.

### 💰 Bán Hàng POS & Tracking Lợi Nhuận
- Đóng túi giỏ hàng (Cart) và tự trừ kho số lượng tương ứng sau thanh toán.
- Lưu log lại `sales_log.csv` để phục vụ công tác tra cứu Báo Cáo Tài Chính. Mức lợi nhuận (Profit) được tính từ hiệu số của Giá Bán trừ cho Giá Gốc thời kỳ.

### 👥 Theo Dõi Khách Hàng Thân Thiết & Chấm Công
- Hệ thống CRM tính điểm thưởng sau mỗi lần mua. Chấm công theo sát các giờ gác ca của nhân viên để tổng tính lương lúc xuất file báo cáo cuối tháng.

---

## 🛠 HƯỚNG DẪN CÀI ĐẶT & CHẠY DỰ ÁN DÀNH CHO END-USER

### 1. Hệ Yêu Cầu Thiết Bị
- Ngôn ngữ: `C++ 20`. 
- Máy tính chạy **OS Windows**.
- **LƯU Ý TRÍ MẠNG**: Thư mục cài đặt code để chạy phần mềm **Tuyệt đối KHÔNG chứa chữ Tiếng Việt có dấu hoặc khoảng trắng**. 
Nếu bỏ trong thư mục sai (vd: `Dự án C++`), CMake/CLion sẽ quăng lỗi `'AuthModel.h' file not found`.
👉 *Đường dẫn dự án Chuẩn: `C:\Users\Admin\CLionProjects\duanqlsieuthi`.*

### 2. Khởi tạo Biên dịch (Build)
Nếu thao tác trên Command Line (Bật CMD tại thư mục gốc dự án):
```bash
# Tao folder build va compile
mkdir build
cd build
cmake ..
cmake --build .
# Thực thi App file vừa sinh ra
```
Nếu bạn dùng Jetbrains CLion, mọi thứ tự động nhưng nếu thay đổi đường dẫn hãy bấm `Reload CMake Project`.

---

## 🏃‍♀️ HƯỚNG DẪN SỬ DỤNG (HOW TO PLAY)

### Bước 1: Log in
Hệ thống có nick mặc định cài sẵn trong Database `data/6_admin/employees.csv`.
> **Tài Khoản Admin cấp cao:** `admin01`
> **Mật khẩu:** `123456`

*(Lưu ý: Bạn nhập ID chữ hoa hay chữ thường thì ứng dụng đều cho phép qua).*

### Bước 2: Một số Mẹo (Cheat Sheet)
1. **Thiết lập Nhập Kho Cấp Bách:** Mở Menu ngành hàng -> tạo nhanh một Ngành hàng trước rồi hẵng nhảy sang Thêm Mới Sản phẩm.
2. **Quay Xe (Hủy Nhập Liệu):** Giữa tiến trình đang lập 1 form thông tin rất cực (ví dụ thêm 5 field), lúc ở field nhập Giá Tiền bạn muốn huỷ bỏ tất cả. Chỉ việc bấm phím `-1` rồi ấn Enter là máy tính thoát cái xoẹt ra Menu!
3. **Tìm kiếm Tiếng Việt:** Chỉ cần gõ *gao st25*, thuật toán quét không dấu sẽ móc ra món mớ hàng *Gạo ST25* cho bạn!
 
Chúc bạn có cho mình những trải nghiệm 5 Sao với dự án hệ thống vận hành đồ sộ này! Hẹn gặp lại.
