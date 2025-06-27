// gameStates.h
#pragma once
#include <SFML/Graphics.hpp>

class StateManager;

class GameState
{
  public:
    virtual ~GameState() = default;

    // called once when this state becomes active
    virtual void onEnter() = 0;
    // called once when this state is removed / replaced
    virtual void onExit() = 0;

    // event‐handling, update & draw
    virtual void handleEvent(const sf::Event &event) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};

class MenuState : public GameState
{
  public:
    MenuState(StateManager &manager, sf::RenderWindow *window);
    void onEnter() override;
    void onExit() override;
    void handleEvent(const sf::Event &e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow &w) override;

  private:
    StateManager &states;
    sf::RenderWindow *window;
    // … menu GUI, buttons, etc.
};