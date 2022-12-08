#include "stdpch.hpp"

#include "Body.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Body::Body(Converter& Cvt, sf::Font& Font, sf::Vector2f Scale, sf::Vector2f Position, bool Flipped):
    SkillChecks(Cvt, Font, "../Resources/item/dead_body.png", Scale, Position)
{
    if (Flipped)
        M_Sprite.setTextureRect(sf::IntRect(0, M_Texture.getSize().y, -M_Texture.getSize().x, M_Texture.getSize().y));
}

Body::~Body()
{
}

const bool Body::IsCleaned() const
{
    return Progress >= MaxProgress;
}
