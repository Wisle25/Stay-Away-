#pragma once

#include "Systems/Animation.hpp"
#include "Systems/Movement.hpp"

enum EState
{
    IDLE_X = 0,
    IDLE_UP,
    IDLE_DOWN,
    WALK_X,
    WALK_UP,
    WALK_DOWN,
    SLIDE,
    ATTACK
};

struct EArgs
{
    // Movement System
    float MaxVelocity;
    float Acceleration;
    float Deceleration;

    // Start Position
    sf::Vector2f& Position;
};

class Entity
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Entity(EArgs Args);
    virtual ~Entity();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnUpdate(const float& DeltaTime);
    void OnDraw(sf::RenderWindow* Window);

private:
    //////////////////////////////
    // State of the Entity
    //////////////////////////////
    enum EState State;
    enum EState LastState;

    //////////////////////////////
    // SF Components
    //////////////////////////////
    sf::Sprite Sprite;

    //////////////////////////////
    // Systems
    //////////////////////////////
    std::map<enum EState, Animation*> SAnimations;
    Movement* SMovement;
};