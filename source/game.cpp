// game.cpp
#include "game.h"

Game::Game() : m_windowSettings(WindowSettings::loadFromFile()), m_window(m_windowSettings.makeWindow())
{
    // init
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
            m_windowSettings.fullscreen = !m_windowSettings.fullscreen;
            m_window.reset();
            m_window = m_windowSettings.makeWindow();
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