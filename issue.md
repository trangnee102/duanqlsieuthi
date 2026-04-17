# 📝 Bảng Theo Dõi Lỗi (Issue Tracker) Hệ Thống Quản Lý Siêu Thị

*Cập nhật gần nhất: 17/4/2026*

Tài liệu này tổng hợp danh sách các vấn đề (bug) và tính năng đã được đội ngũ phát triển xử lý, cũng như lộ trình phát triển trong tương lai. Nhằm giúp các thành viên cùng theo dõi tiến độ đồ án Hệ thống Quản lý.

---

## ✅ Phần 1: Những Vấn Đề Đã Được Giải Quyết (Done)

### 🔒 1. Phân quyền và Bảo mật (Security & Roles)
*   **Kiểm soát quyền vô hiệu hóa:** Ràng buộc quản trị viên (Admin) không được phép tự vô hiệu hóa tài khoản của chính mình.
*   **Hoàn thiện tính năng Soft Delete (Khóa tài khoản):** 
    *   Sửa lỗi logic trạng thái khi thay đổi trạng thái hoạt động (active: `1` thành `0`).
    *   Ngăn chặn đăng nhập vào hệ thống đối với các tài khoản đang trong trạng thái khóa.
    *   Tối ưu hóa bảng thông báo lỗi: Tránh chồng chéo thông báo "sai mật khẩu" khi hiển thị lỗi "tài khoản bị khóa".
*   **Khôi phục tài khoản:** Bổ sung tính năng thay đổi trạng thái và mở khóa quyền truy cập cho những tài khoản bị khóa trước đó.

### 🧮 2. Logic Trạng thái Kinh Doanh & Ràng Buộc Dữ Liệu
*   **Ràng buộc lợi nhuận và doanh thu:** Ràng buộc chặt chẽ logic giá trị: Giá bán luôn phải lớn hơn hoặc bằng giá nhập. Ngăn chặn các trường hợp nhập liệu số âm (`< 0`) cho Tiền lương dự kiến, Giá bán và Giá vốn.
*   **Kiểm tra tính hợp lệ dữ liệu đầu vào (Validation):** Triển khai khâu bắt lỗi input cho các trường số liệu, xử lý ngoại lệ (Exception Handling) khi người dùng nhập chuỗi vào trường kiểu số nguyên hoặc số thực.
*   **Ràng buộc khóa chính (Unique ID):** Cấm trùng lặp định danh cho mã nhân viên và mã hàng hóa.
*   **Quy trình quản lý danh mục (Category):** Ràng buộc luồng khởi tạo Danh mục. Nhân viên nghiệp vụ phải thông qua danh sách Danh mục cấp sẵn hoặc yêu cầu quyền Admin để tạo Ngành hàng mới.

### 🇻🇳 3. Giao diện và Tiêu chuẩn hóa UX/UI
*   **Hỗ trợ Codepage Tiếng Việt:** 
    *   Tái cấu trúc thiết lập Terminal để hỗ trợ hiển thị và nhập liệu Tiếng Việt (UTF-8).
    *   Dịch ngôn ngữ thông báo và toàn bộ User Interface (UI) sang Tiếng Việt.
*   **Tính năng Tìm kiếm (Ignore Case):** Triển khai thuật toán tìm kiếm không phân biệt chữ hoa, chữ thường và chuẩn hóa chuỗi đầu vào.
*   **Auto-Formatting Giao diện Terminal:** Điều chỉnh khoảng cách và căn lề cho việc đọc bảng dữ liệu hàng hóa/nhân sự trên giao diện dòng lệnh bằng việc thêm padding tự động.
*   **Trải nghiệm người dùng trong luồng ngoại lệ:** Thay vì văng về Menu chính hoặc thoát chương trình khi nhập sai mã Hóa Đơn/Sản Phẩm, hệ thống hiện giữ nguyên khung giao diện tương tác và yêu cầu nhập lại định dạng đúng.

### 🐛 4. Fix Bug Cụ Thể (Hotfixes)
*   **Lỗi phân giải quyền hạn người dùng do Case-Sensitive:** Đồng bộ hóa chữ hoa/thường cho các giá trị quyền (Role) trong lúc khởi tạo và kiểm tra.
*   **Kiểm tra ID (Case-Insensitive Identifier Error):** Xử lý luồng kiểm tra trùng mã ID, hiện tại `admin01` và `ADMIN01` sẽ được hệ thống từ chối do trùng lặp.
*   **Routings Điều hướng Sai Mục Tiêu:** Fix các điểm rẽ nhánh bị sai do lỗi điều kiện biên switch-case tại các Module Cấp 2.
*   **Lỗi Encoding khi tìm kiếm:** Áp dụng phương pháp Remove Accents để bóc tách từ khóa Tiếng Việt khi search (Ví dụ: "sua tuoi" có thể tìm ra giá trị "Sữa tươi").
*   **Bảo trì Mã Nguồn:** [Mới] Dọn dẹp mã nguồn, lược bỏ các chú thích và comment nháp/thừa (vibe tags) để nâng cao chất lượng báo cáo cho mã nguồn (Clean Code).

### 📦 5. Quản lý Lô hàng & Hạn sử dụng (Batch & Expiry Date)
*   **[Thêm Entity mới] `Batch` (Lô hàng):** Tạo thêm một Model mới để quản lý riêng từng lô hàng theo thời gian nhập kho. Tích hợp trực tiếp vào danh sách `Product`.
*   **Cập nhật cấu trúc Lưu trữ:** Mở rộng schema đọc ghi file `batches.csv` để lưu trữ song song với `products.csv`.
*   **Xử lý Logic Hạn Sử Dụng Song Song:** Đã áp dụng thuật toán trừ kho theo nguyên tắc **FIFO** (First In First Out), tự động xuất lô hàng cũ/gần hết hạn trước.
*   **Chi tiết lô hàng trên UI:** Nâng cấp menu hiển thị thông tin sản phẩm. Nay đã có thể liệt kê dạng cây (tree-view) các lô con kèm hạn sử dụng nằm trong một sản phẩm chính.
*   **Gán Hạn sử dụng bổ sung nhóm Thực phẩm tươi sống:** Tái cấu trúc bộ nhập liệu, tự động gán Date = Today cho các danh mục hàng siêu tốc độ ăn trong ngày.

### 📊 6. Cải tiến Hệ thống Báo cáo Tài chính (Financial Report)
*   **Đa dạng mốc thời gian:** Tích hợp bộ lọc doanh thu theo Tất cả / Hôm nay / 7 Ngày Qua / Tháng Này / Quý Này dựa trên dữ liệu giao dịch chuẩn xác.
*   **Biểu đồ Tương tác Console (Bar Chart):** Xây dựng trình vẽ biểu đồ cột trực quan trong Terminal khi xem báo cáo 7 ngày, giúp phân tích đỉnh doanh thu (Peak sales) dễ dàng.

---

## 🚧 Phần 2: Những Vấn Đề Còn Tồn Đọng (To Do)

### ✨ 2. Cải tiến Tính Năng Hệ Thống (Enhancements)
*   **Auto-Suggestion trong Màn Hình Nhập:** Hiển thị danh sách gợi ý khi gõ thông tin, giảm thao tác input.
*   **Chuẩn hoá Danh xưng UI:** Rà soát lại việc đặt tên các Module và tính năng cho chuyên nghiệp hơn.
*   **Kiểm thử System Client Module:** Review toàn diện và thêm Unit Tests cho hệ thống đăng ký và quy đổi thẻ thành viên Khách hàng.
