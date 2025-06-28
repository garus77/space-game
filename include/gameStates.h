// gameStates.h
#pragma once
#include "resourceManager.h"
#include "uiManager.h"
#include <SFML/Graphics.hpp>

class StateManager;

// Base state for all other states
class GameState
{
  public:
    virtual ~GameState() = default;

    GameState(StateManager &states, sf::RenderWindow *window, ResourceManager &resources) : m_states(states), m_window(window), m_resources(resources) {}

    // Called once when this state becomes active
    virtual void onEnter() = 0;
    // Called once when this state is removed / replaced
    virtual void onExit() = 0;

    // Event‐handling for this game state
    virtual void handleEvent(const sf::Event &event) = 0;
    // Updating for this game state
    virtual void update(float dt) = 0;
    // Rendering for this game state
    virtual void draw(sf::RenderWindow &window) = 0;
    // Handling resize
    // virtual void onResize(sf::Vector2u newSize) = 0;

    // Sets render window for this game state (only used by state manager)
    void setRenderWindow(sf::RenderWindow *newWindow) { m_window = newWindow; }

  protected:
    // State manager reference inherited by all game states
    StateManager &m_states;
    // Window pointer inherited by all game states
    sf::RenderWindow *m_window;
    // Resource manager reference inherited by all game states
    ResourceManager &m_resources;
};

class MenuState : public GameState
{
  public:
    MenuState(StateManager &states, sf::RenderWindow *window, ResourceManager &resources) : GameState(states, window, resources) {}
    void onEnter() override;
    void onExit() override;
    void handleEvent(const sf::Event &event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;
    // void onResize(sf::Vector2u newSize) override;

  private:
    // … menu GUI, buttons, etc. menu elements
    sf::Text m_titleText;
    sf::Sprite m_backgroundSprite;
    UIManager m_ui;
};

class PauseState : public GameState
{
  public:
    PauseState(StateManager &states, sf::RenderWindow *window, ResourceManager &resources) : GameState(states, window, resources) {}
    void onEnter() override;
    void onExit() override;
    void handleEvent(const sf::Event &event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;
    // void onResize(sf::Vector2u newSize) override;

  private:
    // … menu GUI, buttons, etc. menu elements
    sf::Text m_pauseText;
    sf::Sprite m_backgroundSprite;
};

class PlayState : public GameState
{
  public:
    PlayState(StateManager &states, sf::RenderWindow *window, ResourceManager &resources) : GameState(states, window, resources) {}
    void onEnter() override;
    void onExit() override;
    void handleEvent(const sf::Event &event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;
    // void onResize(sf::Vector2u newSize) override;

  private:
    // … menu GUI, buttons, etc. game elements
    sf::CircleShape m_playa;
};