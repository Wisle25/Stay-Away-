#pragma once

#include "Body.hpp"

class Objective : public SkillChecks
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Objective(Converter& Cvt, sf::Font& Font, sf::Vector2f Scale, sf::Vector2f Position);
    virtual ~Objective();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnUpdate(const float& DeltaTime);

private:
    //////////////////////////////
    // Custom Components
    //////////////////////////////
    SoundManager* CleaningSound;
};