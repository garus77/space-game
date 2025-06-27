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

    void popState()
    {
        if (!states.empty())
        {
            states.back()->onExit();
            states.pop_back();
            if (!states.empty()) states.back()->onEnter();
        }
    }

    void handleEvent(const sf::Event &e)
    {
        if (!states.empty()) states.back()->handleEvent(e);
    }

    void update(float dt)
    {
        if (!states.empty()) states.back()->update(dt);
    }

    void draw(sf::RenderWindow &w)
    {
        if (!states.empty()) states.back()->draw(w);
    }

  private:
    std::vector<std::unique_ptr<GameState>> states;
};
