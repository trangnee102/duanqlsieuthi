# BẢNG PHÂN CÔNG NHIỆM VỤ ĐỒ ÁN
**Dự Án:** Hệ thống Quản Lý Siêu Thị C++ 

Dưới đây là bảng phân công công việc của 5 người trong nhóm. Trong quá trình làm đồ án, nhóm có tham khảo tài liệu, tìm hiểu thuật toán trên mạng và sử dụng các công cụ hỗ trợ AI (vibe coding tools) để tăng tốc độ làm việc cũng như gỡ lỗi. Tuy nhiên, mỗi thành viên đều có vai trò cụ thể để đảm bảo dự án chạy xuyên suốt:

---

## Danh Sách Thành Viên & Vai Trò

| STT | Họ và Tên | Vai trò | Mô tả công việc thực tế | Mức độ hoàn thành |
| :--: | :--- | :--- | :--- | :---: |
| **1** | **Huyền Trang** | Lập trình chính & Tính năng (Main Coder) | Phụ trách sáng tạo và viết mã nguồn (code) chính cho các tính năng cốt lõi và mở rộng của dự án. Dựng sườn MVC ban đầu. Cấu trúc đầy đủ các hàm. *(Tuy nhiên bộ code thô lúc đầu gặp nhiều rủi ro về logic, chưa chặn được lỗi nhập liệu).* | 100% |
| **2** | **Minh Hiếu** | Làm Dữ liệu (Database) | Soạn thảo dữ liệu mẫu cho hệ thống. Điền file Lô hàng, Khách hàng, Hoá đơn vào định dạng `.csv`. Kiểm tra việc file trích xuất đúng định dạng. | 100% |
| **3** | **Tiến Anh** | Gỡ lỗi & Tối ưu Trải nghiệm (Bug Fixer / UX) | Dọn dẹp lỗi logic của bộ code thô, thiết lập "bức tường" chặn lỗi (Bắt nhập sai kiểu chữ/ký tự, vòng lặp vô hạn). Cải thiện mạnh trải nghiệm người dùng (UX). *VD: Chèn thanh Auto-suggestion nhắc người dùng mã SP khi thanh toán; Viết thêm hàm render biểu đồ ASCII khi xem phân tích doanh thu.* | 100% |
| **4** | **Ngọc Hà** | Kiểm thử (Tester) | Đóng vai người dùng để chạy thử hệ thống. Thử các ca nhập tào lao vào màn hình Quản lý Kho để xem chương trình có bị văng (crash) không. Note lỗi lại cho Tiến Anh sửa. | 100% |
| **5** | **Xuân Hiệp** | Kiểm thử (Tester) | Chạy thử luồng Thanh toán (POS) và in Báo cáo. Check xem tiền tính có đúng không, nhập số điện thoại vớ vẩn thì máy có báo lỗi không. | 100% |

---

## Quá Trình Làm Việc Chung
* **Quy trình tiếp sức:** Bạn Huyền Trang đóng vai trò "công binh" mở đường, cày ải viết một lượng code cực lớn cho toàn bộ hệ thống các module và kết hợp với data của bạn Hiếu. Tuy nhiên lúc chạy thì gặp rất nhiều lỗi dở khóc dở cười (do chưa bắt Exception đầu vào).
* Bạn Tiến Anh giống như "cứu hoả", nhận nhiệm vụ đi đọc lại đống code đó, chặn mọi ngóc ngách dễ sinh lỗi vòng lặp, cũng như "make-color" làm đẹp bằng hàng loạt nâng cấp giao diện tinh tế (biểu đồ doanh thu, in thông báo màu mè, gán phím tắt) với sự tham khảo từ AI.
* Ngọc Hà và Xuân Hiệp test liên tục trên file `.exe` cuối cùng (chạy theo bộ kịch bản test), phát hiện khá nhiều lỗi liên quan tới định dạng chữ và lỗi vượt quá kho, sau đó nhóm cùng ngồi lại xử lý cho đến bản cuối cùng.
