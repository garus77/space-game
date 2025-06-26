#pragma once
#include <SFML/Graphics.hpp>

class Game
{
  public:
    Game();
    void run();

  private:
    void handleEvents();
    void update();
    void render();

  private:
    sf::RenderWindow m_window;
};

Game::Game() {}

void Game::run()
{
    m_window.create(sf::VideoMode(800, 600), "Space Game", sf::Style::Default);
    sf::Clock clock;
    while (m_window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        handleEvents();
        if (!m_window.isOpen()) break;
        update();
        render();
    }
}

void Game::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) m_window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) m_window.close();
    }
}

void Game::update()
{
    // update game
}

void Game::render()
{
    m_window.clear();
    // render frame

    //
    m_window.display();
}