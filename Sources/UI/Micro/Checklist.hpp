#pragma once

class Checklist
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Checklist(sf::Vector2f Size, sf::Vector2f Position, std::vector<std::function<void(sf::Event*)>>* EventQueue);
    virtual ~Checklist();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnInput(sf::Event* Event);
    void OnUpdate(const sf::Vector2s& MousePosition, bool& Value);
    void OnDraw(sf::RenderWindow* Window);

private:
    //////////////////////////////
    // SF Components
    //////////////////////////////
    sf::RectangleShape Box;
    sf::RectangleShape Content;

    sf::Cursor ArrowCursor;
    sf::Cursor HandCursor;

    //////////////////////////////
    // Variables
    //////////////////////////////
    bool IsCheckList;
    bool IsActive;
};