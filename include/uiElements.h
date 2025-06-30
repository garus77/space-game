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

    virtual void resize(sf::Vector2u newSize) = 0;

    // Visibility / interactivity toggles
    void setVisible(bool v) { m_visible = v; }
    bool isVisible() const { return m_visible; }
    void setEnabled(bool e) { m_enabled = e; }
    bool isEnabled() const { return m_enabled; }

  protected:
    bool m_visible = true;
    bool m_enabled = true;
    sf::Vector2f m_anchorPos = {0.f, 0.f};
    sf::Vector2f m_anchorSize = {0.f, 0.f};

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
    Button(const sf::Font &font, const std::string &text, std::function<void()> callback) : m_callback(std::move(callback))
    {
        // configure the box
        m_box.setFillColor(sf::Color(100, 100, 100));
        m_box.setOutlineColor(sf::Color::Black);
        m_box.setOutlineThickness(-2.f);

        // configure the text
        m_label.setFont(font);
        m_label.setString(text);
        m_label.setCharacterSize(24);
        m_label.setOutlineThickness(-1.f);
        m_label.setOutlineColor(sf::Color::Black);
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

    void setRelativeBounds(sf::Vector2f newAnchor, sf::Vector2f newAnchorSize)
    {
        m_anchorPos = newAnchor;
        m_anchorSize = newAnchorSize;
        // you could immediately call resize(currentWindowSize),
        // or wait until the next onResize
    }

    void resize(sf::Vector2u newSize) override
    {
        float px = m_anchorPos.x * newSize.x;
        float py = m_anchorPos.y * newSize.y;
        float w = m_anchorSize.x * newSize.x;
        float h = m_anchorSize.y * newSize.y;
        setPosition(px, py);
        m_box.setSize({w, h});
        centerLabel();
    }

  protected:
    // draw the button (box + label)
    void draw(sf::RenderTarget &renderTarget, sf::RenderStates states) const override
    {
        if (!m_visible) return;
        states.transform *= getTransform();
        renderTarget.draw(m_box, states);
        renderTarget.draw(m_label, states);
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

class SpriteElement : public UIElement
{
  public:
    // tex: the texture to display
    // callback: optional on-click handler
    SpriteElement(const sf::Texture &tex) { m_sprite.setTexture(tex); }

    bool handleEvent(const sf::Event &ev, const sf::RenderWindow &window) override { return false; }

    void update(float) override {}

    // Set relative anchor & size (fractions of window dimensions)
    void setRelativeBounds(sf::Vector2f anchor, sf::Vector2f size)
    {
        m_anchorPos = anchor;
        m_anchorSize = size;
    }

    void resize(sf::Vector2u newSize) override
    {
        float px = m_anchorPos.x * newSize.x;
        float py = m_anchorPos.y * newSize.y;
        float w = m_anchorSize.x * newSize.x;
        float h = m_anchorSize.y * newSize.y;
        setPosition(px, py);
        // scale sprite to fit the designated area
        auto texSize = m_sprite.getTexture()->getSize();
        m_sprite.setScale(w / texSize.x, h / texSize.y);
    }

  protected:
    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override
    {
        if (!m_visible) return;
        states.transform *= getTransform();
        rt.draw(m_sprite, states);
    }

    sf::FloatRect getLocalBounds() const override { return m_sprite.getLocalBounds(); }

  private:
    sf::Sprite m_sprite;
};

// Label: displays text at a relative position; font size stays constant
class Label : public UIElement
{
  public:
    // font: loaded sf::Font reference
    // text: string to display
    // charSize: pixel size of characters (remains fixed)
    Label(const sf::Font &font, const std::string &text, unsigned charSize = 24)
    {
        m_text.setFont(font);
        m_text.setString(text);
        m_text.setCharacterSize(charSize);
    }

    bool handleEvent(const sf::Event &, const sf::RenderWindow &) override
    {
        // labels are not interactive by default
        return false;
    }

    void update(float) override {}

    // Set only relative position; size unchanged
    void setRelativePosition(sf::Vector2f anchor) { m_anchorPos = anchor; }

    void resize(sf::Vector2u newSize) override
    {
        float px = m_anchorPos.x * newSize.x;
        float py = m_anchorPos.y * newSize.y;
        setPosition(px, py);
    }

  protected:
    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override
    {
        if (!m_visible) return;
        states.transform *= getTransform();
        rt.draw(m_text, states);
    }

    sf::FloatRect getLocalBounds() const override { return m_text.getLocalBounds(); }

  private:
    sf::Text m_text;
};