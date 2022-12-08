#pragma once

class Entity;

class Interactable
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Interactable(const String& Texture, sf::Vector2f Scale, sf::Vector2f Position);
    virtual ~Interactable();

    //////////////////////////////
    // Accessors
    //////////////////////////////
    const sf::Vector2f& GetDefaultScale() const;
    const bool InBoundary(const sf::Vector2f& Position) const;

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    virtual void OnUpdate(const float& DeltaTime) = 0;
    virtual void OnDraw(sf::RenderWindow* Window);

protected:
    /////////////////////////////
    // SFML Components
    /////////////////////////////
    sf::Sprite M_Sprite;
    sf::Texture M_Texture;
    sf::RectangleShape M_Boundaries;

    sf::Vector2f DefaultScale;
};