#pragma once

#include "States/MainMenuState.hpp"

class App
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    App();
    virtual ~App();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnUpdate();
    void OnDraw();
    void Run();

private:
    // Main Components
    sf::RenderWindow* Window;
    sf::Event Event;
    sf::Image Icon;
    std::stack<State*> States;

    // Context Settings
    Settings Settings;
    Context Ctx;

    // Delta Time
    sf::Clock DtClock;
    float DeltaTime;
};