#include "stdpch.hpp"
#include "Hatch.hpp"

///////////// Constructor & Destructor /////////////////

Hatch::Hatch(sf::Vector2f Scale, sf::Vector2f Position):
    Interactable("../Resources/item/hatch.png", Scale, Position)
{

}

Hatch::~Hatch()
{
    delete Sound;
}

///////////// Lifecycle /////////////

void Hatch::OnUpdate(const float& DeltaTime)
{

}