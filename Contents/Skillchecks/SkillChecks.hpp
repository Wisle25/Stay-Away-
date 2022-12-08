#pragma once

#include "Interactable.hpp"

class Bar;
class SkillCheck;
struct Converter;

class SkillChecks : public Interactable
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    SkillChecks(Converter& Cvt, sf::Font& Font, const String& Texture, sf::Vector2f Scale, sf::Vector2f Position);
    virtual ~SkillChecks();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    virtual void OnUpdate(const float& DeltaTime);
    virtual void OnDraw(sf::RenderWindow* Window, unsh Status);

protected:
    //////////////////////////////
    // Custom Components
    //////////////////////////////
    Bar* ProgressBar;
    SkillCheck* M_SkillCheck;

    //////////////////////////////
    // Variables
    //////////////////////////////
    float Progress;
    float MaxProgress;

    float SkillCheckTimer;
    float SkillCheckTimerMax;

    bool DrawSkillCheck;
};