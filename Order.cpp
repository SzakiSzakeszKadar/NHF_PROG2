#include "Order.h"
#include <iostream>
/*
 * Rendelés osztály konstruktora, inicializálja az új rendelést az adott azonosítóval és ügyfél névvel.
 */
Order::Order(int id, const std::string& customerName)
        : id(id), customerName(customerName) {
}
/*
 * Rendelés osztály destruktora.
 */
Order::~Order() = default;
/*
 * Rendelés azonosítójának lekérdezése.
 */
int Order::getId() const {
    return id;
}
/**
 * Rendelés ügyfél nevének lekérdezése.
 */
const std::string& Order::getCustomerName() const {
    return customerName;
}
/**
 * Rendeléshez tétel hozzáadása a megadott készlet tételből és mennyiségből.
 * A tétel hozzáadása után frissíti a készlet mennyiségét.
 */
void Order::addItem(StockItem* stockItem, int quantity) {
    items.push_back(make_pair(stockItem, quantity));
    stockItem->updateCount(-1*quantity);
}
/**
 * A rendeléshez tartozó tételek lekérdezése.
 */
const Vector<Pair<StockItem*, int>>& Order::getItems() const {
    return items;
}
/**
 * Rendelés adatainak megjelenítése a konzolon.
 */
void Order::display() const {
    std::cout << "Order [ID=" << id << ", Customer=" << customerName << "]\n";
    for (size_t i = 0; i < items.size(); ++i) {
        const StockItem* stockItem = items.at(i).first;
        int quantity = items.at(i).second;
        std::cout << "  Item [ID=" << stockItem->getId()
                  << ", Name=" << stockItem->getName()
                  << ", Price=" << stockItem->getPrice()
                  << ", Quantity=" << quantity << "]\n";
    }
}
/**
 * Rendelés ajánlatának megjelenítése a konzolon.
 * Az ajánlat tartalmazza a rendelt tételeket és az összesített árat.
 */
void Order::displayOffer() const {
    std::cout << "Order offer [ID=" << id << ", Customer=" << customerName << "]\n";
    double totalPrice = 0.0;
    for (size_t i = 0; i < items.size(); ++i) {
        const StockItem* stockItem = items.at(i).first;
        int quantity = items.at(i).second;
        double itemTotal = stockItem->getPrice() * quantity;
        totalPrice += itemTotal;
        std::cout << "  Item [ID=" << stockItem->getId()
                  << ", Name=" << stockItem->getName()
                  << ", Price=" << stockItem->getPrice()
                  << ", Quantity=" << quantity
                  << ", Total Price=" << itemTotal << "]\n";
    }
    std::cout << "Total Order Price: " << totalPrice << "\n";
}
