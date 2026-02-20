#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

class Product
{
private:
    std::string name;
    unsigned long price;
    unsigned long stock;
    unsigned long sold;
    int categoryId;

public:
    Product(std::string name, unsigned long price, unsigned long stock, int catId, unsigned long sold = 0);

    std::string getName() const;
    unsigned long getPrice() const;
    unsigned long getStock() const;
    unsigned long getSold() const;
    int getCategoryId() const;

    void sell(unsigned long count);
    void addStock(unsigned long count);
};

#endif