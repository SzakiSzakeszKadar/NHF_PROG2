#include "Machine.h"
#include <iostream>
/*
 * Gép osztály konstruktora, inicializálja az új gépet a megadott paraméterekkel.
 */
Machine::Machine(int id, const std::string& name, double price, int count, bool needsConductor)
        : StockItem(id, name, price, count), needsConductor(needsConductor) {
}
/*
 * Megjeleníti a gép adatait az alábbi formátumban:
 * Machine [ID=azonosító, Name=név, Price=ár, Count=mennyiség, Needs Conductor=igen/nem]
 * Ha a gépből nincs készleten, az "out of stock" üzenetet jeleníti meg.
*/
void Machine::display() const {
   if(count>0) std::cout << "Machine [ID=" << id << ", Name=" << name << ", Price=" << price << ", Count=" << count << ", Needs Conductor=" << (needsConductor ? "Yes" : "No") << "]\n";
   else std::cout<<"Item with ID = "<<id<<" is out of stock\n";
}
/*
 * Ellenőrzi, hogy a gépnek szüksége van-e vezérlőre.
 * Visszatérési érték: true, ha szükség van, egyébként false.
*/
bool Machine::NeedsConductor() const {
    return needsConductor;
}
