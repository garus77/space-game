// uiElement.h
#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class UIElement : public sf::Drawable, public sf::Transformable
{
  public:
    virtual ~UIElement() = default;

    // Called each frame to update animations, hover‐states, etc.
    virtual void update(float dt) = 0;

    // Called for every SFML event; return true if consumed
    virtual bool handleEvent(const sf::Event &ev, const sf::RenderWindow &window) = 0;

    // If you need to know your clickable area, override this
    virtual sf::FloatRect getGlobalBounds() const
    {
        // default: use the local bounds of the shape/text you drew,
        // transformed by your Transformable
        return getTransform().transformRect(getLocalBounds());
    }

    // Visibility / interactivity toggles
    void setVisible(bool v) { m_visible = v; }
    bool isVisible() const { return m_visible; }
    void setEnabled(bool e) { m_enabled = e; }
    bool isEnabled() const { return m_enabled; }

  protected:
    bool m_visible = true;
    bool m_enabled = true;

    // Subclasses must implement draw; check m_visible there if desired
    virtual void draw(sf::RenderTarget &rt, sf::RenderStates states) const override = 0;

    // Helper: subclasses can implement getLocalBounds() to return
    // their own bounding box in local coordinates
    virtual sf::FloatRect getLocalBounds() const = 0;
};

class Button : public UIElement
{
  public:
    // size: button dimensions
    // font: reference to loaded sf::Font
    // text: label shown on the button
    // callback: function invoked when the button is clicked
    Button(const sf::Vector2f &size, const sf::Font &font, const std::string &text, std::function<void()> callback) : m_callback(std::move(callback))
    {
        // configure the box
        m_box.setSize(size);
        m_box.setFillColor(sf::Color(100, 100, 100));
        m_box.setOutlineColor(sf::Color::White);
        m_box.setOutlineThickness(2.f);

        // configure the text
        m_label.setFont(font);
        m_label.setString(text);
        m_label.setCharacterSize(24);
        centerLabel();
    }

    // handle mouse click events
    bool handleEvent(const sf::Event &ev, const sf::RenderWindow &window) override
    {
        if (!m_enabled || !m_visible) return false;

        if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left)
        {
            // map pixel to world coords and test hit
            sf::Vector2f pt = window.mapPixelToCoords({ev.mouseButton.x, ev.mouseButton.y});
            if (getTransform().transformRect(m_box.getGlobalBounds()).contains(pt))
            {
                if (m_callback) m_callback();
                return true;
            }
        }
        return false;
    }

    // update per frame (optional, for hover/click animations)
    void update(float) override {}

  protected:
    // draw the button (box + label)
    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override
    {
        if (!m_visible) return;
        states.transform *= getTransform();
        rt.draw(m_box, states);
        rt.draw(m_label, states);
    }

    // provide local bounds for hit testing
    sf::FloatRect getLocalBounds() const override { return m_box.getLocalBounds(); }

  private:
    // center label within the box
    void centerLabel()
    {
        auto b = m_label.getLocalBounds();
        float x = (m_box.getSize().x - b.width) / 2.f - b.left;
        float y = (m_box.getSize().y - b.height) / 2.f - b.top;
        m_label.setPosition(x, y);
    }

    sf::RectangleShape m_box;
    sf::Text m_label;
    std::function<void()> m_callback;
};