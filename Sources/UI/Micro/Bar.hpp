#pragma once

struct BArgs
{
    sf::Vector2f& Size;
    sf::Vector2f& Position;
    sf::Font& Font;
    unsh CharSize;
    sf::Color TextColor = sf::Color::White;
};

class Bar
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Bar(BArgs Args);
    virtual ~Bar();

    /////////////////////////////
    // Modifiers
    /////////////////////////////
    void setContainerOutline(sf::Color Color, short Thickness);
    void setContentColor(sf::Color Color);

    /////////////////////////////
    // Lifecycle
    /////////////////////////////
    void onUpdate(short Current, short Max, const std::string BarTitle);
    void onDraw(sf::RenderWindow* Window);

private:
    /////////////////////////////
    // SF Components
    /////////////////////////////
    sf::RectangleShape Container;
    sf::RectangleShape Content;
    sf::Text Text;
};