#pragma once

struct AttrArgs
{
    float HP;
    float MaxHP;
    float BaseDamage;

    float MaxStamina = 100.f; // Default value is 100
};

class Attributes
{
public:
    /////////////////////////////
    // Stats
    /////////////////////////////
    float HP;
    float MaxHP;
    float BaseDamage;
    float MaxStamina;
    float Stamina = MaxStamina;

    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Attributes(AttrArgs Args);

    //////////////////////////////
    // Accessors
    //////////////////////////////
    const bool Dead() const;

    //////////////////////////////
    // Modifiers
    //////////////////////////////
    void LoseHP(float Amount);
    void GainHP(float Amount);
};