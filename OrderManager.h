#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include "Order.h"
#include "StockManager.h"
#include "Vector.h"


class OrderManager {
public:
    void addOrder(Order* order);
    void writeOrdersToFile(const std::string& filename);
    void createOrder(StockManager& stockManager);
    void displayAllOrders() const;
    void readOrdersFromFile(const std::string& filename, StockManager& stockManager);
    void deleteOrder();
    void updateOrdersInFile(const std::string& filename);
    bool orderExists(int orderId) const;
    ~OrderManager();

    Vector<Order*> orders;
};

#endif // ORDER_MANAGER_H
