// menuState.cpp
#include "stateManager.h"

void MenuState::onEnter()
{
    m_window->setTitle("MENUSTATE");
    // e.g. setup menu items
    // 1) Grab the font (throws if missing)
    const sf::Font &font = m_resources.getFont("arial");

    // 2) Configure sf::Text
    m_titleText.setFont(font);
    m_titleText.setString("GALAXUS");
    m_titleText.setCharacterSize(48); // in pixels
    m_titleText.setFillColor(sf::Color::Blue);
    m_titleText.setOutlineColor(sf::Color::Black);
    m_titleText.setOutlineThickness(-1.0f);
    // center it at the top of the window:
    sf::Vector2u sz = m_window->getSize();
    auto bounds = m_titleText.getLocalBounds();
    m_titleText.setPosition((sz.x - bounds.width) / 2.f - bounds.left, 50.f);

    const sf::Texture &bgTex = m_resources.getTexture("menu_background");
    m_backgroundSprite.setTexture(bgTex);
    auto winSize = m_window->getSize();
    auto texSize = bgTex.getSize();
    m_backgroundSprite.setScale(float(winSize.x) / texSize.x, float(winSize.y) / texSize.y);

    auto &playBtn = m_ui.create<Button>(font, "Play", [this] { m_states.changeState<PlayState>(m_states, m_window, m_resources); });
    playBtn.setRelativeBounds({.1f, .1f}, {.1f, .1f});

    onResize(m_window->getSize());
}

void MenuState::onExit()
{
    // m_window->setTitle("NOT MENUSTATE");
    // cleanup if needed
    // m_resources.unloadTexture("menu_background");
}

void MenuState::onResize(sf::Vector2u newSize)
{
    m_ui.resizeAll(newSize);
    const sf::Texture &bgTex = m_resources.getTexture("menu_background");
    auto texSize = bgTex.getSize();
    m_backgroundSprite.setScale({float(newSize.x) / texSize.x, float(newSize.y) / texSize.y});
}

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
        if (key == sf::Keyboard::A)
        {
            m_titleText.setFillColor(sf::Color::Red);
        }
        if (key == sf::Keyboard::S)
        {
            m_titleText.setFillColor(sf::Color::Green);
        }
    }
}

void MenuState::update(float dt) { /* maybe animate */ }

void MenuState::draw(sf::RenderWindow &window)
{
    // draw menu…
    window.draw(m_backgroundSprite);
    window.draw(m_titleText);
    m_ui.draw(window);
}
