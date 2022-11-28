#pragma once

#include "Map/TileMap.hpp"

#include "State.hpp"

class TileSelector;
class Modal;

class EditorState : public State
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    EditorState(Context* I_Ctx);
    virtual ~EditorState();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnInput(sf::Event* Event);
    void OnUpdate(const float& DeltaTime);
    void OnDraw(sf::RenderWindow* Window);

private:
    /////////////////////////////
    // SF Components
    /////////////////////////////
    /* Grid */
    std::vector<std::vector<sf::RectangleShape>> Grid;

    /* Selector */
    sf::RectangleShape Selector;
    TileSelector* Tileselector;

    /////////////////////////////
    // Custom Components
    /////////////////////////////
    std::map<std::string, Button*> Buttons;
    std::map<std::string, Modal*> Modals;
    TileMap* Map;

    /////////////////////////////
    // Variables
    /////////////////////////////
    sf::Vector2s MaxWorldSize;
    sf::Vector2s MouseGrid;

    /* Tile Data Temp */
    std::string TextureFile;
    enum TTypes Type;

    bool ShowSelector;
    bool ShowGrid;
    bool ShowModal;

    /////////////////////////////
    // Initializer Methods
    /////////////////////////////
    void InitializeGrid();
    void InitializeCamera();
    void InitializeSelector();
    void InitializeButtons();
    void InitializeComponents();

    /////////////////////////////
    // Input Handler Methods
    /////////////////////////////
    void MouseInputHandler(sf::Event* Event);
    void KeyboardInputHandler(sf::Event* Event);

    /////////////////////////////
    // Updater Methods
    /////////////////////////////
    void ZoomCameraAt(sf::Vector2i pixel, float zoom);
    void UpdateMousePosition();
    void HandleButtons();
};