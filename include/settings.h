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

    // Loads window settings from "settings.json". Called on game constructor
    static WindowSettings loadFromFile();

    // makeWindow never re-reads JSON; it just uses the window setting's members
    std::unique_ptr<sf::RenderWindow> makeWindow() const;
};
