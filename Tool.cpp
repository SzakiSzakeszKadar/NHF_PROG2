#include "Tool.h"
#include <iostream>
/*
 * Tool osztály konstruktora.
*/
Tool::Tool(int id, const std::string& name, double price, int count, double heavinessIndex)
        : StockItem(id, name, price, count), heavinessIndex(heavinessIndex) {
}
/*
 * Tool osztály display() metódusa.
 * Megjeleníti az eszköz adatait a konzolon.
 * Amennyiben az eszközből nincs készleten, az out of stock üzenetet jeleníti meg.
*/
void Tool::display() const {
    if(count>0)std::cout << "Tool [ID=" << id << ", Name=" << name << ", Price=" << price << ", Count=" << count << ", Heaviness Index=" << heavinessIndex << "]\n";
    else std::cout<<"Item with ID = "<<id<<" is out of stock\n";
}
/*
 * Tool osztály getHeavinessIndex() metódusa.
 * Visszaadja az eszköz súlyossági indexét.
 * visszaadja eszköz súlyossági indexét.
*/
double Tool::getHeavinessIndex() const {
    return heavinessIndex;
}
