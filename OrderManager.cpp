#include "OrderManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "ConcreteStockItem.h"
#include "memtrace.h"
#include "Inputs.h"
/**
 * Rendelés hozzáadása a rendelések listájához.
 */
void OrderManager::addOrder(Order* order) {
    orders.push_back(order);
}
/**
 * Ellenőrzi, hogy egy adott rendelési azonosító létezik-e már a rendszerben.
 * Visszatérési érték: true, ha létezik, egyébként false.
 */
bool OrderManager::orderExists(int orderId) const {
    for (size_t i = 0; i < orders.size(); ++i) {
        if (orders[i]->getId() == orderId) {
            return true;
        }
    }
    return false;
}
/**
 * Rendelések kiírása fájlba.
 */
void OrderManager::writeOrdersToFile(const std::string& filename) {
    std::ofstream file(filename, std::ofstream::trunc);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    for (size_t i = 0; i < orders.size(); ++i) {
        Order* order = orders.at(i);
        file << order->getId() << "," << order->getCustomerName();
        const Vector<Pair<StockItem*, int>>& items = order->getItems();
        for (size_t j = 0; j < items.size(); ++j) {
            StockItem* stockItem = items.at(j).first;
            int quantity = items.at(j).second;
            file << "," << stockItem->getId() << "," << stockItem->getName() << "," << stockItem->getPrice() << "," << quantity;
        }
        file << "\n";
    }
}
/**
 * Új rendelés létrehozása a rendelési listához.
 */
void OrderManager::createOrder(StockManager& stockManager) {
    int orderId = readNumber<int>("Enter order ID: ");
    if (orderExists(orderId)) {
        std::cerr << "An order with ID " << orderId << " already exists.\n";
        return;
    }

    std::string customerName = readString("Enter customer name: ");
    auto* order = new Order(orderId, customerName);
    while (true) {
        int stockItemId = readNumber<int>("Enter stock item ID to add to order (or -1 to finish): ");
        if (stockItemId == -1) {
            break;
        }
        Vector<StockItem*> matchingItems;
        for (size_t i = 0; i < stockManager.getStocks().size(); ++i) {
            StockItem* stockItem = stockManager.getStocks().at(i);
            if (stockItem->getId() == stockItemId) {
                matchingItems.push_back(stockItem);
            }
        }
        if (matchingItems.size()==0) {
            std::cerr << "There is no item with ID " << stockItemId << "\n";
            continue;
        }
        if (matchingItems.size() == 1) {
            int quantity = readNumber<int>("Enter quantity: ");
            StockItem* selectedItem = matchingItems.at(0);
            if (selectedItem->getCount() < quantity) {
                std::cerr << "Not enough stock available. Available: " << selectedItem->getCount() << "\n";
                continue;
            }
            order->addItem(selectedItem, quantity);
        } else {
            std::cout << "Multiple items found with the same ID. Please choose the item:\n";
            for (size_t i = 0; i < matchingItems.size(); ++i) {
                std::cout << i + 1 << ". " << matchingItems.at(i)->getName()
                          << " (ID: " << matchingItems.at(i)->getId()
                          << ", Price: " << matchingItems.at(i)->getPrice()
                          << ", Stock: " << matchingItems.at(i)->getCount() << ")\n";
            }
            int choice = readNumber<int>("Enter the number of the item you want to choose: ");
            if (choice < 1 || choice > static_cast<int>(matchingItems.size())) {
                std::cerr << "Invalid choice\n";
                continue;
            }
            StockItem* selectedItem = matchingItems.at(choice - 1);
            int quantity = readNumber<int>("Enter quantity: ");
            if (selectedItem->getCount() < quantity) {
                std::cerr << "Not enough stock available. Available: " << selectedItem->getCount() << "\n";
                continue;
            }
            order->addItem(selectedItem, quantity);
        }
    }
    order->displayOffer();
    std::string confirmation = readString("Do you want to confirm the order? (yes/no): ");
    if (confirmation == "yes") {
        addOrder(order);
        writeOrdersToFile("orders.csv");
        std::cout << "Order confirmed.\n";
    } else {
        delete order;
        std::cout << "Order not confirmed and removed.\n";
    }
}
/**
 * Összes rendelés megjelenítése.
 */
void OrderManager::displayAllOrders() const {
    for (size_t i = 0; i < orders.size(); ++i) {
        orders.at(i)->display();
    }
}
/**
 * Rendeléskezelő osztály destruktora.
 */
OrderManager::~OrderManager() {
    for (size_t i = 0; i < orders.size(); ++i) {
        delete orders.at(i);
    }
}
/**
 * Rendelések beolvasása fájlból.
 */
void OrderManager::readOrdersFromFile(const std::string& filename, StockManager& stockManager) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string token;
        std::getline(iss, token, ',');
        int orderId = std::stoi(token);
        std::getline(iss, token, ',');
        std::string customerName = token;
        auto* order = new Order(orderId, customerName);
        while (std::getline(iss, token, ',')) {
            int stockItemId = std::stoi(token);
            std::getline(iss, token, ',');
            std::string stockItemName = token;
            std::getline(iss, token, ',');
            double stockItemPrice = std::stod(token);
            std::getline(iss, token, ',');
            int quantity = std::stoi(token);
            StockItem* stockItem = stockManager.getStockById(stockItemId);
            if (!stockItem) {
                stockItem = new ConcreteStockItem(stockItemId, stockItemName, stockItemPrice, 0);
                stockManager.addStockItem(stockItem);
            }
            order->addItem(stockItem, quantity);
        }
        addOrder(order);
    }
    file.close();
    std::cout << "Orders read from file " << filename << " successfully\n";
}
/**
 * Rendelés törlése az azonosító alapján.
 */
void OrderManager::deleteOrder() {
    int orderId = readNumber<int>("Enter the ID of the element you want to delete:");
    for (size_t i = 0; i < orders.size(); ++i) {
        if (orders[i]->getId() == orderId) {
            delete orders[i];
            for (size_t j = i; j < orders.size() - 1; ++j) {
                orders[j] = orders[j + 1];
            }
            orders.pop_back();
            std::cout << "Order with ID " << orderId << " has been deleted.\n";
            return;
        }
    }
    std::cerr << "Order with ID " << orderId << " not found.\n";
}
/**
 * Rendelések frissítése fájlban.
 */
void OrderManager::updateOrdersInFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::trunc);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    file.close();
    writeOrdersToFile(filename);
    std::cout << "Order data updated in file " << filename << " successfully.\n";
}

