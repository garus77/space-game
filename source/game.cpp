// game.cpp
#include "game.h"

Game::Game() : m_windowSettings(WindowSettings::loadFromFile())
{
    // init
}

void Game::recreateWindow()
{
    // destroy old and build new
    m_window = m_windowSettings.makeWindow();
    // tell your states about the new window pointer, if they cache it:
    m_states.setRenderWindow(m_window.get());
    m_states.handleResize(m_window->getSize());
}

void Game::run()
{
    // 1) Create window before entering the loop
    recreateWindow();

    // 2) Now that the window exists, push your initial state
    m_states.pushState<MenuState>(m_states, m_window.get(), m_resources);

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
        if (event.type == sf::Event::Resized)
        {
            m_states.handleResize(sf::Vector2u(event.size.width, event.size.height));
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11)
        {
            m_windowSettings.fullscreen = !m_windowSettings.fullscreen;
            recreateWindow();
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
    m_window->clear(sf::Color::Black);
    m_states.draw(*m_window);
    m_window->display();
}