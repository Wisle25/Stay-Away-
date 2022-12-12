#include "stdpch.hpp"

#include "Systems/SoundManager.hpp"

#include "Body.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Body::Body(Converter& Cvt, sf::Font& Font, sf::Vector2f Scale, sf::Vector2f Position):
    SkillChecks(Cvt, Font, "../Resources/item/dead_body.png", Scale, Position)
{
    CleaningSound = new SoundManager("../Resources/sounds/enviroment/cleaning.wav");
}

Body::~Body()
{
    delete CleaningSound;
}

const bool Body::IsCleaned() const
{
    return Progress >= MaxProgress;
}

void Body::OnUpdate(const float& DeltaTime)
{
    // Inheritance
    SkillChecks::OnUpdate(DeltaTime);

    CleaningSound->Play(DeltaTime);
}