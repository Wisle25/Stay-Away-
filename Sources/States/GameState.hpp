#pragma once

#include "State.hpp"

class TileMap;
class Player;
class PlayerGUI;
class Collectable;
class Body;

enum Status
{
    ONDEFAULT,
    ONPROGRESS
};

class GameState : public State
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    GameState(Context* I_Ctx);
    virtual ~GameState();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnInput(sf::Event* Event);
    void OnUpdate(const float& DeltaTime);
    void OnDraw(sf::RenderWindow* Window);

private:
    /////////////////////////////
    // Variables
    /////////////////////////////
    enum Status M_Status;

    /////////////////////////////
    // Custom Components
    /////////////////////////////
    TileMap* Map;
    std::vector<std::vector<Collectable*>> Items;

    /////////////////////////////
    // Entities
    /////////////////////////////
    Player* M_Player;
    std::vector<Body*> KBodies; /* Kuyang Body */

    /////////////////////////////
    // GUI
    /////////////////////////////
    PlayerGUI* M_PlayerGUI;

    /////////////////////////////
    // Initializer Methods
    /////////////////////////////
    void InitializeCamera();
    void InitializeMap();
    void InitializeEntities();
    void InitializeGUI();
    void InitializeItems();

    /////////////////////////////
    // Input Handler Methods
    /////////////////////////////
    void MouseInputHandler(sf::Event* Event);
    void KeyboardInputHandler(sf::Event* Event);
    void HandleInputPlayer(const float& DeltaTime);

    /////////////////////////////
    // Update Methods
    /////////////////////////////
    void UpdateInteractable(const float& DeltaTime);
};