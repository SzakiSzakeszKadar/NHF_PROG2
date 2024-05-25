#include "Worker.h"
#include <iostream>
/*
 * Worker osztály konstruktorának definíciója.
 * */
Worker::Worker(int id, const std::string& name, double price, int count, const std::string& spec)
        : StockItem(id, name, price, count), spec(spec) {
}
/*
 * display függvény definíciója, mely kiírja a dolgozó adatait.
 * */
void Worker::display() const {
    if(count>0)std::cout << "Worker [ID=" << id << ", Name=" << name << ", Price=" << price << ", Count=" << count << ", Spec=" << spec << "]\n";
    else std::cout<<"Item with ID = "<<id<<" is out of stock\n";
}
/*
 * // getSpecialization függvény definíciója, mely visszaadja a dolgozó specializációját.
 * */
std::string Worker::getSpecialization() const {
    return spec;
}
