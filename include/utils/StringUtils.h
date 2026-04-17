#ifndef DUANQLSIEUTHI_STRINGUTILS_H
#define DUANQLSIEUTHI_STRINGUTILS_H

#pragma once
#include <string>

class StringUtils {
public:
    // Chuyển toàn bộ chuỗi UTF-8 sang chữ thường (Dùng cho Tìm kiếm - Ignore Case)
    static std::string toLowerCase(const std::string& input);

    // VD: "ngUYỄn văN a" -> "Nguyễn Văn A"
    static std::string toTitleCase(const std::string& input);

    // Loại bỏ dấu Tiếng Việt
    static std::string removeAccents(const std::string& input);

    // Cắt chuỗi an toàn cho UTF-8 (Tiếng Việt), không gây lỗi ký tự rác
    static std::string safeSubstr(const std::string& str, int maxLen);

    // Tính độ dài chuỗi (Số lượng ký tự thực sự hiển thị trên màn hình, bỏ qua byte độn)
    static int utf8_length(const std::string& str);

    // Chèn đúng số khoảng trắng (Space) vào chuỗi để căn lề hiển thị
    static std::string padRight(std::string str, int width);
};

#endif //DUANQLSIEUTHI_STRINGUTILS_H