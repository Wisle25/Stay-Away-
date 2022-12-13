#pragma once

#include "Kuyang.hpp"

class Pocong : public Ghost
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Pocong(EArgs Args);
    virtual ~Pocong();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnDraw(sf::RenderWindow* Window, sf::Shader* Shader = nullptr, bool ShowBox = false);

private:

};