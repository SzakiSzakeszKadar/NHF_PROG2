#ifndef STOCKITEM_H
#define STOCKITEM_H

#include <string>


class StockItem {
public:
    StockItem(int id, const std::string& name, double price, int count);
    StockItem() = default;
    virtual ~StockItem() = default;
    int getId() const;
    const std::string& getName() const;
    double getPrice() const;
    int getCount() const;
    void updateCount(int countChange);
    virtual void display() const = 0;

protected:
    int id{};
    std::string name;
    double price{};
    int count{};
};

#endif // STOCKITEM_H
