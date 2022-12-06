#pragma once

#include "Nail.hpp"

class SandBag : public Collectable
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    SandBag(sf::Vector2f Scale, sf::Vector2f Position, float Rotate);
    virtual ~SandBag();

    /////////////////////////////
    // Modifiers
    /////////////////////////////
    void UseItem(const sf::Vector2f& Position, const sf::Vector2f& I_Direction);

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnUpdate(const float& DeltaTime);

private:
    bool Usage;
};