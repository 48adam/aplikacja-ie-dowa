#pragma once
#include <string>

class Stock {
public:
    Stock(const std::string& symbol, const std::string& name, float currentPrice, float previousPrice);

    std::string getSymbol() const;
    std::string getName() const;
    float getCurrentPrice() const;
    float getPreviousPrice() const;

private:
    std::string symbol;
    std::string name;
    float currentPrice;
    float previousPrice;
};