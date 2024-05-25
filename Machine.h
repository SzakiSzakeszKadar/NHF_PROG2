#ifndef MACHINE_H
#define MACHINE_H

#include "StockItem.h"
#include <string>

class Machine : public StockItem {
public:
    Machine(int id, const std::string& name, double price, int count, bool needsConductor);
    bool NeedsConductor() const;
    void display() const override;

    bool needsConductor;
};

#endif // MACHINE_H
