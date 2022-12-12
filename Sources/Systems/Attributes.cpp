#include "stdpch.hpp"
#include "Attributes.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Attributes::Attributes(AttrArgs Args):
    HP(Args.HP),
    MaxHP(Args.MaxHP),
    BaseDamage(Args.BaseDamage),
    MaxStamina(Args.MaxStamina)
{
}

///////////// Accessors /////////////////

const bool Attributes::Dead() const
{
    if (HP <= 0.f)
        return true;

    return false;
}

void Attributes::LoseHP(float Amount)
{
    HP -= Amount;
}

void Attributes::GainHP(float Amount)
{
    HP += Amount;
}
