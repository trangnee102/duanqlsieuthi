#include "utils/StringUtils.h"
#include <locale>
#include <codecvt>
#include <cwctype>
#include <vector>

std::string StringUtils::toLowerCase(const std::string& input) {
    try {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wide = converter.from_bytes(input);
        for (wchar_t& c : wide) {
            c = std::towlower(c);
        }
        return converter.to_bytes(wide);
    } catch (...) {
        return input;
    }
}

std::string StringUtils::toTitleCase(const std::string& input) {
    try {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wide = converter.from_bytes(input);
        bool newWord = true;
        for (wchar_t& c : wide) {
            if (std::iswspace(c)) {
                newWord = true;
            } else if (newWord) {
                c = std::towupper(c);
                newWord = false;
            } else {
                c = std::towlower(c);
            }
        }
        return converter.to_bytes(wide);
    } catch (...) {
        return input;
    }
}

std::string StringUtils::removeAccents(const std::string& input) {
    try {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wide = converter.from_bytes(input);

        std::wstring withAccents = L"áàảãạăắằẳẵặâấầẩẫậéèẻẽẹêếềểễệíìỉĩịóòỏõọôốồổỗộơớờởỡợúùủũụưứừửữựýỳỷỹỵđÁÀẢÃẠĂẮẰẲẴẶÂẤẦẨẪẬÉÈẺẼẸÊẾỀỂỄỆÍÌỈĨỊÓÒỔỖỘƠỚỜỞỠỢÚÙỦŨỤƯỨỪỬỮỰÝỲỶỸỴĐ";
        std::wstring withoutAccents = L"aaaaaaaaaaaaaaaaaeeeeeeeeeeeiiiiiooooooooooooooooouuuuuuuuuuuyuuuuuyyyyydaaaaaaaaaaaaaaaaaeeeeeeeeeeeiiiiiooooooooooooooooouuuuuuuuuuuyyyyyd";

        for (wchar_t& c : wide) {
            size_t pos = withAccents.find(c);
            if (pos != std::wstring::npos) {
                c = withoutAccents[pos];
            }
        }
        return converter.to_bytes(wide);
    } catch (...) {
        return input;
    }
}

int StringUtils::utf8_length(const std::string& str) {
    int len = 0;
    for (size_t i = 0; i < str.length(); ) {
        unsigned char c = (unsigned char)str[i];
        if (c < 0x80) i += 1;
        else if (c < 0xE0) i += 2;
        else if (c < 0xF0) i += 3;
        else i += 4;
        len++;
    }
    return len;
}

// [MỚI]: Hàm cắt chuỗi an toàn cho UTF-8 (Tiếng Việt)
std::string StringUtils::safeSubstr(const std::string& str, int maxLen) {
    if (utf8_length(str) <= maxLen) return str;

    std::string res = "";
    int currentLen = 0;
    for (size_t i = 0; i < str.length(); ) {
        unsigned char c = (unsigned char)str[i];
        int charSize = 0;
        if (c < 0x80) charSize = 1;
        else if (c < 0xE0) charSize = 2;
        else if (c < 0xF0) charSize = 3;
        else charSize = 4;

        if (currentLen + 1 > maxLen) break;

        res += str.substr(i, charSize);
        i += charSize;
        currentLen++;
    }
    return res;
}

std::string StringUtils::padRight(std::string str, int width) {
    int visualLen = utf8_length(str);
    if (width > visualLen) {
        str.append(width - visualLen, ' ');
    }
    return str;
}