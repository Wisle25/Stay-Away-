#include "stdpch.hpp"
#include "Collectable.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Collectable::Collectable(const String& Texture, sf::Vector2f Scale, sf::Vector2f I_Position, float Rotate):
    Interactable(Texture, Scale, I_Position),
    Removable(true),
    MaxAmount(15), // Default value of amount
    Amount(MaxAmount)
{
    M_Sprite.setRotation(Rotate);
}

Collectable::~Collectable()
{

}

///////////// Accessors /////////////////

const String& Collectable::GetName() const
{
    return Name;
}

const unsh& Collectable::GetAmount() const
{
    return Amount;
}

const unsh& Collectable::GetMaxAmount() const
{
    return MaxAmount;
}

const sf::Vector2f& Collectable::GetPosition() const
{
    return M_Sprite.getPosition();
}

const bool& Collectable::IsRemovable() const
{
    return Removable;
}


///////////// Modifiers /////////////////

void Collectable::SetPosition(const sf::Vector2f& Position)
{
    M_Sprite.setPosition(Position);
}

void Collectable::SetScale(const sf::Vector2f& Scale)
{
    M_Sprite.setScale(Scale);
}

void Collectable::SetRotation(float Angle)
{
    M_Sprite.setRotation(Angle);
}

void Collectable::SetDirection(sf::Vector2f I_Direction)
{
    Direction = I_Direction;
}