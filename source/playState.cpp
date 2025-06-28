// playState.cpp
#include "stateManager.h"

void PlayState::onEnter()
{
    // m_window->setTitle("PLAYSTATE");
    // e.g. setup items
    m_playa.setFillColor(sf::Color::Red);
    m_playa.setOutlineColor(sf::Color::Black);
    m_playa.setOutlineThickness(-1.0f);
    float radius = 10.0f;
    m_playa.setOrigin(radius, radius);
    m_playa.setRadius(radius);
    m_playa.setPosition(300.0f, 400.0f);
}

void PlayState::onExit()
{
    // cleanup if needed
}

void PlayState::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        sf::Keyboard::Key key = event.key.code;
        if (key == sf::Keyboard::Enter && m_states.top() == this)
        {
            // switch to MenuState when Enter is pressed
            m_states.changeState<MenuState>(m_states, m_window, m_resources);
        }
        if (key == sf::Keyboard::Escape)
        {
            m_states.pushState<PauseState>(m_states, m_window, m_resources);
        }
    }
}

void PlayState::update(float dt)
{
    // update
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_playa.setPosition(m_playa.getPosition() + sf::Vector2f(100.0f, 0.0f) * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) m_playa.setPosition(m_playa.getPosition() + sf::Vector2f(-100.0f, 0.0f) * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) m_playa.setPosition(m_playa.getPosition() + sf::Vector2f(0.0f, 100.0f) * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) m_playa.setPosition(m_playa.getPosition() + sf::Vector2f(0.0f, -100.0f) * dt);
}

void PlayState::draw(sf::RenderWindow &window)
{
    // draw...
    window.draw(m_playa);
}
