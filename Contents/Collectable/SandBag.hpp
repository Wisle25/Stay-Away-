#pragma once

#include "Nail.hpp"

class Bar;

class SandBag : public Collectable
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    SandBag(sf::Vector2f Scale, sf::Vector2f Position, float Rotate);
    virtual ~SandBag();

    /////////////////////////////
    // Accessors
    /////////////////////////////
    Collider* GetHitbox();

    /////////////////////////////
    // Modifiers
    /////////////////////////////
    void UseItem(const sf::Vector2f& Position, const sf::Vector2f& I_Direction);

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnUpdate(const float& DeltaTime);
};