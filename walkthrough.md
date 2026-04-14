# 🚀 Báo Cáo Sửa Lỗi Tương Tác & Logic Core Của Dự Án

Chúng ta vừa thực hiện một đợt nâng cấp và vá các lỗi logic nghiêm trọng nhất trong hệ thống quản lý Siêu thị. Sự thay đổi này tập trung vào tính tương tác mượt mà và sửa lỗi so khớp dữ liệu. Dưới đây là những tính năng đã được đại tu:

## 1. Hệ thống Tìm kiếm Tiếng Việt (Vietnamese Search)
Chúng ta đã tích hợp thành công `StringUtils::removeAccents` vào quy trình tìm kiếm sản phẩm. 
- **Trước đây:** Hệ thống đòi hỏi người dùng phải gõ chính xác 100% từng dấu câu của sản phẩm (ví dụ "Sữa tươi"). Nếu gõ "sua tuoi" sẽ không thể tìm thấy.
- **Hiện tại:** Hệ thống cho phép **Tìm kiếm không dấu**. Gõ "Sua tuoi TH", "sua tuoi" hay "SỮA TƯƠI" thì thuật toán đều tự động chuyển hoá và tìm ra đúng dòng sản phẩm phù hợp. Hệ thống rất "khoan dung" với lỗi gõ Telex của nhân sự!

## 2. Nâng cấp Bộ lọc Case-Insensitive (Chống phân biệt Hoa/Thường)
Mọi ID của nhân viên, sản phẩm và dữ liệu phân quyền (Role) hiện tại đều được so khớp ở chế độ **Case-Insensitive** thông qua `StringUtils::toLowerCase`.
- **Sửa Lỗi Phân Quyền:** Ngăn chặn triệt để tình trạng Admin cấp quyền `Admin` nhưng nhân sự đăng nhập lại bị ném thành `Purchasing` do sai lệch viết hoa/viết thường ở chuỗi gán quyền. 
- **Xử Lý Trùng Mã ID (Zero-Duplicate):** Bây giờ, nếu nhân sự mã `admin01` đã tồn tại, việc cố gắng thêm một nhân tài khoản tên `ADMIN01` sẽ bị hệ thống chặn lại ngay lập tức thay vì lưu đè/lưu trùng lặp vào cơ sở dữ liệu.

## 3. Khắc phục Lỗi Tràn Menu & Cấu Trúc Biên Dịch
- Sửa lỗi điều hướng tại Menu Ngành Hàng: Chương trình đã định tuyến chính xác phím tùy chọn, màn hình không còn buông rèm *"Vui lòng nhập từ 0 đến 11"* khi gọi các tính năng ở phần dưới của Menu.
- Fix xong lỗi biên dịch C++ (`'StringUtils' has not been declared`): Triển khai các khai báo Header Include chính xác cho `AuthModel.cpp`, khắc phục điểm nghẽn khiến source code không thể compile lúc build.
- Gom toàn bộ các file Markdown Test Cases cũ lại một nhà (`test_cases/`) để bộ khung dự án ngăn nắp hơn.

> [!TIP]
> **Hướng Thử Nghiệm:** Bạn có thể tự mình test tính năng bằng cách chạy chương trình, giả vờ gõ các mã hàng với chữ **THƯỜNG** thay vì chữ **HOA**, hoặc test hệ thống tìm kiếm sản phẩm bằng cách dùng kiểu gõ **không có dấu tiếng Việt**. Hệ thống sẽ không văng lỗi và trả về đúng dữ liệu chuẩn!
