#pragma once

#include "SkillChecks.hpp"

class Bar;
struct Converter;
class SkillCheck;

class Body : public SkillChecks
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Body(Converter& Cvt, sf::Font& Font, sf::Vector2f Scale, sf::Vector2f Position, bool Flipped);
    virtual ~Body();

    //////////////////////////////
    // Accessors
    //////////////////////////////
    const bool IsCleaned() const;
};