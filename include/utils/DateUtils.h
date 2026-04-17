#ifndef DUANQLSIEUTHI_DATEUTILS_H
#define DUANQLSIEUTHI_DATEUTILS_H

#include <string>

class DateUtils {
public:
    static std::string getCurrentDate();
    static std::string addDays(const std::string& dateStr, int days);
    static bool isExpired(const std::string& expiryDate, const std::string& currentDate);
    static bool isValidFormat(const std::string& dateStr);

    
    static int getDaysDifference(const std::string& date1, const std::string& date2);
};

#endif