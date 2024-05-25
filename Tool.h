#ifndef TOOL_H
#define TOOL_H

#include "StockItem.h"
#include <string>

class Tool : public StockItem {
public:
    Tool(int id, const std::string& name, double price, int count, double heavinessIndex);

    void display() const override;

    double getHeavinessIndex() const;

private:
    double heavinessIndex;
};

#endif // TOOL_H
