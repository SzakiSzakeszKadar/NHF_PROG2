#ifndef ORDER_H
#define ORDER_H

#include <string>
#include "Vector.h"
#include "StockItem.h"
#include "Pair.hpp"


class Order {
public:
    Order(int id, const std::string& customerName);
    ~Order();
    int getId() const;
    const std::string& getCustomerName() const;
    void addItem(StockItem* stockItem, int quantity);
    const Vector<Pair<StockItem*, int>>& getItems() const;
    void display() const;
    void displayOffer() const;
private:
    int id;
    std::string customerName;
    Vector<Pair<StockItem*, int>> items;
};

#endif // ORDER_H
