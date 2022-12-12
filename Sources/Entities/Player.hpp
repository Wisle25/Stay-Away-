#pragma once

#include "Entity.hpp"

class Collectable;
class Inventory;
struct Converter;

class Player : public Entity
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Player(
        EArgs Args,
        Converter& Cvt,
        sf::Font& Font,
        std::vector<Collectable*>* I_UsedItem, std::vector<std::function<void(sf::Event*)>>* EventQueue
    );
    virtual ~Player();

    //////////////////////////////
    // Accessors
    //////////////////////////////
    const String GetItemName() const;
    const bool IsFull() const;

    //////////////////////////////
    // Modifiers
    //////////////////////////////
    void AddItem(std::vector<Collectable*> Item);
    void UseItem();
    void OnProgress(const bool Value);

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnUpdate(const float& DeltaTime);
    void OnDraw(sf::RenderWindow* Window, sf::Shader* Shader = nullptr, bool ShowBox = false);
    void DrawInventory(sf::RenderWindow* Window);

private:
    //////////////////////////////
    // Custom Components
    //////////////////////////////
    Inventory* M_Inventory;
};