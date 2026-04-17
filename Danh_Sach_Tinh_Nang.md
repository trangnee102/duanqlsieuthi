# DANH SÁCH TÍNH NĂNG CHI TIẾT CỦA HỆ THỐNG
**Dự án:** Phần mềm Quản Lý Siêu Thị Thực Phẩm bằng C++ (Terminal POS Application)
---
## 1. Hệ thống Xác thực & Phân quyền (Authentication & Authorization)
Hệ thống được thiết kế bảo mật chặt chẽ bằng cơ chế định danh File I/O và phân rã quyền truy cập (Role-based access control) theo 3 cấp bậc:
* **Quyền Admin (Quản lý cấp cao):** Có toàn quyền truy cập 100% ứng dụng bao gồm Xoá/Thanh lý sản phẩm, in báo cáo tài chính tổng hợp.
* **Quyền Purchasing (Nhân sự Kho/Thu mua):** Chỉ có chức năng làm việc với Inventory. Có quyền Nhập lô hàng mới, theo dõi cảnh báo Tồn kho và chỉnh sửa Giá bán/Giá vốn. Không được quyền thanh toán (tránh gian lận dòng tiền).
* **Quyền Staff (Thu ngân/Bán hàng):** Quyền thấp nhất, chỉ được mở tính năng Giao dịch POS (Bán hàng), đăng ký thẻ Khách hàng và xem danh sách hàng hoá (không hiện Giá vốn).

## 2. Quản Lý Kho & Thuật Toán Lô Hàng (Inventory & Batch Management)
Điểm sáng của kiến trúc dự án nằm ở thuật toán tách biệt Lô Hàng thay vì gộp chung Sản phẩm:
* **Kiến trúc Tree-View Lô hàng:** Cho phép một Mã Sản phẩm (SKU) sở hữu vô hạn các Lô hàng (Batches) phụ thuộc vào quá trình nhập kho nhiều lần. Khi hiển thị, màn hình sẽ phân tách cây thư mục (VD: Dưới `Sữa Vinamilk` sẽ rẽ nhánh hiển thị `[Lô 1] HSD: 12/05`, `[Lô 2] HSD: 20/06`).
* **Thuật toán Trừ Khấu Hao FIFO (First In - First Out):** Khi khách hàng mua một món hàng, Hệ thống sẽ liên tục quét các Lô Hàng của Sản phẩm đó để tự động bào mòn số lượng của Lô cũ nhất/gần hết hạn nhất. Nếu Lô A hết sẽ nhảy sang trừ tiếp Lô B mà không cần nhân sự can thiệp.
* **Gán hạn dùng thông minh (Daily Fresh):** Tự động phát hiện nếu người quản lý nhập nhóm ngành *Thực phẩm tươi sống / Đồ ăn trong ngày*, hệ thống sẽ ngầm gán Hạn sử dụng của chính lô hàng đó kết thúc ngay vào 24h đêm hôm đó.

## 3. Quản Lý Dòng Tiền & Điểm Bán Hàng (POS & Financials)
* **Giao dịch POS tích hợp xử lý ngoại lệ:** Chặn đứng các rủi ro mua vượt quá số lượng tồn kho. Hoá đơn sẽ tổng hợp từng Item kèm theo độ dài chữ được quy chuẩn bằng hàm Căn Lề `padRight()`, chống vỡ form trên màn hình đen.
* **Khuyến mãi Tự Động dựa theo Time-to-Live:** Khi quẹt hàng, hệ thống âm thầm so sánh Date hiện tại của hệ thống với Hạn sử dụng của sản phẩm.
  * Hàng ráo khô sắp hết hạn (Cận Date): Tự trừ 20% trên màn hình.
  * Hàng tươi sống sau 19h00: Tự trừ 50% dọn kho trong ngày. Quá 22h00: Cấm bán tuyệt đối để bảo vệ an toàn vệ sinh.
* **Báo Cáo Tài Chính Cấp Doanh Nghiệp (Multi-timerange Report):** Module in báo cáo siêu mạnh mẽ, lọc doanh thu theo Tất Cả, Hôm Nay, 7 Ngày Qua, Tháng Này, và Quý Này.
* **Dynamic ASCII Bar Chart:** Một tính năng mang tính "Show off - Trình diễn" kỹ năng lập trình cực cao. Khi in Báo cáo 7 ngày, hệ thống sẽ chạy vòng lặp tìm **Đỉnh Doanh Thu**, sau đó dùng toán học để scale và tự vẽ ra một Biểu đồ Cột (Bar Chart) tuỳ biến chiều dài bằng các dải hashtag `#` ngay trên giao diện Console. 

## 4. Quản Lý Khách Hàng Thân Thiết (CRM & Membership)
* **Định danh Auto-ID độc lập:** Khi đăng ký Thành viên, thu ngân chỉ cần nhập SĐT. Nếu SĐT mâu thuẫn (trùng), hệ thống sẽ chặn lại. Nếu hợp lệ, hệ thống tự động bốc mã `KHxx` cao nhất hiện tại để sinh ra thẻ mới.
* **Tích luỹ Điểm (Loyalty Points) Auto-Discount:** Điểm của Khách hàng = `Doanh Thu / 10000`. Cứ mỗi lần đọc SĐT ở các hoá đơn sau, điểm sẽ tự động được kiểm duyệt để nâng hạng (Bạc, Vàng, Kim cương) và móc thẳng vào hoá đơn trừ đi vài % tổng bill trước khi khách quẹt thẻ trả tiền.

## 5. Trải Nghiệm Người Dùng & Quản Trị Lỗi (UX & Exception Catching)
* **Bộ chặn Exception toàn diện:** Mọi Input số (int, double) hoặc ký tự đều được bọc bởi vòng lặp an toàn `InputUtils`. Máy sẽ miễn nhiễm với mọi trò "Phá game" (Người dùng gõ chữ cái vào ô điền Tiền, hoặc gõ độ dài âm).
* **Hỗ Trợ Nhập Liệu (Auto-suggestion UI):** Dập tắt rủi ro sai sót của nhân viên khi phải nhớ hàng ngũ hàng trăm mã Sản phẩm. Mỗi khi thu ngân cần quét mã Hàng hoặc Nhập kho mới, một luồng helper sẽ chạy ra để render thanh Gợi Ý Mã Hàng trên đỉnh giao diện màn hình `[HỖ TRỢ NHẬP LIỆU: SP01 | RAU02 | ...]`, giúp thao tác nhanh gấp 3 lần.

---
**Nhận xét quy mô:** 
Dự án không chỉ dừng lại ở các bài toán Nhập Xuất mảng cơ bản mà đã chạm tới kiến trúc phần mềm thực thụ nhờ tư duy cấu trúc hướng đối tượng (OOP - Encapsulation, Polymorphism) và File Structuring thông minh. Giao diện Terminal đạt cảnh giới sạch sẽ (Clean UI) và chuyên nghiệp tối đa dành cho C++ native.
