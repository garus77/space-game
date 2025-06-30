// menuState.cpp
#include "stateManager.h"

void MenuState::onEnter()
{
    m_window->setTitle("MENUSTATE");
    // e.g. setup menu items

    const sf::Texture &bgTex = m_resources.getTexture("menu_background");
    auto &bgSprite = m_ui.create<SpriteElement>(bgTex);
    bgSprite.setRelativeBounds({0.f, 0.f}, {1.f, 1.f});

    const sf::Font &font = m_resources.getFont("arial");

    auto &playBtn = m_ui.create<Button>(font, "Play", [this] { m_states.changeState<PlayState>(m_states, m_window, m_resources); });
    playBtn.setRelativeBounds({.1f, .1f}, {.1f, .1f});

    auto &testLabel = m_ui.create<Label>(font, "TESTING LABEL", 36);
    testLabel.setRelativePosition({.5f, .5f});

    onResize(m_window->getSize());
}

void MenuState::onExit()
{
    // m_window->setTitle("NOT MENUSTATE");
    // cleanup if needed
    m_resources.unloadTexture("menu_background");
}

void MenuState::onResize(sf::Vector2u newSize) { m_ui.resizeAll(newSize); }

void MenuState::handleEvent(const sf::Event &event)
{
    if (m_ui.handleEvent(event, *m_window)) return;
    if (event.type == sf::Event::KeyPressed)
    {
        sf::Keyboard::Key key = event.key.code;
        if (key == sf::Keyboard::Enter && m_states.top() == this)
        {
            // switch to PlayState when Enter is pressed
            m_states.changeState<PlayState>(m_states, m_window, m_resources);
        }
        /*if (key == sf::Keyboard::A)
        {
            m_titleText.setFillColor(sf::Color::Red);
        }
        if (key == sf::Keyboard::S)
        {
            m_titleText.setFillColor(sf::Color::Green);
        }*/
    }
}

void MenuState::update(float dt) { m_ui.update(dt); }

void MenuState::draw(sf::RenderWindow &window)
{
    // draw menu…
    m_ui.draw(window);
}
