// stateManager.h
#pragma once
#include "gameStates.h"
#include <memory>
#include <utility> // for std::forward
#include <vector>

class StateManager
{
  public:
    // Replace current state
    template <typename State, typename... Args> void changeState(Args &&...args)
    {
        if (!states.empty())
        {
            states.back()->onExit();
            states.pop_back();
        }
        pushState<State>(std::forward<Args>(args)...);
    }

    // Push a new state on top
    template <typename State, typename... Args> void pushState(Args &&...args)
    {
        states.emplace_back(std::make_unique<State>(std::forward<Args>(args)...));
        states.back()->onEnter();
    }

    // Pop top state
    void popState()
    {
        if (!states.empty())
        {
            states.back()->onExit();
            states.pop_back();
            if (!states.empty()) states.back()->onEnter();
        }
    }

    // Handle events for top state
    void handleEvent(const sf::Event &event)
    {
        if (!states.empty()) states.back()->handleEvent(event);
    }

    // Update for top state
    void update(float dt)
    {
        if (!states.empty()) states.back()->update(dt);
    }

    // Render for top state
    void draw(sf::RenderWindow &window)
    {
        if (!states.empty()) states.back()->draw(window);
    }

    // Sets the render window for all game states
    void setRenderWindow(sf::RenderWindow *window)
    {
        for (auto &s : states)
            s->setRenderWindow(window);
    }

  private:
    // Game states owned by this manager
    std::vector<std::unique_ptr<GameState>> states;
};
