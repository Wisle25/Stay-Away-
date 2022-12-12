#pragma once

#include "Interactable.hpp"

class SoundManager;

class Hatch : public Interactable
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Hatch(sf::Vector2f Scale, sf::Vector2f Position);
    virtual ~Hatch();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnUpdate(const float& DeltaTime);

private:
    //////////////////////////////
    // Custom Components
    //////////////////////////////
    SoundManager* Sound;
};