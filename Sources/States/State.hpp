#pragma once

#include "UI/Converter.hpp"
#include "UI/Micro/Button.hpp"

#include "Systems/Settings.hpp"

class State;

// \brief A Data Context for State, Always pass this to every state
struct Context
{
    // Main Components
    sf::RenderWindow* Window;
    sf::Event* Event;
    std::stack<State*>* States;

    Settings* Settings;

    float GridSize;

    // Font
    sf::Font MainFont;
    sf::Font SecondFont;

    // Coloring
    sf::Color MainColor;
    sf::Color SecondColor;
};

// \brief Abstract class of States, Never use this for Implementation!
class State
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    State(Context* I_Ctx);
    virtual ~State();

    /////////////////////////////
    // Accessors
    /////////////////////////////
    const bool& isQuit() const;
    const bool& isPaused() const;

    /////////////////////////////
    // Methods
    /////////////////////////////
    void RunEvent();
    void Quit();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    virtual void OnInput(sf::Event* Event) = 0;
    virtual void OnUpdate(const float& DeltaTime);
    virtual void OnDraw(sf::RenderWindow* Window) = 0;

protected:
    // Variables
    bool Paused;
    bool Is_Quit;

    // Camera
    sf::View* Camera;

    Context* Ctx;
    Converter Cvt;

    // Keybinding
    std::map<std::string, unsh> Keybinds;

    // Event Queue
    std::vector<std::function<void(sf::Event*)>> EventQueue;

    // Mouse Position
    sf::Vector2s MouseWindow;
    sf::Vector2f MouseView;
};