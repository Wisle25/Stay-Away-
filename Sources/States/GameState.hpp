#pragma once

#include "State.hpp"

class Body;
class Collectable;
class Ghost;
class Hatch;
class Objective;
class Player;
class PlayerGUI;
class TileMap;
class Jumpscare;

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
    // SFML Components
    /////////////////////////////
    sf::RectangleShape FinishedScreen;
    sf::Texture        FinishedScreenTexture;

    sf::Music          Backsound;
    sf::Music          HeartBeat;

    /////////////////////////////
    // Variables
    /////////////////////////////
    float GhostAttackTimer;
    float GhostAttackTimerMax;

    float GhostSpawnerTimer;
    float GhostSpawnerTimerMax;

    float ItemSpawnerTimer;
    float ItemSpawnerTimerMax;

    bool Finished;
    bool HeartBeatPlayed;

    String GhostName;

    /////////////////////////////
    // Custom Components
    /////////////////////////////
    TileMap* Map;
    Hatch* M_Hatch;

    std::vector<Objective*> Objectives;
    std::vector<std::vector<Collectable*>> Items;
    std::vector<Collectable*> UsedItem;

    std::map<String, Jumpscare*> Jumpscares;

    /////////////////////////////
    // Entities
    /////////////////////////////
    Player* M_Player;
    std::vector<Ghost*> Ghosts;

    /////////////////////////////
    // GUI
    /////////////////////////////
    PlayerGUI* M_PlayerGUI;

    /////////////////////////////
    // Initializer Methods
    /////////////////////////////
    void InitializeCamera  ();
    void InitializeMap     ();
    void InitializeEntities();
    void InitializeGUI     ();
    void InitializeItems   ();

    /////////////////////////////
    // Input Handler Methods
    /////////////////////////////
    void MouseInputHandler   (sf::Event* Event);
    void KeyboardInputHandler(sf::Event* Event);
    void HandleInputPlayer   (const float& DeltaTime);

    /////////////////////////////
    // Update or Handler Methods
    /////////////////////////////
    void UpdateInteractable(const float& DeltaTime);
    void HandleCombat      (const float& DeltaTime);
    void HandleCamera      ();

    void SpawnGhost        (const float& DeltaTime);
    void SpawnItem         (const float& DeltaTime);
    void SpawnHatch        ();
};