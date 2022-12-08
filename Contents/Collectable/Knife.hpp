#pragma once

#include "Collectable.hpp"

class Collider;

class Knife : public Collectable
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Knife(sf::Vector2f Scale, sf::Vector2f Position, float Rotate);
    virtual ~Knife();

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
    void OnDraw(sf::RenderWindow* Window);

private:
    /////////////////////////////
    // Custom Components
    /////////////////////////////
    Collider* M_HitBox;
};