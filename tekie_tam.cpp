#include "tekie_tam.h"

tekie_tam::tekie_tam(const std::string& message, const std::string& fontPath, unsigned int fontSize) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Nie uda³o siê za³adowaæ czcionki z: " << fontPath << std::endl;
        return;
    }

    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(fontSize);
    text.setFillColor(sf::Color::White);
    text.setPosition(10.f, 10.f); // Lewy górny róg z niewielkim marginesem
}

void tekie_tam::draw(sf::RenderWindow& window) {
    window.draw(text);
}