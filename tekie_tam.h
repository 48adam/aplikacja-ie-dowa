#pragma once
#include<string>
#include<iostream>
#include <SFML/Graphics.hpp>

class tekie_tam
{
private:
public:
    tekie_tam(const std::string& message, const std::string& fontPath, unsigned int fontSize = 16);

    void draw(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text text;

};

