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
    std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(fullscreen ? sf::VideoMode::getDesktopMode() : sf::VideoMode(width, height), "Galaxus", fullscreen ? sf::Style::Fullscreen : sf::Style::Close);

    window->setVerticalSyncEnabled(vsync);
    if (frameLimit > 0) window->setFramerateLimit(frameLimit);

    sf::Image icon;
    if (!icon.loadFromFile("resources/textures/icon.png")) throw std::runtime_error("Failed to load window icon");
    auto size = icon.getSize();
    window->setIcon(size.x, size.y, icon.getPixelsPtr());

    return window;
}
