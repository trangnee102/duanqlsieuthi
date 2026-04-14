# 🛒 Hệ Thống Quản Lý Siêu Thị (Supermarket Management System)

Một ứng dụng quản lý siêu thị toàn diện được viết bằng **C++** chạy trên môi trường Console, áp dụng chặt chẽ kiến trúc **MVC (Model - View - Controller)** và các nguyên lý **Lập trình hướng đối tượng (OOP)**.

## 🌟 Tính năng Nổi bật

### 🔐 Phân quyền & Quản lý Người dùng
*   **Admin:** Toàn quyền quản lý kho hàng, nhân sự, danh mục ngành hàng và báo cáo doanh thu.
*   **Purchasing (Nhân viên Nhập hàng):** Quyền thao tác kho cơ bản, cập nhật số lượng, sắp xếp, lọc hàng hết hạn.
*   **Staff (Nhân viên Bán hàng/Thu ngân):** Bán hàng (POS), xem hàng trên kệ (chỉ thấy giá bán niêm yết), đăng ký khách hàng.
*   **Quản lý Trạng thái:** Có tính năng Khóa (Cho nghỉ việc) hệ thống thông minh, và Hồi sinh (Mở khóa) tài khoản khi cần thiết.

### 📦 Quản lý Kho hàng (Inventory)
*   **CRUD Sản phẩm:** Thêm mới, cập nhật (giá nhập, giá bán, số lượng), xoá mềm (kèm ghi log lưu lý do tiêu hủy).
*   **Danh Mục Ngành Hàng (Category):** Xây dựng CSDL ngành hàng độc lập. Khóa cứng quy trình nhập liệu: Nhân viên bắt buộc phải chọn ngành hàng từ danh sách định trước do Admin quản lý, khử 100% rác dữ liệu.
*   **Vòng lặp Bảo vệ UX (Re-enter Loop):** Quét trùng lặp Mã ID ngay từ câu lệnh đầu tiên, neo vòng lặp nhập lại để chống hiện tượng văng (Push out) ứng dụng và chặn thao tác "bán lỗ" (Giá bán bé hơn Giá gốc).
*   **Sắp xếp, Lọc & Hàng Cận Date:** Sắp xếp theo mã/ngành; tự động giảm giá đồ cận hạn (VD: Cận 3 ngày giảm 50%); có hệ sinh thái lọc đồ `tuoi` riêng biệt.

### 💳 Bán hàng (Point of Sale - POS)
*   **Giỏ hàng:** Nhập mã SP, kiểm tra tồn kho, áp dụng logic giá sau chiết khấu. 
*   **In hoá đơn (Receipt):** Xuất hoá đơn chuẩn format gồm tiêu đề, thông tin nhân viên thu ngân, danh sách món hàng, tổng tiền, điểm tích lũy.
*   **Lưu vết giao dịch:** Ghi nhận toàn bộ thông tin bán hàng (doanh thu, giá vốn tại thời điểm bán) vào `sales_log.csv` để thống kê lợi nhuận xác thực thay vì ước tính.

### 👥 Quản lý Khách hàng & Tích điểm
*   **Đăng ký thành viên:** Lưu danh bạ khách hàng.
*   **Tích điểm tự động:** Mỗi đơn hàng được quy đổi điểm vào hệ thống của khách hàng.

### 📊 Báo cáo Thống Kê (Chỉ dành cho Admin)
*   Quản trị viên có tính năng đọc lịch sử bán hàng (`sales_log.csv`) để tính toán **Tổng Doanh Thu**, **Tổng Lợi Nhuận (Profit)** dựa vào chênh lệch giữa giá bán thực tế và giá nhập.

### 🌐 Đột Phá Xử Lý Tiếng Việt (UTF-8) & Console UI
*   **Native UTF-8 Input/Output:** Ép hook `CP_UTF8` để tương tác 100% Tiếng Việt có dấu ngay trên màn hình Terminal kinh điển của C++.
*   **AI Formatting (`StringUtils`):** 
    *   Thuật toán *Title Case* tự động bắt và viết hoa các danh từ riêng (Ví dụ tự chỉnh `ngUYỄn vĂN A` thành `Nguyễn Văn A`).
    *   Tra cứu thông minh *Ignore Case* (Bỏ qua hoa thường) khi tìm kiếm sản phẩm.
