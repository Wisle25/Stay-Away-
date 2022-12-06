#pragma once

class Body
{  
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Body(std::vector<std::function<void(sf::Event*)>>* EventQueue);
    virtual ~Body();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnInput(sf::Event* Event);
    void OnUpdate(const float& DeltaTime);
    void OnDraw(sf::RenderWindow* Window);

private:

};