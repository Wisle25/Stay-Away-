#pragma once

#include "State.hpp"

class Dropdown;
class Button;

class SettingsState : public State
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    SettingsState(Context* I_Ctx);
    virtual ~SettingsState();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnInput(sf::Event* Event);
    void OnUpdate(const float& DeltaTime);
    void OnDraw(sf::RenderWindow* Window);

private:
    //////////////////////////////
    // Custom Components
    //////////////////////////////
    sf::Text TitleText;
    std::vector<sf::Text> SessionText;
    std::map<String, sf::Text> SettingsName;
    std::map<String, Dropdown*> Settings;
    std::map<String, Button*> Btns;
};