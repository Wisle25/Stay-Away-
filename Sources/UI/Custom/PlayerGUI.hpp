#pragma once

class Bar;
class Attributes;
struct Converter;

class PlayerGUI
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    PlayerGUI(Converter& Cvt, sf::Font& Font);
    virtual ~PlayerGUI();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnUpdate(Attributes* I_Attribute);
    void OnDraw(sf::RenderWindow* Window);

private:
    /////////////////////////////
    // Bar
    /////////////////////////////
    Bar* HP_Bar;
    Bar* Stamina_Bar;
};