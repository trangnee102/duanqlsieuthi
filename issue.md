# 📝 Bảng Theo Dõi Lỗi (Issue Tracker) Của Dự Án

*Cập nhật gần nhất: 18h50 ngày 14/4/2026*

Dưới đây là danh sách các lỗi (bug) và tính năng đã được team xử lý, cùng với những việc còn đang dang dở. Bảng này giúp các bạn (kể cả các bạn sinh viên năm nhất mới học C++) có thể dễ dàng nắm bắt tình hình dự án!

---

## ✅ Phần 1: Những Vấn Đề Đã Được Giải Quyết (Done)

### 🔒 1. Phân quyền và Bảo mật (Security & Roles)
*   **Không tự "cắt chém" chính mình:** Cấm Admin tự khoá tài khoản của bản thân.
*   **Sửa lỗi khoá tài khoản (Soft Delete):** 
    *   Trước đây tính năng khoá tài khoản bị lỗi logic (không đổi được trạng thái từ `1` thành `0`). Đã fix xong!
    *   Trước đây tài khoản bị khoá vẫn có thể đăng nhập được. Đã chặn lại!
    *   Trước đây khi mở tài khoản bị khóa, nó báo "tài khoản bị khóa" nhưng lại xì ra thêm câu "sai tài khoản/mật khẩu". Đã dọn dẹp sạch sẽ logic hiển thị thông báo.
*   **Hồi sinh tài khoản:** Đã thêm tính năng mở khoá cho các tài khoản đang bị khoá.

### 🧮 2. Logic Kinh Doanh & Ràng Buộc Dữ Liệu (Business Logic)
*   **Chống lạm phát và phá sản:** Giá bán ra KHÔNG ĐƯỢC rẻ hơn giá nhập. Các loại số tiền như Giá bán, Giá nhập hay Tiền lương đều không được phép để số ÂM (`< 0`).
*   **Kiểm tra tính hợp lệ của dữ liệu (Validation):** Siết chặt việc nhập dữ liệu. Chỗ nào yêu cầu nhập "Số" thì cấm nhập "Chữ" và ngược lại (tránh crash chương trình).
*   **Quản lý ID độc nhất:** Chặn hoàn toàn việc nhập trùng mã ID (cả nhân viên lẫn hàng hóa).
*   **Quản lý Ngành hàng (Category):** Đã phân quyền chặt chẽ các ngành hàng kinh doanh. Nhân viên không được tự tiện đẻ ra ngành hàng mới khi đang nhập hàng. Muốn có ngành mới phải xin Admin gõ vào mục riêng.

### 🇻🇳 3. Giao diện và Trải nghiệm (UI/UX & Tiếng Việt)
*   **Hỗ trợ Tiếng Việt 100%:** 
    *   Đã cài mã trang (codepage) để Terminal gõ được tiếng Việt có dấu.
    *   Sửa lỗi Terminal và code backend lúc đầu "kỳ thị" tiếng Việt (Bây giờ thì menu, thông báo hay dữ liệu đều đã full Tiếng Việt).
*   **Tìm kiếm thông minh (Ignore Case):** Tìm kiếm không phân biệt chữ Hoa/chữ thường. Hệ thống sẽ tự động gò dòng chữ người dùng nhập về chuẩn format.
*   **Căn lề cho Terminal:** Khắc phục lỗi in danh sách nhân viên/hàng hóa bị lệch cột, dính chữ vào nhau. Giờ bảng đã ngay ngắn, thẳng tắp!
*   **UX - Trải nghiệm người dùng:** Fix lỗi: Trước đây người dùng gõ nhầm Mã Hàng Hóa (ID), chương trình thẳng tay đuổi người dùng văng ra tận Menu chính. Giờ thì hiền hơn, cho phép gõ lại ID khác ngay tại chỗ.

### 🐛 4. Lỗi Logic Đã Fix Khẩn Cấp (Đã Xử Lý)
*   **Lỗi Phân quyền do Viết hoa/thường:** Admin tạo tài khoản gán quyền `Admin` nhưng lúc đăng nhập lại hóa thành `Purchasing`. (Đã xử lý Role không phân biệt hoa thường).
*   **Lỗi Trùng ID:** Thêm nhân viên mang mã `admin01` thì hệ thống không nhận ra là nó bị trùng với mã `ADMIN01` đã có trong dữ liệu. (Đã xử lý ID không phân biệt hoa thường).
*   **Lỗi nhầm Menu Ngành Hàng:** Gõ phím `12` để vào trang "Quản lý ngành hàng" thì hệ thống khóc bù lu bù loa. (Đã cập nhật phạm vi menu và điều hướng chính xác).
*   **Tìm kiếm Tiếng Việt:** Gõ chữ không dấu nhưng vẫn có thể tìm ra được sản phẩm tên có dấu (Ví dụ: Gõ "Sua tuoi" tìm được "Sữa tươi"). (Đã được áp dụng hàm xoá dấu).

---

## 🚧 Phần 2: Những Vấn Đề Còn Tồn Đọng (To Do)

### 📦 1. Quản lý Lô hàng & Hạn sử dụng (Batch & Expiry Date)
*   **[Thêm Entity mới] `Batch` (Lô hàng):** Tạo thêm một Model mới để quản lý riêng từng lô hàng (vì nhập hàng theo đợt).
*   **Cập nhật Database:** Sửa lại số lượng cột và cấu trúc file lưu trữ để chừa chỗ cho `Batch`.
*   **Xử lý trùng lặp sản phẩm nhưng khác Date:** Bài toán đau đầu: Cùng một mã sữa, nhưng lô tháng 1 khác hạn sử dụng với lô tháng 2. Cần tìm giải pháp để quản lý được hạn sử dụng cho từng lô.
*   **Gán Hạn sử dụng cho nhóm Rau, củ, quả:** Hiện tại nhóm rau cỏ đang không có hệ thống đếm ngược hạn sử dụng.


### ✨ 2. Cải tiến Tính Năng (Enhancements)
*   **Auto-Suggestion:** In ra các gợi ý/ví dụ để mớm lời cho người dùng mỗi khi họ cắm mặt xuống bàn phím ở các bước nhập liệu.
*   **Đổi tên mục Menu:** Sửa lại tên cái Menu tính tiền (mục số 9) cho kêu hơn/phù hợp hơn.
*   **Review hệ thống Khách hàng:** Check lại hoạt động của tính năng Đăng ký khách hàng xem có lỗi gì không.
*   **Giao diện Báo cáo Tài Chính Mới:** Romboy lại bộ hiển thị thống kê. Có thể in được báo cáo terminal theo tuỳ chọn mốc thời gian lớn: Ngày / Tuần / Tháng / Quý / Năm.
