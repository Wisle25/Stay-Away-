#pragma once

#include "Interactable.hpp"

class Bar;
class SkillCheck;
class SoundManager;
struct Converter;

class SkillChecks : public Interactable
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    SkillChecks(Converter& Cvt, sf::Font& Font, const String& Texture, sf::Vector2f Scale, sf::Vector2f Position);
    ~SkillChecks();

    //////////////////////////////
    // Accessors
    //////////////////////////////
    const bool IsCompleted() const;

    //////////////////////////////
    // Modifiers
    //////////////////////////////
    void SetOnProgress(bool I_Value);

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    virtual void OnUpdate(const float& DeltaTime);
    virtual void OnDraw  (sf::RenderWindow* Window, bool I_OnProgress = false);

protected:
    //////////////////////////////
    // Custom Components
    //////////////////////////////
    Bar*                            ProgressBar;
    SkillCheck*                     M_SkillCheck;
    std::map<String, SoundManager*> Sounds;

    //////////////////////////////
    // Variables
    //////////////////////////////
    float Progress;
    float MaxProgress;

    float SkillCheckTimer;
    float SkillCheckTimerMax;

    bool DrawSkillCheck;
    bool OnProgress;

    //////////////////////////////
    // Private Methods
    //////////////////////////////
    void Reset();
};