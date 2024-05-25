#include "StockItem.h"
/**
 * Készlet tétel osztály konstruktora, inicializálja az új készlet tételt az adott azonosítóval, névvel, árral és mennyiséggel.
 */
StockItem::StockItem(int id, const std::string& name, double price, int count)
        : id(id), name(name), price(price), count(count) {
}
/**
 * Készlet tétel azonosítójának lekérdezése.
 */
int StockItem::getId() const {
    return id;
}
/**
 * Készlet tétel nevének lekérdezése.
 */
const std::string& StockItem::getName() const {
    return name;
}
/**
 * Készlet tétel árának lekérdezése.
 */
double StockItem::getPrice() const {
    return price;
}
/**
 * Készlet tétel mennyiségének lekérdezése.
 */
int StockItem::getCount() const {
    return count;
}
/**
 * Készlet tétel mennyiségének frissítése a megadott változással.
 */
void StockItem::updateCount(int countChange) {
    count += countChange;
}

