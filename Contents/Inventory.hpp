#pragma once

class Collectable;
class Bar;

class Inventory
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Inventory(float Size, sf::Vector2f Position, sf::Font& Font, std::vector<std::function<void(sf::Event*)>>* EventQueue);
    virtual ~Inventory();

    //////////////////////////////
    // Accessors
    //////////////////////////////

    //////////////////////////////
    // Modifiers
    //////////////////////////////
    void AddItem(std::vector<Collectable*> Item);
    void UseItem(const sf::Vector2f& Position, const sf::Vector2f& I_Direction);

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnInput(sf::Event* Event);
    void OnUpdate(const float& DeltaTime, const sf::Vector2i& GridPosition, float GridSize);
    void OnDraw(sf::RenderWindow* Window);

private:
    /////////////////////////////
    // SFML Components
    /////////////////////////////
    sf::RectangleShape Selector;
    std::vector<Bar*> AmountBars;
    std::vector<sf::RectangleShape> ItemContainers;

    /////////////////////////////
    // Items that can be saved to inventory
    /////////////////////////////
    std::vector<std::vector<Collectable*>> Items;
    std::vector<Collectable*> UsedItem;

    /////////////////////////////
    // Variables
    /////////////////////////////
    float ContainerSize;

    unsh Now; /* Now is the current position of the selector */

    /////////////////////////////
    // Initializer Methods
    /////////////////////////////
    void InitializeContainer(sf::Vector2f Position, sf::Font& Font);
    void InitializeSelector();
};