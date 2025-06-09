#pragma once
#include "Stock.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <vector>
#include <mutex>
#include <filesystem>
#include <sstream>
#include <memory>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class StockMarket {
private:
    std::vector<Stock> stocks;
    std::mutex mtx;
    std::filesystem::path filepath;
    std::string result;

   
    void copyLinesToVector(const std::vector<std::string>& source, size_t start, size_t end, std::vector<std::string>& output);
    std::string readSingleFileMultithreaded(std::vector<std::string>& part1, std::vector<std::string>& part2);

public:
    StockMarket();
    float getPriceForSymbol(const std::string& symbol) const;
    void loadStocks();
    std::map<std::string, float> getPricesFromYahoo(const std::vector<std::string>& symbols);
    void update(); // aktualizuje ceny wszystkich akcji
    const std::vector<Stock>& getStocks() const;
    Stock* findStockBySymbol(const std::string& symbol);




};