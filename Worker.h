#ifndef WORKER_H
#define WORKER_H

#include "StockItem.h"
#include <string>

class Worker : public StockItem {
public:
    Worker(int id, const std::string& name, double price, int count, const std::string& spec);
    std::string getSpecialization() const;
    void display() const override;

private:
    std::string spec;
};

#endif // WORKER_H
