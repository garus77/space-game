// settings.h
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

struct WindowSettings
{
    unsigned width = 800;
    unsigned height = 600;
    bool fullscreen = false;
    bool vsync = false;
    unsigned frameLimit = 60;

    // loadFromFile is a *static* factory that you call exactly once
    static WindowSettings loadFromFile();

    // makeWindow never re-reads JSON; it just uses these members
    std::unique_ptr<sf::RenderWindow> makeWindow() const;
};
