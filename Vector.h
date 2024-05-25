#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include "memtrace.h"
/*
 * Vektor osztály sablon definíciója.
 */
template<typename T>
class Vector {
public:
    Vector();
    ~Vector();
    void push_back(const T& value);
    T& at(size_t index);
    const T& at(size_t index) const;
    size_t size() const;
    void erase(size_t index);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    void pop_back();
private:
    T* data;
    size_t capacity;
    size_t length;
    void resize();
};
/*
 * Operátor [] felülbírálása.
 * */
template <typename T>
T& Vector<T>::operator[](size_t index) {
    return at(index);
}
/*
 * Konstans operátor [] felülbírálása.
*/
template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    return at(index);
}
/*
 * Vector osztály konstruktora.
 */
template<typename T>
Vector<T>::Vector() : data(nullptr), capacity(0), length(0) {}
/*
 *Vector osztály destruktora.
 */
template<typename T>
Vector<T>::~Vector() {
    delete[] data;
}
/*
 *  Új elem hozzáadása a Vector végéhez.
 * */
template<typename T>
void Vector<T>::push_back(const T& value) {
    if (length == capacity) {
        resize();
    }
    data[length++] = value;
}
/*
 * Adott indexen lévő elem lekérdezése.
 * */
template<typename T>
T& Vector<T>::at(size_t index) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}
/*
 * Adott indexen lévő konstans elem lekérdezése.
*/
template<typename T>
const T& Vector<T>::at(size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}
/*
* Vector méretének lekérdezése.
*/
template<typename T>
size_t Vector<T>::size() const {
    return length;
}
/*
 *Vector méretének növelése.
 * */
template<typename T>
void Vector<T>::resize() {
    capacity = (capacity == 0) ? 1 : capacity * 2;
    T* newData = new T[capacity];
    for (size_t i = 0; i < length; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}
/*
 * Adott indexű elem törlése a Vectorból.
*/
template<typename T>
void Vector<T>::erase(size_t index) {
    if (index >= size()) return;
    for (size_t i = index; i < size() - 1; ++i) {
        data[i] = data[i + 1];
    }
    --length;
}

/*
 *Utolsó elem törlése a Vectorból.
*/
template <typename T>
void Vector<T>::pop_back() {
    if (length > 0) {
        --length;
    } else {
        std::cerr << "Vector is empty, cannot pop_back.\n";
    }
}
#endif // VECTOR_H
