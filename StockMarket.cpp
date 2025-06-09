

#include "StockMarket.h"


void StockMarket::loadStocks() {
    stocks.clear();

    std::vector<std::string> vector1, vector2;
    std::string result = this->readSingleFileMultithreaded(vector1, vector2);

    if (result != "OK") {
        std::cerr << "Błąd wczytywania danych: " << result << std::endl;
        return;
    }

    
        auto parseLineToStock = [this](const std::string& line) {
            std::stringstream ss(line);
            std::string symbol, name, currentStr, previousStr;

            

                if (std::getline(ss, symbol, ',') &&
                    std::getline(ss, name, ',') &&
                    std::getline(ss, currentStr, ',') &&
                    std::getline(ss, previousStr)) {

                    try {
                        float current = std::stof(currentStr);
                        float previous = std::stof(previousStr);
                        stocks.emplace_back(symbol, name, current, previous);
                    }
                    catch (const std::exception& e) {
                        std::cerr << "Błąd konwersji danych w linii: " << line << " | " << e.what() << std::endl;
                    } 
                
            }
            };
       
        for (const auto& line : vector1) parseLineToStock(line);
        for (const auto& line : vector2) parseLineToStock(line);

}

std::map<std::string, float> StockMarket::getPricesFromYahoo(const std::vector<std::string>& symbols) {
    std::map<std::string, float> result;

    // Łączenie symboli do jednego ciągu, np. "AAPL,GOOG,MSFT"
    std::string symbolList;
    for (const auto& s : symbols) {
        if (!symbolList.empty()) symbolList += ",";
        symbolList += s;
    }

    // Twój prawdziwy klucz z RapidAPI:
    const std::string apiKey = "2925562540msh88f1568cf65fc6bp1eb699jsn82be18988410";

    cpr::Response r = cpr::Get(
        cpr::Url{ "https://apidojo-yahoo-finance-v1.p.rapidapi.com/market/v2/get-quotes" },
        cpr::Header{
            {"X-RapidAPI-Key", apiKey},
            {"X-RapidAPI-Host", "apidojo-yahoo-finance-v1.p.rapidapi.com"}
        },
        cpr::Parameters{
            {"region", "US"},
            {"symbols", symbolList}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "Błąd HTTP (RapidAPI): " << r.status_code << std::endl;
        std::cout << "Kod odpowiedzi: " << r.status_code << "\n";
        std::cout << "Treść odpowiedzi: " << r.text << "\n";

        return result;
    }

    try {
        auto j = json::parse(r.text);
        for (const auto& item : j["quoteResponse"]["result"]) {
            std::string sym = item["symbol"];
            if (!item.contains("regularMarketPrice")) {
                std::cerr << "Brak ceny dla symbolu: " << item["symbol"] << std::endl;
                continue;
            }
            float price = item["regularMarketPrice"];

            result[sym] = price;
        }
    }
    catch (...) {
        std::cerr << "Błąd parsowania JSON z RapidAPI." << std::endl;
    }

    return result;
}

void StockMarket::copyLinesToVector(const std::vector<std::string>& source, size_t start, size_t end, std::vector<std::string>& output) {
    for (size_t i = start; i < end; ++i) {
        output.push_back(source[i]);
    }
}

std::string StockMarket::readSingleFileMultithreaded(std::vector<std::string>& part1, std::vector<std::string>& part2) {
   // std::cout << "[DEBUG] Ścieżka pliku: " << this->filepath << std::endl;

    std::ifstream file(this->filepath);
    if (!file.is_open()) {
        std::cerr << "[BŁĄD] Nie udało się otworzyć pliku: " << this->filepath << std::endl;
        return "FAIL";
    }

    std::vector<std::string> allLines;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            allLines.push_back(line);
        }
    }
    file.close();

    if (allLines.empty()) {
        std::cerr << "Plik jest pusty lub niepoprawny." << std::endl;
        return "FAIL";
    }

    size_t total = allLines.size();
    size_t mid = total / 2;

    part1.reserve(mid);
    part2.reserve(total - mid);

    std::thread t1([&]() {
        for (size_t i = 0; i < mid; ++i) {
            part1.push_back(allLines[i]);
        }
        });

    std::thread t2([&]() {
        for (size_t i = mid; i < total; ++i) {
            part2.push_back(allLines[i]);
        }
        });

    t1.join();
    t2.join();

    //std::cout << "[DEBUG] Linie w part1: " << part1.size() << ", part2: " << part2.size() << std::endl;

    return "OK";
}

StockMarket::StockMarket() {
    this->filepath = std::filesystem::absolute("resources/stock_info.txt");
  //  this->loadStocks();
}

float StockMarket::getPriceForSymbol(const std::string& symbol) const
{
    for (const auto& stock : stocks) {
        if (stock.getSymbol() == symbol) {
            return stock.getCurrentPrice();
        }
    }
    return 0.0f;
}


void StockMarket::update() {
    std::vector<std::string> symbols;
    for (const auto& stock : stocks)
        symbols.push_back(stock.getSymbol());

    auto prices = getPricesFromYahoo(symbols);

    for (auto& stock : stocks) {
        auto it = prices.find(stock.getSymbol());
        if (it != prices.end()) {
            stock = Stock(stock.getSymbol(), stock.getName(), it->second, stock.getCurrentPrice());
        }
    }
}

const std::vector<Stock>& StockMarket::getStocks() const {
    return stocks;
}

Stock* StockMarket::findStockBySymbol(const std::string& symbol) {
    for (auto& stock : stocks) {
        if (stock.getSymbol() == symbol) {
            return &stock;
        }
    }
    return nullptr;
}