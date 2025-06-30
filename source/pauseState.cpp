// pauseState.cpp
#include "stateManager.h"

void PauseState::onEnter()
{
    // e.g. setup menu items
    // 1) Grab the font (throws if missing)
    const sf::Font &font = m_resources.getFont("arial");

    // 2) Configure sf::Text
    m_pauseText.setFont(font);
    m_pauseText.setString("PAUSED");
    m_pauseText.setCharacterSize(48); // in pixels
    m_pauseText.setFillColor(sf::Color::Blue);
    m_pauseText.setOutlineColor(sf::Color::Black);
    m_pauseText.setOutlineThickness(-1.0f);
    // center it at the top of the window:
    sf::Vector2u sz = m_window->getSize();
    auto bounds = m_pauseText.getLocalBounds();
    m_pauseText.setPosition((sz.x - bounds.width) / 2.f - bounds.left, 100.f);
}

void PauseState::onExit()
{
    // m_window->setTitle("NOT PauseState");
    // cleanup if needed
    // m_resources.unloadTexture("menu_background");
}

void PauseState::onResize(sf::Vector2u newSize)
{
    // m_ui.resizeAll(newSize);
}

void PauseState::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        sf::Keyboard::Key key = event.key.code;
        if (key == sf::Keyboard::Escape)
        {
            m_states.popState();
        }
        if (key == sf::Keyboard::B)
        {
            m_pauseText.setFillColor(sf::Color::Magenta);
        }
        if (key == sf::Keyboard::C)
        {
            m_pauseText.setFillColor(sf::Color::Green);
        }
    }
}

void PauseState::update(float dt) { /* maybe animate */ }

void PauseState::draw(sf::RenderWindow &window)
{
    // draw menu…
    window.draw(m_pauseText);
}
