// uiManager.h
#pragma once
#include "uiElements.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <utility>
#include <vector>

class UIManager
{
  public:
    // Create & store a widget of type Widget, forwarding ctor args.
    // Returns a reference so you can call setPosition(), etc.
    template <typename Widget, typename... Args> Widget &create(Args &&...args)
    {
        auto widget = std::make_unique<Widget>(std::forward<Args>(args)...);
        Widget &ref = *widget;
        widgets.emplace_back(std::move(widget));
        return ref;
    }

    // Remove all widgets
    void clear() { widgets.clear(); }

    // Give each widget a chance to eat the event (topmost first)
    bool handleEvent(const sf::Event &event, const sf::RenderWindow &window)
    {
        for (auto it = widgets.rbegin(); it != widgets.rend(); it++)
            if ((*it)->handleEvent(event, window)) return true;
        return false;
    }

    // Per-frame updates (hover animations, blinking cursors, etc.)
    void update(float dt)
    {
        for (auto &widget : widgets)
            widget->update(dt);
    }

    // Draw in insertion order (bottom -> top)
    void draw(sf::RenderWindow &window)
    {
        for (auto &widget : widgets)
            window.draw(*widget);
    }

  private:
    std::vector<std::unique_ptr<UIElement>> widgets;
};
