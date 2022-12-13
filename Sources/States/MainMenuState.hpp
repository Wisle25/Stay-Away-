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
    //////////////////////////////
    // Background
    //////////////////////////////
    sf::Sprite Shape;
    sf::Texture Background;

    sf::Music Music;

    bool MusicPlayed;

    //////////////////////////////
    // Custom Components
    //////////////////////////////
    std::map<String, Button*> Buttons;

    //////////////////////////////
    // Initializer Methods
    //////////////////////////////
    void InitializeBackground();
};
