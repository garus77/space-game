// stateManager.h
#pragma once
#include "gameStates.h"
#include <memory>
#include <utility> // for std::forward
#include <vector>

class StateManager
{
  public:
    // Replace top state
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

    // Change bottom of the stack, exiting from the others in top->bottom order
    template <typename State, typename... Args> void changeBaseState(Args &&...args)
    {
        // 1) Call onExit() on every state, from top -> bottom
        for (auto it = states.rbegin(); it != states.rend(); ++it)
            (*it)->onExit();

        // 2) Clear out the vector entirely
        states.clear();

        // 3) Push the new base state (will call its onEnter())
        pushState<State>(std::forward<Args>(args)...);
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

    GameState *top() { return states.empty() ? nullptr : states.back().get(); }
    bool empty() const { return states.empty(); }

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

    // Render for states in order from bottom to top
    void draw(sf::RenderWindow &window)
    {
        if (!states.empty())
            for (auto &s : states)
                s->draw(window);
    }

    // Sets the render window for all game states
    void setRenderWindow(sf::RenderWindow *window)
    {
        for (auto &s : states)
            s->setRenderWindow(window);
    }

    void handleResize(sf::Vector2u newSize)
    {
        for (auto &s : states)
            s->onResize(newSize);
    }

  private:
    // Game states owned by this manager
    std::vector<std::unique_ptr<GameState>> states;
};
