// game.cpp
#include "game.h"

Game::Game() : m_settings(WindowSettings::loadFromFile())
{
    m_window = m_settings.makeWindow();
    sf::Image icon;
    if (!icon.loadFromFile("resources/textures/icon.png")) throw std::runtime_error("Failed to load window icon");
    auto size = icon.getSize();
    m_window->setIcon(size.x, size.y, icon.getPixelsPtr());
    m_states.pushState<MenuState>(m_states, m_window.get());
}

void Game::run()
{
    sf::Clock clock;
    while (m_window->isOpen())
    {
        float dt = clock.restart().asSeconds();
        handleEvents();
        if (!m_window->isOpen()) break;
        update(dt);
        render();
    }
}

void Game::handleEvents()
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) m_window->close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11)
        {
            m_settings.fullscreen = !m_settings.fullscreen;
            m_window = m_settings.makeWindow();
        }
        m_states.handleEvent(event);
    }
}

void Game::update(float deltaTime)
{
    // update game
    m_states.update(deltaTime);
}

void Game::render()
{
    // render
    m_states.draw(*m_window);
}