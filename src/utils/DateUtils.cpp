#include "utils/DateUtils.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

// 1. Lấy ngày hiện tại hệ thống (Định dạng YYYY-MM-DD)
std::string DateUtils::getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(now, "%Y-%m-%d");
    return oss.str();
}

// 2. Logic cộng thêm ngày: Sử dụng mktime để điều chỉnh tự động
std::string DateUtils::addDays(const std::string& dateStr, int days) {
    std::tm t = {};
    std::istringstream iss(dateStr);

    // Đọc chuỗi YYYY-MM-DD vào cấu trúc tm
    char hyphen;
    if (!(iss >> t.tm_year >> hyphen >> t.tm_mon >> hyphen >> t.tm_mday)) {
        return dateStr; // Trả về ngày gốc nếu định dạng sai
    }

    // Cần điều chỉnh vì tm_year tính từ 1900 và tm_mon từ 0-11
    t.tm_year -= 1900;
    t.tm_mon -= 1;

    // Cộng thêm số ngày
    t.tm_mday += days;

    // mktime sẽ tự động điều chỉnh ngày/tháng/năm nếu mday vượt quá giới hạn tháng
    std::mktime(&t);

    std::ostringstream oss;
    oss << std::put_time(&t, "%Y-%m-%d");
    return oss.str();
}

// 3. So sánh ngày (Dựa trên tính chất của chuỗi YYYY-MM-DD)
bool DateUtils::isExpired(const std::string& expiryDate, const std::string& currentDate) {
    if (expiryDate == "None" || expiryDate.empty()) return false;
    // So sánh chuỗi trực tiếp vì định dạng YYYY-MM-DD cho phép so sánh thứ tự từ điển
    return expiryDate < currentDate;
}

// 4. Kiểm tra định dạng ngày có hợp lệ không
bool DateUtils::isValidFormat(const std::string& dateStr) {
    if (dateStr.length() != 10) return false;
    if (dateStr[4] != '-' || dateStr[7] != '-') return false;

    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(dateStr[i])) return false;
    }
    return true;
}

// ==========================================
// THÊM MỚI: 5. Tính số ngày chênh lệch (Ngày 2 - Ngày 1)
// ==========================================
int DateUtils::getDaysDifference(const std::string& date1, const std::string& date2) {
    // Nếu một trong hai ngày trống hoặc "None", trả về một số rất lớn (999 ngày)
    if (date1 == "None" || date2 == "None" || date1.empty() || date2.empty()) {
        return 999;
    }

    std::tm tm1 = {}, tm2 = {};
    std::istringstream iss1(date1), iss2(date2);
    char h; // Chứa dấu gạch ngang '-'

    // Đọc ngày 1
    if (!(iss1 >> tm1.tm_year >> h >> tm1.tm_mon >> h >> tm1.tm_mday)) return 999;
    // Đọc ngày 2
    if (!(iss2 >> tm2.tm_year >> h >> tm2.tm_mon >> h >> tm2.tm_mday)) return 999;

    // Chuẩn hóa định dạng cho struct tm
    tm1.tm_year -= 1900; tm1.tm_mon -= 1;
    tm2.tm_year -= 1900; tm2.tm_mon -= 1;

    // Chuyển sang time_t (số giây) để trừ nhau
    std::time_t t1 = std::mktime(&tm1);
    std::time_t t2 = std::mktime(&tm2);

    if (t1 == -1 || t2 == -1) return 999;

    // Tính chênh lệch giây và đổi ra ngày (1 ngày = 86400 giây)
    double seconds = std::difftime(t2, t1);
    return static_cast<int>(seconds / (60 * 60 * 24));
}