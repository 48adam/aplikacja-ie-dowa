#include "Stock.h"
#include <cstdlib>

Stock::Stock(const std::string& symbol, const std::string& name, float currentPrice, float previousPrice)
    : symbol(symbol), name(name), currentPrice(currentPrice), previousPrice(previousPrice) {
}



std::string Stock::getSymbol() const { return symbol; }
std::string Stock::getName() const { return name; }
float Stock::getCurrentPrice() const { return currentPrice; }
float Stock::getPreviousPrice() const { return previousPrice; }