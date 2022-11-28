#include "stdpch.hpp"
#include "Entity.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Entity::Entity(EArgs Args):
    State(IDLE_X),
    LastState(State)
{
    // Starting spawn position
    Sprite.setPosition(Args.Position);

    // Initializing Systems
    SMovement = new Movement(Sprite, Args.MaxVelocity, Args.Acceleration, Args.Deceleration);
}

Entity::~Entity()
{
    for (auto& Anim : SAnimations)
        delete Anim.second;

    delete this->SMovement;
}

///////////// Private Methods /////////////

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void Entity::OnUpdate(const float& DeltaTime)
{
}

// \brief Draw SF drawable components to screen
void Entity::OnDraw(sf::RenderWindow* Window)
{
}