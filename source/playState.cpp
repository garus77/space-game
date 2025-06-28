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

void PlayState::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
    {
        // switch to MenuState when Enter is pressed
        m_states.changeState<MenuState>(m_states, m_window, m_resources);
    }
}

void PlayState::update(float dt) { /* maybe animate */ }

void PlayState::draw(sf::RenderWindow &window)
{
    window.clear(sf::Color::Blue);
    // draw...
    window.display();
}
