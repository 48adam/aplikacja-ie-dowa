#pragma once
// PortfolioManager.h
#pragma once
#include <string>
#include <vector>
#include <map>

struct PortfolioEntry {
    std::string ticker;
    int quantity = 0;
    float avgBuyPrice = 0.0f;
};

class PortfolioManager {
private:
    std::vector<PortfolioEntry> entries;
    float cash = 10000.f; // Domyœlnie 10 000 jednostek
    std::map<std::string, int> portfolio;  // symbol -> iloœæ akcji



public:
    bool buyStock(const std::string& ticker, float price, int quantity);
    bool sellStock(const std::string& ticker, float price, int quantity);
    float totalValue(const std::map<std::string, float>& currentPrices) const;

    void loadFromFile(const std::string& username);
    void saveToFile(const std::string& username);
    float getCash() const { return cash; }


    const std::vector<PortfolioEntry>& getEntries() const;
    PortfolioEntry* getEntry(const std::string& ticker);
};
