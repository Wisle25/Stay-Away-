#pragma once

#include "SkillChecks.hpp"

class Bar;
class SkillCheck;
class SoundManager;
struct Converter;

class Body : public SkillChecks
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Body(Converter& Cvt, sf::Font& Font, sf::Vector2f Scale, sf::Vector2f Position);
    virtual ~Body();

    //////////////////////////////
    // Accessors
    //////////////////////////////
    const bool IsCleaned() const;

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