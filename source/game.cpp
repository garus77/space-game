#include "game.h"
#include "settings.h"

Game::Game() : m_settings(WindowSettings::loadFromFile()) { m_window = m_settings.makeWindow(); }

void Game::run()
{
    // m_window.create(sf::VideoMode(800, 600), "Galaxus", sf::Style::Default);

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
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) m_window->close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11)
        {
            m_settings.fullscreen = !m_settings.fullscreen;
            m_window = m_settings.makeWindow();
        }
    }
}

void Game::update(float deltaTime)
{
    // update game
}

void Game::render()
{
    m_window->clear();
    // render frame

    //
    m_window->display();
}