#pragma once

#include "Map/TileSelector.hpp"

#include "State.hpp"

class MainMenuState : public State
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    MainMenuState(Context* I_Ctx);
    virtual ~MainMenuState();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnInput(sf::Event* Event);
    void OnUpdate(const float& DeltaTime);
    void OnDraw(sf::RenderWindow* Window);

private:
    // Variables

    // UI Components
    std::map<String, Button*> Buttons;
};