#ifndef INPUTS_H
#define INPUTS_H

#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <cctype>

/*
 * Sablonfüggvény a felhasználó által bevitt szám olvasására.
 * A függvény ellenőrzi, hogy a bemeneti típus szám-e.
 * Ha nem, fordítási hibát generál.
*/
template <typename T>
T readNumber(const std::string& prompt) {
    static_assert(std::is_arithmetic<T>::value, "Template parameter must be a numeric type.");
    T value;
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cerr << "Error reading input. Please try again.\n";
            continue;
        }
        std::istringstream iss(line);
        iss >> std::noskipws >> value;
        if (iss.eof()) {
            return value;
        } else {
            std::cerr << "Invalid input. Please enter a valid number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
/*
 * Felhasználó által bevitt szöveg olvasása.
*/
inline std::string readString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (!value.empty()) {
            return value;
        } else {
            std::cerr << "Input cannot be empty. Please enter a valid string.\n";
        }
    }
}
/*
 * Felhasználó által bevitt logikai érték (true/false) olvasása.
*/
inline bool readBool(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cerr << "Error reading input. Please try again.\n";
            continue;
        }
        for (char& c : line) {
            c = std::tolower(c);
        }
        if (line == "0" || line == "false") {
            return false;
        } else if (line == "1" || line == "true") {
            return true;
        } else {
            std::cerr << "Invalid input. Please enter 0 (false) or 1 (true).\n";
        }
    }
}

#endif // INPUTS_H
