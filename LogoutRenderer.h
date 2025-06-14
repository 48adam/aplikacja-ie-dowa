#pragma once

// LogoutRenderer.h
class LogoutRenderer {
public:
    virtual void render(sf::RenderTarget& target) = 0;
    virtual bool handleClick(const sf::Vector2f& pos) = 0;
    virtual ~LogoutRenderer() = default;
};
