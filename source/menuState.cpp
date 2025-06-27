// menuState.cpp
#include "gameStates.h"
#include "stateManager.h"

MenuState::MenuState(StateManager &m, sf::RenderWindow *w) : m_states(m), m_window(w) {}

void MenuState::onEnter()
{
    // m_window->setTitle("MENUSTATE");
    // e.g. setup menu items
}

void MenuState::onExit()
{
    // m_window->setTitle("NOT MENUSTATE");
    // cleanup if needed
}

void MenuState::handleEvent(const sf::Event &e)
{
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter)
    {
        // switch to PlayState when Enter is pressed
        m_states.changeState<PlayState>(m_states, m_window);
    }
}

void MenuState::update(float dt) { /* maybe animate */ }

void MenuState::draw(sf::RenderWindow &w)
{
    w.clear(sf::Color::Green);
    // draw menu…
    w.display();
}
