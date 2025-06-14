#pragma once
#include "okno.h"
#include "LogoutRenderer.h"
// StandardLogoutButton.h
class StandardLogoutButton : public LogoutRenderer {
private:
    sf::RectangleShape button;
    sf::Text label;
    sf::FloatRect bounds;
    sf::Font& font;

public:
    StandardLogoutButton(sf::Font& f, float x, float y) : font(f) {
        button.setSize({ 120.f, 30.f });
        button.setPosition(x, y);
        button.setFillColor(sf::Color::Red);

        label.setFont(font);
        label.setString("Wyloguj");
        label.setCharacterSize(16);
        label.setFillColor(sf::Color::White);
        label.setPosition(x + 20.f, y + 5.f);

        bounds = button.getGlobalBounds();
    }

    void render(sf::RenderTarget& target) override {
        target.draw(button);
        target.draw(label);
    }

    bool handleClick(const sf::Vector2f& pos) override {
        return bounds.contains(pos);
    }
};
