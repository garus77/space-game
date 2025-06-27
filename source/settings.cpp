// settings.cpp
#include "settings.h"
#include "json.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>

using json = nlohmann::json;

WindowSettings WindowSettings::loadFromFile()
{
    std::ifstream in{"settings.json"};
    if (!in) throw std::runtime_error("Could not open settings.json");

    json j;
    in >> j;

    WindowSettings windowSettings;
    windowSettings.width = j.value("windowWidth", 800u);
    windowSettings.height = j.value("windowHeight", 600u);
    windowSettings.fullscreen = j.value("fullscreen", false);
    windowSettings.vsync = j.value("vsync", false);
    windowSettings.frameLimit = j.value("frameLimit", 60u);
    return windowSettings;
}

std::unique_ptr<sf::RenderWindow> WindowSettings::makeWindow() const
{
    std::unique_ptr<sf::RenderWindow> window;
    if (fullscreen)
    {
        window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "Galaxus", sf::Style::Fullscreen);
    }
    else
    {
        window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Galaxus", sf::Style::Close);
    }

    window->setVerticalSyncEnabled(vsync);
    if (frameLimit > 0) window->setFramerateLimit(frameLimit);

    return window;
}
