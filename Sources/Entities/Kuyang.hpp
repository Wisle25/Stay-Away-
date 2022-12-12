#pragma once

#include "Kunti.hpp"

class Body;
struct Converter;

class Kuyang : public Ghost
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Kuyang(EArgs Args, Converter& Cvt, sf::Font& Font);
    virtual ~Kuyang();

    //////////////////////////////
    // Accessors
    //////////////////////////////
    Body* GetBody() const;

    //////////////////////////////
    // Modifiers
    //////////////////////////////
    void SetCleaned(bool Value);

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnUpdate(const float& DeltaTime, const sf::Vector2f& PlayerPosition);
    void OnDraw(sf::RenderWindow* Window, sf::Shader* Shader = nullptr, bool ShowBox = false);

private:
    //////////////////////////////
    // Custom Components
    //////////////////////////////
    Body* M_Body;

    bool IsCleaned;
};