#pragma once

#include "Collectable.hpp"

class Knife : public Collectable
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Knife(sf::Vector2f Scale, sf::Vector2f Position, float Rotate);
    virtual ~Knife();

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