*   **Căn lề tuyệt đối (True Length Padding):** Thay thế lệnh `std::setw` truyền thống bị lỗi với chuỗi đa byte bằng giải pháp đếm Byte `utf8_length` tích hợp bù khoảng trắng `padRight`. Cột bảng (Báo cáo, Kho, Nhân viên) luôn tăm tắp 100%!

---

## 🏗️ Cấu trúc Thư mục

Dự án tổ chức mã nguồn rõ ràng để phân tách trách nhiệm (Separation of Concerns).

```text
├── CMakeLists.txt        # Tệp cấu hình CMake
├── README.md             # Tài liệu này
├── include/              # Thư mục chứa Headers (*.h) 
├── src/                  # Thư mục Source Files (*.cpp)
│   ├── main.cpp          # Điểm khởi đầu của ứng dụng
│   ├── controllers/      # (C) Điều phối Logic Model và Giao diện View (InventoryController...)
│   ├── models/           # (M) Khối quản lý Dữ liệu 
│   │   ├── entities/     # Thực thể dữ liệu: Product, Employee, Customer, Person
│   │   └── logic/        # Các nghiệp vụ: AuthModel, InventoryModel, CustomerModel, CategoryModel
│   ├── views/            # (V) Trình bày Output Console và thu nhận Input
│   └── utils/            # Thư viện tĩnh: DateUtils, FileHandler, StringUtils (Xử lý Tiếng Việt)
└── data/                 # Thư mục CSDL dạng Flat file (products.csv, categories.csv, sales_log.csv)
```

---

## 🧑‍💻 Nguyên tắc Lập Trình Đặc Trưng
1.  **Đóng gói (Encapsulation):** Toàn bộ Field của Entities (Mã, Tên, Giá, SL) được ẩn (`private`), mọi truy cập ngoài được vận hành thông qua các phương thức Get/Set.
2.  **Kế thừa (Inheritance):** Các lớp tác nhân cụ thể như `Employee` và `Customer` vận dụng thiết kế giảm trùng lặp bằng cách kế thừa thẳng từ lớp `Person`.
3.  **Đa hình & Trừu tượng (Polymorphism & Abstraction):** Áp dụng triệt để Dependency Inversion và Interface-based design. Sử dụng đa hình qua các hàm `virtual` cho phép khả năng mở rộng (Scalability) của dự án sau này. 
4.  **Clean Code & Chuẩn hóa:** Module hoá triệt để, phân quyền theo MVC rõ rệt, có các thư viện Utils độc lập dùng chung cho Thao tác chuỗi, File I/O và Date-Time.

---

## ⚙️ Hướng dẫn Cài đặt & Build

### Yêu cầu hệ thống:
*   Trình biên dịch C++ hỗ trợ **C++20** (GCC, Clang, hoặc MSVC).
*   **CMake** bản từ 4.1 trở lên.

### Các bước Build bằng CMake:
Mở Terminal / Command Prompt trong thư mục gốc của dự án (`duanqlsieuthi`), chạy liên tiếp các lệnh sau:

```bash
# 1. Tạo thư mục để chứa các tệp build sinh ra
mkdir build
cd build

# 2. Sinh Makefile / Project configuration
cmake ..

# 3. Tiến hành Compile sinh file thực thi
cmake --build .
# (Hoặc gõ `make` nếu đang dùng Make trên MacOS/Linux)
```

### Chạy ứng dụng:
*   Chạy file thực thi vừa được sinh ra trong cấu trúc thư mục của tệp Build. 
*   **Lưu ý:** Vì phần IO đang cấu hình sử dụng đường dẫn file tương đối `../data/...`, bạn cần thực thi ứng dụng ở thư mục mà nó map đúng vào `data/` trong cấu trúc.

---
*Chúc bạn trải nghiệm và xây dựng thành công! Cần khởi tạo tài khoản Admin trong tệp data để đăng nhập trong lần đầu.*
