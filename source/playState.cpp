// playState.cpp
#include "stateManager.h"

void PlayState::onEnter()
{
    // m_window->setTitle("PLAYSTATE");
    // e.g. setup items
}

void PlayState::onExit()
{
    // cleanup if needed
}

void PlayState::handleEvent(const sf::Event &e)
{
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter)
    {
        // switch to MenuState when Enter is pressed
        m_states.changeState<MenuState>(m_states, m_window, m_resources);
    }
}

void PlayState::update(float dt) { /* maybe animate */ }

void PlayState::draw(sf::RenderWindow &w)
{
    w.clear(sf::Color::Blue);
    // draw...
    w.display();
}
