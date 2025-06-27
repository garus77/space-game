// menuState.cpp
#include "gameStates.h"
#include "stateManager.h"

MenuState::MenuState(StateManager &m, sf::RenderWindow *w) : states(m), window(w) {}

void MenuState::onEnter()
{
    // e.g. setup menu items
}

void MenuState::onExit()
{
    // cleanup if needed
}

void MenuState::handleEvent(const sf::Event &e)
{
    /*
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter)
    {
        // switch to PlayState when Enter is pressed
        states.changeState<PlayState>(states, window);
    }
    */
}

void MenuState::update(float dt) { /* maybe animate */ }

void MenuState::draw(sf::RenderWindow &w)
{
    w.clear();
    // draw menu…
    w.display();
}
