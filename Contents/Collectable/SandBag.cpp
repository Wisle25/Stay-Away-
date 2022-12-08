#include "stdpch.hpp"
#include "SandBag.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
SandBag::SandBag(sf::Vector2f Scale, sf::Vector2f Position, float Rotate):
    Collectable("../Resources/item/sand_bag.png", Scale, Position, Rotate)
{
    Name = "SandBag";
}

SandBag::~SandBag()
{

}

///////////// Modifiers /////////////

void SandBag::UseItem(const sf::Vector2f& Position, const sf::Vector2f& I_Direction)
{
}

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void SandBag::OnUpdate(const float& DeltaTime)
{
}