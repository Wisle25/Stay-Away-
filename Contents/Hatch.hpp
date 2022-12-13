#pragma once

#include "Interactable.hpp"

class SoundManager;
class Player;
struct Converter;

class Hatch : public Interactable
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Hatch(Converter& Cvt, sf::Vector2f Scale, sf::Vector2f Position);
    virtual ~Hatch();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnUpdate(const float& DeltaTime);
    void OnDraw(sf::RenderWindow* Window);

private:
    //////////////////////////////
    // SFML Components
    //////////////////////////////
    sf::Sprite Shape;
    sf::Texture Text;
};