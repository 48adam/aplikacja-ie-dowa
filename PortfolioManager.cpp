// PortfolioManager.cpp
#include "PortfolioManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

bool PortfolioManager::buyStock(const std::string& symbol, float price, int quantity) {
    float total = price * quantity;
    if (cash < total) return false;

    for (auto& e : entries) {
        if (e.ticker == symbol) {
            // aktualizacja œredniej ceny
            float oldTotal = e.avgBuyPrice * e.quantity;
            float newTotal = price * quantity;
            e.quantity += quantity;
            e.avgBuyPrice = (oldTotal + newTotal) / e.quantity;
            cash -= total;
            return true;
        }
    }

    // jeœli to nowa akcja
    entries.push_back({ symbol, quantity, price });
    cash -= total;
    return true;
}



bool PortfolioManager::sellStock(const std::string& symbol, float price, int quantity) {
    if (portfolio[symbol] >= quantity) {
        portfolio[symbol] -= quantity;
        cash += price * quantity;
        return true;
    }
    return false;
}


float PortfolioManager::totalValue(const std::map<std::string, float>& currentPrices) const {
    float sum = 0.0f;
    for (const auto& entry : entries) {
        auto it = currentPrices.find(entry.ticker);
        if (it != currentPrices.end()) {
            sum += it->second * entry.quantity;
        }
    }
    return sum;
}

void PortfolioManager::loadFromFile(const std::string& username) {
    entries.clear();
    std::ifstream file("portfolios/" + username + ".portfolio");
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string ticker;
        iss >> ticker;

        if (ticker == "CASH") {
            iss >> cash;
            continue;
        }

        PortfolioEntry entry;
        entry.ticker = ticker;
        iss >> entry.quantity >> entry.avgBuyPrice;
        entries.push_back(entry);
    }
}


void PortfolioManager::saveToFile(const std::string& username) {
    std::ofstream file("portfolios/" + username + ".portfolio");
    for (const auto& e : entries) {
        file << e.ticker << " " << e.quantity << " " << e.avgBuyPrice << "\n";
    }
    file << "CASH " << cash << "\n";
}


const std::vector<PortfolioEntry>& PortfolioManager::getEntries() const {
    return entries;
}

PortfolioEntry* PortfolioManager::getEntry(const std::string& ticker) {
    for (auto& entry : entries) {
        if (entry.ticker == ticker) {
            return &entry;
        }
    }
    return nullptr;
}
