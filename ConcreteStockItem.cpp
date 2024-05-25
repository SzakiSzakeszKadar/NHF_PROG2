#include "ConcreteStockItem.h"
#include <iostream>
/*
 * ConcreteStockItem konstruktor, amely inicializálja az új készlet tételt
 * a megadott azonosítóval, névvel, árral és mennyiséggel.
*/
ConcreteStockItem::ConcreteStockItem(int id, const std::string& name, double price, int count)
        : StockItem(id, name, price, count) {}
/*
 * Megjeleníti a készlet tétel adatait az alábbi formátumban:
 * StockItem [ID=azonosító, Name=név, Price=ár, Count=mennyiség]
*/
void ConcreteStockItem::display() const {
    std::cout << "StockItem [ID=" << id << ", Name=" << name << ", Price=" << price << ", Count=" << count << "]" << std::endl;
}
