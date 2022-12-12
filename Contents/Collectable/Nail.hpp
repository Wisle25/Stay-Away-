#pragma once

#include "Knife.hpp"

class Nail : public Collectable
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Nail(sf::Vector2f Scale, sf::Vector2f Position, float Rotate);
    virtual ~Nail();

    /////////////////////////////
    // Accessors
    /////////////////////////////
    Collider* GetHitbox();

    /////////////////////////////
    // Modifiers
    /////////////////////////////
    void SetPosition(const sf::Vector2f& Position);
    void SetScale(const sf::Vector2f& Scale);
    void SetRotation(float Angle);

    void UseItem(const sf::Vector2f& Position, const sf::Vector2f& I_Direction);

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnUpdate(const float& DeltaTime);

private:
    /////////////////////////////
    // Custom Components
    /////////////////////////////
    Collider* M_HitBox;
};