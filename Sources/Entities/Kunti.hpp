#pragma once

#include "Ghost.hpp"

class Kunti : public Ghost
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Kunti(EArgs Args);
    virtual ~Kunti();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnDraw(sf::RenderWindow* Window, sf::Shader* Shader, bool ShowBox);

};