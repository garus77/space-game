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

    WindowSettings s;
    s.width = j.value("windowWidth", s.width);
    s.height = j.value("windowHeight", s.height);
    s.fullscreen = j.value("fullscreen", s.fullscreen);
    s.vsync = j.value("vsync", s.vsync);
    s.frameLimit = j.value("frameLimit", s.frameLimit);
    return s;
}

std::unique_ptr<sf::RenderWindow> WindowSettings::makeWindow() const
{
    sf::VideoMode mode = fullscreen ? sf::VideoMode::getDesktopMode() : sf::VideoMode(width, height);

    auto style = fullscreen ? sf::Style::Fullscreen : sf::Style::Close;

    auto window = std::make_unique<sf::RenderWindow>(mode, "Galaxus", style);
    window->setVerticalSyncEnabled(vsync);
    if (frameLimit > 0) window->setFramerateLimit(frameLimit);

    sf::Image icon;
    if (!icon.loadFromFile("resources/textures/icon.png")) throw std::runtime_error("Failed to load window icon");

    auto sz = icon.getSize();
    window->setIcon(sz.x, sz.y, icon.getPixelsPtr());
    return window;
}