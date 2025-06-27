// settings.h
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

struct WindowSettings
{
    unsigned width;
    unsigned height;
    bool fullscreen;
    bool vsync;
    unsigned frameLimit;

    // load from the settings.json file (throws on error)
    static WindowSettings loadFromFile();

    // create and return a RenderWindow configured with these settings
    std::unique_ptr<sf::RenderWindow> makeWindow() const;
};