#pragma once

struct BaArgs
{
    const sf::Vector2f& Size;
    const sf::Vector2f& Position;
    const sf::Font& Font;
    unsh CharSize;
    sf::Color TextColor = sf::Color::White;
};

class Bar
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Bar(BaArgs Args);
    virtual ~Bar();

    /////////////////////////////
    // Modifiers
    /////////////////////////////
    void SetContainerOutline(sf::Color Color, short Thickness);
    void SetContentColor(sf::Color Color);

    /////////////////////////////
    // Lifecycle
    /////////////////////////////
    void OnUpdate(float Current, float Max, const String& BarTitle);
    void OnDraw(sf::RenderWindow* Window);

private:
    /////////////////////////////
    // SF Components
    /////////////////////////////
    sf::RectangleShape Container;
    sf::RectangleShape Content;
    sf::Text Text;
};