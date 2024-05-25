#ifndef STOCKMANAGER_H
#define STOCKMANAGER_H

#include "StockItem.h"
#include "Vector.h"
#include <string>

class StockManager {
public:
    StockManager() = default;
    ~StockManager();
    void addStockItem(StockItem* item);
    StockItem* getStockById(int id) const;
    void readStocksFromFile(const std::string& filename);
    static void addItem(StockManager& stockManager);
    void displayAllStocks() const;
    void removeStockItemById();
    void decreaseStockItemCountById(int id) const;
    void writeStocksToFile(const std::string& filename);
    void updateStocksInFile(const std::string& filename);
    bool hasSameIdInCategory(int id, const std::string& type);
    const Vector<StockItem*>& getStocks() const {
        return stocks;
    }
private:
   Vector<StockItem*> stocks;
};

#endif // STOCKMANAGER_H
