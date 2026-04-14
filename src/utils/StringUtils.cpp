#include "utils/StringUtils.h"
#include <locale>
#include <codecvt>
#include <cwctype>

std::string StringUtils::toLowerCase(const std::string& input) {
    try {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wide = converter.from_bytes(input);
        for (wchar_t& c : wide) {
            c = std::towlower(c);
        }
        return converter.to_bytes(wide);
    } catch (...) {
        return input; // Fallback
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
        return input; // Fallback
    }
}

int StringUtils::utf8_length(const std::string& str) {
    int len = 0;
    for (char c : str) {
        // UTF-8 bytes that do not start with 10xxxxxx are the start of a character.
        // Therefore, counting them gives the number of characters.
        if ((c & 0xC0) != 0x80) len++;
    }
    return len;
}

std::string StringUtils::padRight(std::string str, int width) {
    int len = utf8_length(str);
    if (width > len) {
        str.append(width - len, ' ');
    }
    return str;
}
