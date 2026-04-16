# Bộ Kịch Bản Kiểm Thử (Test Cases) - Tính Năng Chăm Sóc Khách Hàng & Nâng Cấp Logic

Dưới đây là các kịch bản kiểm thử (Test Cases) cho những thay đổi vừa thực hiện, đảm bảo tuân thủ tiêu chuẩn chất lượng của dự án C++ QLSieuThi.

## 1. Test Case: Phân Hạng Thành Viên & Cấp Mức Giảm Giá Kép
**Mục đích:** Đảm bảo hệ thống tự động thăng hạng khách hàng dựa trên điểm số và áp dụng đúng mã giảm giá theo hạng.

* **Bước 1:** Khởi động hệ thống, đăng nhập bằng tài khoản `staff01`.
* **Bước 2:** Vào Menu `9. Thanh toán POS`. Khai báo SĐT Khách hàng VIP (Ví dụ khách hàng đang có 1200 điểm - Cao thủ).
* **Bước 3:** Quét mã sản phẩm (giả sử trị giá đơn hàng là `500.000` VND trước chiết khấu).
* **Bước 4:** Gõ `0` để chốt đơn in hóa đơn.
* **Kết quả mong muốn:**
  - Tiền hàng hiển thị: `500.000` VND.
  - Màn hình hiển thị dòng thông báo: `Chiết khấu thành viên (Cao thủ): -150000 VND` (Tương đương 30%).
  - TỔNG PHẢI THANH TOÁN: `350.000` VND. Giao dịch diễn ra trơn tru. Hệ thống tự động update cộng thêm 35 điểm (350k/10k) vào tài khoản cho đợt đi chợ lần tới.

## 2. Test Case: Cấp Lương Cứng & Xoá Bỏ Giờ Công
**Mục đích:** Xác minh việc xóa bỏ module giờ làm, hệ thống tự cấp lương cứng dựa trên quyền.

* **Bước 1:** Đăng nhập tk Admin. Vào Menu Quản lý Nhân sự (Phím `3`).
* **Bước 2:** Chọn mục `1. Xem danh sách`.
* **Kết quả mong muốn:**
  - Bảng hiển thị không còn cột `Giờ làm`. Cột cuối cùng được đổi tên thành `Lương cơ bản`. Lương cứng hiển thị mốc cố định: Admin (200k), Purchasing (60k), Staff (50k).
* **Bước 3:** Nhấn Menu tạo mới nhân sự, phân quyền `Staff`.
* **Kết quả mong muốn:** Hệ thống KHÔNG CÒN HỎI CÂU "Mức lương bao nhiêu?". 
* **Bước 4:** Load lại danh sách. Thấy nhân sự mới hiển thị lương base chuẩn là `50000` VND.

## 3. Test Case: Bán Hàng POS Trễ Giờ - Bắt Cú Đêm
**Mục đích:** Xác nhận hệ thống cấm thu ngân tính tiền những mặt hàng không hợp lệ.

* **Tình huống A (Hàng Khô Hết Hạn):**
  - Chọn một mặt hàng khô, sửa `hsd` trong file kho thành ngày hôm qua.
  - Quét mã sản phẩm tại máy POS thu ngân.
  - **Dự kiến:** Bị chặn đứng bởi dòng thông báo màu đỏ: `=> [LỖI] SẢN PHẨM KHÔNG CÒN HẠN SỬ DỤNG`. Cấm mua.

* **Tình huống B (Hàng Tươi Sai Giờ Cấm):**
  - Chỉnh giờ đồng hồ máy tính hệ thống (Windows) qua mốc `22:00` khuya.
  - Quét mã hàng tươi sống (Thịt/Rau Daily Fresh) có HSD bằng đúng Ngày Hôm Nay.
  - **Dự kiến:** Thông báo `=> [LỖI] ĐÃ QUÁ 22H! ĐỒ TƯƠI ĐÃ HẾT HẠN!`. Không được tự tiện bán với giá giảm 50% như trong khung giờ 19h nữa. Bị chặn tuyệt đối khỏi giỏ hàng.

## 4. Test Case: Nhập Lô Hàng Thông Minh Đỡ Sai Sót
**Mục đích:** Rà soát lại việc sinh mã lô hàng Tự Động và UX khi sửa dữ liệu.

* **Bước 1:** Đăng nhập tk Purchasing `PU01`, vào Menu QL Kho (Phím `2`).
* **Bước 2:** Nhấn phím `14` dể Nhập lô bổ sung.
* **Bước 3:** Nhập thử ID `ABC_Sai_Ma`. => Dự kiến: Máy báo Lỗi Không tìm thấy sản phẩm và đá văng Menu ra, không làm mất thời gian.
* **Bước 4:** Gõ đúng ID Sản phẩm thịt lợn. 
* **Dự kiến:** Máy in `Tên Sản Phẩm: Thịt ba chỉ` ra màn hình để báo hiệu chuẩn xác (đúng yêu cầu UX).
* **Bước 5:** Báo hoàn thành. Vào `batches.csv` để chứng thực. Dòng dữ liệu được bổ sung nối tiếp với định cấu trúc lưu 5 cột hoàn chỉnh `Batch_ID, Product_ID, Expiry, Qty, Import_Date`.
