#include "StockManager.h"
#include "Worker.h"
#include "Machine.h"
#include "Tool.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Inputs.h"
#include "memtrace.h"
/**
 * Ellenőrzi, hogy az azonosítóval rendelkező elem létezik-e már ugyanolyan típusban.
 */
bool StockManager::hasSameIdInCategory(int id, const std::string& type) {
    for (size_t i = 0; i < stocks.size(); ++i) {
        if (stocks[i]->getId() == id) {
            if ((type == "Worker" && dynamic_cast<Worker*>(stocks[i])) ||
                (type == "Machine" && dynamic_cast<Machine*>(stocks[i])) ||
                (type == "Tool" && dynamic_cast<Tool*>(stocks[i]))) {
                return true;
            }
        }
    }
    return false;
}
/**
 * Készlet tétel hozzáadása a készlethez.
 */
void StockManager::addStockItem(StockItem* item) {
    stocks.push_back(item);
}
/**
 * Készlet tétel hozzáadása.
 */
void StockManager::addItem(StockManager& stockManager) {
    std::string type = readString("Enter stock item type (Worker, Machine, Tool): ");
    int id = readNumber<int>("Enter ID: ");
    bool hasSame = stockManager.hasSameIdInCategory(id, type);
    if (hasSame) {
        std::cerr << "Error: An item with the same ID already exists in the category.\n";
        return;
    }
    std::string name = readString("Enter name: ");
    auto price = readNumber<double>("Enter price: ");
    int count = readNumber<int>("Enter count: ");
    if (type == "Worker") {
        std::string spec = readString("Enter specialization: ");
        stockManager.addStockItem(new Worker(id, name, price, count, spec));
    } else if (type == "Machine") {
        bool needsConductor = readBool("Does it need a conductor? (1 for yes, 0 for no): ");
        stockManager.addStockItem(new Machine(id, name, price, count, needsConductor));
    } else if (type == "Tool") {
        auto heavinessIndex = readNumber<double>("Enter heaviness index: ");
        stockManager.addStockItem(new Tool(id, name, price, count, heavinessIndex));
    } else {
        std::cout << "Invalid type\n";
    }
}
/**
 * Azonosító alapján készlet tétel lekérdezése.
 */
StockItem* StockManager::getStockById(int id) const {
    for (size_t i = 0; i < stocks.size(); ++i) {
        if (stocks.at(i)->getId() == id) {
            return stocks.at(i);
        }
    }
    return nullptr;
}
/**
 * Készletek beolvasása fájlból.
 */
void StockManager::readStocksFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::cout << "Reading line: " << line << "\n";  // Debug print
        std::istringstream iss(line);
        std::string type, id, count, name, price;
        std::getline(iss, type, ',');
        std::getline(iss, id, ',');
        std::getline(iss, name, ',');
        std::getline(iss, price, ',');
        std::getline(iss, count, ',');
        if (type == "Worker") {
            std::string spec;
            std::getline(iss, spec, ',');
            addStockItem(new Worker(std::stoi(id), name, std::stod(price), std::stoi(count), spec));
        } else if (type == "Machine") {
            std::string needsConductor;
            std::getline(iss, needsConductor, ',');
            addStockItem(new Machine(std::stoi(id), name, std::stod(price), std::stoi(count), std::stoi(needsConductor)));
        } else if (type == "Tool") {
            std::string heavinessIndex;
            std::getline(iss, heavinessIndex, ',');
            addStockItem(new Tool(std::stoi(id), name, std::stod(price), std::stoi(count), std::stod(heavinessIndex)));
        }
    }
}
/**
 * Készlet tétel eltávolítása az azonosító alapján.
 */
void StockManager::removeStockItemById() {
    int id = readNumber<int>("Enter the ID of the stock item to remove: ");
    Vector<int> matchingIndices;
    for (size_t i = 0; i < stocks.size(); ++i) {
        if (stocks.at(i)->getId() == id) {
            matchingIndices.push_back(static_cast<int>(i));
        }
    }
    std::cout << "Found " << matchingIndices.size() << " item(s) with ID " << id << ":\n";
    for (size_t i = 0; i < matchingIndices.size(); ++i) {
        std::cout << i + 1 << ". ";
        stocks.at(matchingIndices.at(i))->display();
    }
    auto choice = readNumber<unsigned long long>("Enter the number of the item to remove: ");
    if (choice < 1 || choice > matchingIndices.size()) {
        std::cerr << "Invalid selection.\n";
        return;
    }
    int indexToRemove = matchingIndices.at(choice - 1);
    delete stocks.at(indexToRemove);
    stocks.erase(indexToRemove);
    std::cout << "Stock item with ID " << id << " has been removed.\n";
}
/**
 * Készlet mennyiségének csökkentése az azonosító alapján.
 */
void StockManager::decreaseStockItemCountById(int id) const {
    StockItem* item = getStockById(id); // Find the stock item by its ID
    if (item) {
        item->updateCount(-1); // Decrease the count of the item
        std::cout << "Stock item with ID " << id << " successfully decreased by one\n";
    } else {
        std::cerr << "Error: Stock item with ID " << id << " not found\n";
    }
}
/**
 * Összes készlet tétel megjelenítése.
 */
void StockManager::displayAllStocks() const {
    for (size_t i = 0; i < stocks.size(); ++i) {
        stocks.at(i)->display();
    }
}
/*
 * Készletek írása fájlba.
 */
void StockManager::writeStocksToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::trunc);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    for (size_t i = 0; i < stocks.size(); ++i) {
        StockItem* item = stocks.at(i);
        if (dynamic_cast<Worker*>(item)) {
            auto* worker = dynamic_cast<Worker*>(item);
            file << "Worker," << worker->getId() << "," << worker->getName() << "," << worker->getPrice() << "," << worker->getCount() << "," << worker->getSpecialization() << "\n";
        } else if (dynamic_cast<Machine*>(item)) {
            auto* machine = dynamic_cast<Machine*>(item);
            file << "Machine," << machine->getId() << "," << machine->getName() << "," << machine->getPrice() << "," << machine->getCount() << "," << machine->needsConductor << "\n";
        } else if (dynamic_cast<Tool*>(item)) {
            Tool* tool = dynamic_cast<Tool*>(item);
            file << "Tool," << tool->getId() << "," << tool->getName() << "," << tool->getPrice() << "," << tool->getCount() << "," << tool->getHeavinessIndex() << "\n";
        }
    }
    file.close();
}
/**
 * Készletek frissítése fájlban.
 */
void StockManager::updateStocksInFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::trunc);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    file.close();
    writeStocksToFile(filename);
    std::cout << "Stock data updated in file " << filename << " successfully.\n";
}
/**
 * StockManager osztály destruktora.
 */
StockManager::~StockManager() {
    for (size_t i = 0; i < stocks.size(); ++i) {
        delete stocks.at(i);
    }
}