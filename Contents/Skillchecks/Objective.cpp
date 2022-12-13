#include "stdpch.hpp"

#include "Systems/SoundManager.hpp"

#include "Objective.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Objective::Objective(Converter& Cvt, sf::Font& Font, sf::Vector2f Scale, sf::Vector2f Position):
    SkillChecks(Cvt, Font, "../Resources/item/grave.png", Scale, Position)
{
    CleaningSound = new SoundManager("../Resources/sounds/enviroment/cleaning.wav");
}

Objective::~Objective()
{
    delete CleaningSound;
}

void Objective::OnUpdate(const float& DeltaTime)
{
    // Inheritance
    SkillChecks::OnUpdate(DeltaTime);

    CleaningSound->Play(DeltaTime);
}