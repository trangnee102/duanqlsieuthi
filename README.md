# 🛒 Hệ Thống Quản Lý Siêu Thị (Supermarket Management System)

Một ứng dụng quản lý siêu thị toàn diện được viết bằng **C++** chạy trên môi trường Console, áp dụng chặt chẽ kiến trúc **MVC (Model - View - Controller)** và các nguyên lý **Lập trình hướng đối tượng (OOP)**.

## 🌟 Tính năng Nổi bật

### 🔐 Phân quyền & Quản lý Người dùng
*   **Admin:** Toàn quyền quản lý kho hàng, nhân sự và báo cáo doanh thu.
*   **Purchasing (Nhân viên Nhập hàng):** Quyền thao tác kho cơ bản, cập nhật số lượng, sắp xếp, lọc hàng hết hạn.
*   **Staff (Nhân viên Bán hàng/Thu ngân):** Bán hàng (POS), xem hàng trên kệ (chỉ thấy giá bán niêm yết), đăng ký khách hàng.

### 📦 Quản lý Kho hàng (Inventory)
*   **CRUD Sản phẩm:** Thêm mới, cập nhật (giá nhập, giá bán, số lượng), xoá mềm (kèm ghi log lưu lý do tiêu hủy).
*   **Sắp xếp & Lọc:** Sắp xếp theo ngành hàng và mã SP; tìm kiếm nhanh.
*   **Xử lý hàng cận Date/Hết hạn:** Tự động lọc sản phẩm hết hạn.
*   **Cảnh báo thời gian thực:** Lọc các sản phẩm tươi sống dựa trên hệ thống gán mác `tuoi` để nhắc nhở nhân viên kiểm tra hàng ngày.
*   **Khuyến mãi thông minh:** Tự động chiết khấu giá nếu hạn sử dụng còn dưới các mốc cận date (VD: Cận hạn 3 ngày giảm 50%, 7 ngày giảm 20%).

### 💳 Bán hàng (Point of Sale - POS)
*   **Giỏ hàng:** Nhập mã SP, kiểm tra tồn kho, áp dụng logic giá sau chiết khấu. 
*   **In hoá đơn (Receipt):** Xuất hoá đơn chuẩn format gồm tiêu đề, thông tin nhân viên thu ngân, danh sách món hàng, tổng tiền, điểm tích lũy.
*   **Lưu vết giao dịch:** Ghi nhận toàn bộ thông tin bán hàng (doanh thu, giá vốn tại thời điểm bán) vào `sales_log.csv` để thống kê lợi nhuận xác thực thay vì ước tính.

### 👥 Quản lý Khách hàng & Tích điểm
*   **Đăng ký thành viên:** Lưu danh bạ khách hàng.
*   **Tích điểm tự động:** Mỗi đơn hàng được quy đổi điểm vào hệ thống của khách hàng.

### 📊 Báo cáo Thống Kê (Chỉ dành cho Admin)
*   Quản trị viên có tính năng đọc lịch sử bán hàng (`sales_log.csv`) để tính toán **Tổng Doanh Thu**, **Tổng Lợi Nhuận (Profit)** dựa vào chênh lệch giữa giá bán thực tế và giá nhập.

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
│   │   ├── entities/     # Thực thể dữ liệu: Product, Employee, Customer, Person...
│   │   └── logic/        # Các nghiệp vụ như: AuthModel, InventoryModel, CustomerModel
│   ├── views/            # (V) Trình bày Output Console và thu nhận Input (InventoryView...)
│   └── utils/            # Thư viện tĩnh dùng chung (DateUtils, FileHandler để đọc/ghi file CSV)
└── data/                 # Thư mục CSDL dạng Flat file (chứa các tệp .csv giả lập Database)
```

---

## 🧑‍💻 Nguyên tắc Lập Trình Đặc Trưng
1.  **Đóng gói (Encapsulation):** Toàn bộ Field của Entities (Mã, Tên, Giá, SL) được ẩn (`private`), mọi truy cập ngoài được vận hành thông qua các phương thức Get/Set.
2.  **Kế thừa (Inheritance):** Các lớp tác nhân cụ thể như `Employee` và `Customer` vận dụng thiết kế giảm trùng lặp bằng cách kế thừa thẳng từ lớp `Person`.
3.  **Clean Code & Chuẩn hóa:** Module hoá triệt để, có các thư viện Utils riêng cho Thao tác chuỗi, File và Date-Time.

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
