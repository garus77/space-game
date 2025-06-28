// gameStates.h
#pragma once
#include <SFML/Graphics.hpp>

class StateManager;

class GameState
{
  public:
    virtual ~GameState() = default;

    GameState(StateManager &manager, sf::RenderWindow *window) : m_states(manager), m_window(window) {}

    // called once when this state becomes active
    virtual void onEnter() = 0;
    // called once when this state is removed / replaced
    virtual void onExit() = 0;

    // event‐handling for this game state
    virtual void handleEvent(const sf::Event &event) = 0;
    // updating for this game state
    virtual void update(float dt) = 0;
    // rendering for this game state
    virtual void draw(sf::RenderWindow &window) = 0;

    // sets render window for this game state (only used by state manager)
    void setRenderWindow(sf::RenderWindow *newWindow) { m_window = newWindow; }

  protected:
    StateManager &m_states;
    sf::RenderWindow *m_window;
};

class MenuState : public GameState
{
  public:
    MenuState(StateManager &manager, sf::RenderWindow *window) : GameState(manager, window) {}
    void onEnter() override;
    void onExit() override;
    void handleEvent(const sf::Event &e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow &w) override;

  private:
    // … menu GUI, buttons, etc. menu elements
};

class PlayState : public GameState
{
  public:
    PlayState(StateManager &manager, sf::RenderWindow *window) : GameState(manager, window) {}
    void onEnter() override;
    void onExit() override;
    void handleEvent(const sf::Event &e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow &w) override;

  private:
    // … menu GUI, buttons, etc. game elements
};