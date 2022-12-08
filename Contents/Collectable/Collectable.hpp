#pragma once

#include "Interactable.hpp"

class Entity;

class Collectable : public Interactable
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Collectable(const String& Texture, sf::Vector2f Scale, sf::Vector2f I_Position, float Rotate);
    virtual ~Collectable();

    /////////////////////////////
    // Accessors
    /////////////////////////////
    const String& GetName() const;
    const sf::Vector2f& GetPosition() const;

    //////////////////////////////
    // Modifiers
    //////////////////////////////
    virtual void SetPosition(const sf::Vector2f& Position);
    virtual void SetScale(const sf::Vector2f& Scale);
    virtual void SetRotation(float Angle);
    void SetDirection(sf::Vector2f I_Direction);

    virtual void UseItem(const sf::Vector2f& Position, const sf::Vector2f& I_Direction) = 0;

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    virtual void OnUpdate(const float& DeltaTime) = 0;

protected:
    /////////////////////////////
    // Variables
    /////////////////////////////
    sf::Vector2f Direction;

    String Name;

    float Damage;
};