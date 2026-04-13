#ifndef DUANQLSIEUTHI_INPUTUTILS_H
#define DUANQLSIEUTHI_INPUTUTILS_H

#pragma once
#include <string>

class InputUtils {
public:
    // Bắt người dùng nhập Số nguyên hợp lệ. 
    // Trả về -1 nếu người dùng muốn HỦY tiến trình.
    static int getValidInt(std::string prompt, int minVal = 0, int maxVal = 2147483647);

    // Bắt người dùng nhập Số thập phân hợp lệ. 
    // Trả về -1.0 nếu người dùng muốn HỦY tiến trình.
    static double getValidDouble(std::string prompt, double minVal = 0.0);

    // Bắt người dùng nhập Chuỗi không rỗng và không dính dấu phẩy (bảo vệ CSV).
    // Người dùng gõ "CANCEL" hoặc "-1" để HỦY.
    // Trả về "CANCEL" nếu muốn hủy.
    static std::string getValidString(std::string prompt);
};

#endif //DUANQLSIEUTHI_INPUTUTILS_H
