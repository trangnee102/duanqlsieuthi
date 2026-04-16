#include "models/entities/Customer.h"

// Gọi constructor của class cha (Person) để nó tự gán ID, Name, Phone
Customer::Customer(std::string id, std::string name, std::string phone, int points)
    : Person(id, name, phone), points(points) {
    updateLevel();
}

// Logic phân hạng thành viên
void Customer::updateLevel() {
    if (points >= 2000) memberLevel = "Thách đấu";
    else if (points >= 1000) memberLevel = "Cao thủ";
    else if (points >= 500) memberLevel = "Kim cương";
    else if (points >= 400) memberLevel = "Bạch kim";
    else if (points >= 300) memberLevel = "Vàng";
    else if (points >= 200) memberLevel = "Bạc";
    else if (points >= 100) memberLevel = "Đồng";
    else memberLevel = "Thường";
}

double Customer::getDiscountRate() const {
    if (points >= 2000) return 0.35;
    if (points >= 1000) return 0.30;
    if (points >= 500) return 0.25;
    if (points >= 400) return 0.20;
    if (points >= 300) return 0.15;
    if (points >= 200) return 0.10;
    if (points >= 100) return 0.05;
    return 0.0;
}

// Trả về thông tin riêng của Customer
int Customer::getPoints() const { return points; }
std::string Customer::getMemberLevel() const { return memberLevel; }

// Khi mua hàng, gọi hàm này để cộng điểm và tự nâng hạng
void Customer::addPoints(int p) {
    points += p;
    updateLevel();
}