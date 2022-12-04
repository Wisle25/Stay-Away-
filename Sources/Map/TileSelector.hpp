#pragma once

class ScrollMode;
class Button;
class Card;
struct Converter;
class TextField;

class TileSelector
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    TileSelector(Converter& Cvt, float I_GridSize, sf::Font& Font, std::vector<std::function<void(sf::Event*)>>* EventQueue);
    virtual ~TileSelector();

    /////////////////////////////
    // Accessors
    /////////////////////////////
    const bool& IsActive() const;
    const std::map<std::string, std::string>& GetData() const;

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnUpdate(const sf::Vector2s& MousePosition);
    void OnDraw(sf::RenderWindow* Window);

private:
    /////////////////////////////
    // SF Components
    /////////////////////////////
    sf::RectangleShape Container;

    /////////////////////////////
    // Custom Components
    /////////////////////////////
    ScrollMode* Scrollmode;

    std::map<std::string, sf::Text> Texts;
    std::map<std::string, Button*> Buttons;

    std::vector<std::pair<std::string, std::map<std::string, std::string>>> Category;
    std::vector<std::vector<Card*>> Cards;

    /////////////////////////////
    // Variables
    /////////////////////////////
    bool Active;
    float GridSize;

    unsh Page;

    /////////////////////////////
    // Private Methods
    /////////////////////////////
    void InitializeCategory();
    void InitializeBase(Converter& Cvt, sf::Font& Font);
    void InitializeComponents(Converter& Cvt, sf::Font& Font, std::vector<std::function<void(sf::Event*)>>* EventQueue);
};