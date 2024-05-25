#ifndef CONCRETESTOCKITEM_H
#define CONCRETESTOCKITEM_H

#include "StockItem.h"


class ConcreteStockItem : public StockItem {
public:
    ConcreteStockItem(int id, const std::string& name, double price, int count);
    void display() const override;
};

#endif // CONCRETESTOCKITEM_H
