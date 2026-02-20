#include "Product.hpp"

/*
 * نام تابع: Product (Constructor)
 * وظیفه: مقداردهی اولیه کالا - حالا مقدار sold را هم برای بازیابی از فایل دریافت می‌کند
 */
Product::Product(std::string name, unsigned long price, unsigned long stock, int catId, unsigned long sold)
    : name(name), price(price), stock(stock), sold(sold), categoryId(catId) {}

std::string Product::getName() const { return name; }
unsigned long Product::getPrice() const { return price; }
unsigned long Product::getStock() const { return stock; }
unsigned long Product::getSold() const { return sold; }
int Product::getCategoryId() const { return categoryId; }

/*
 * نام تابع: sell
 * وظیفه: کاهش موجودی و افزایش آمار فروش
 */
void Product::sell(unsigned long count) {
    if (stock >= count) {
        stock -= count;
        sold += count;
    }
}

void Product::addStock(unsigned long count) { stock += count; }