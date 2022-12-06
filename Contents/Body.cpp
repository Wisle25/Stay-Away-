#include "stdpch.hpp"
#include "Body.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Body::Body(std::vector<std::function<void(sf::Event*)>>* EventQueue)
{

    // Enqueue On Input methods to Event Queue
    EventQueue->push_back(std::bind(&OnInput, this, std::placeholders::_1));
}

Body::~Body()
{

}

///////////// Private Methods /////////////

///////////// Lifecycle /////////////////

// \brief Handling input 
void Body::OnInput(sf::Event* Event)
{
    
}

// \brief Called every frame, apply game logic here
void Body::OnUpdate(const float& DeltaTime)
{
    
}

// \brief Draw SF drawable components to screen
void Body::OnDraw(sf::RenderWindow* Window)
{
    
}