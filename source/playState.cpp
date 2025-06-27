// playState.cpp
#include "gameStates.h"
#include "stateManager.h"

PlayState::PlayState(StateManager &m, sf::RenderWindow *w) : m_states(m), m_window(w) {}

void PlayState::onEnter()
{
    // m_window->setTitle("PLAYSTATE");
    // e.g. setup menu items
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
        m_states.changeState<MenuState>(m_states, m_window);
    }
}

void PlayState::update(float dt) { /* maybe animate */ }

void PlayState::draw(sf::RenderWindow &w)
{
    w.clear(sf::Color::Blue);
    // draw menu…
    w.display();
}
