#pragma once

#include "Systems/Animation.hpp"
#include "Systems/Attributes.hpp"
#include "Systems/Collision/Collider.hpp"
#include "Systems/Collision/Collision.hpp"
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
    sf::Vector2f Position;

    // Attributes
    float HP;
    float MaxHP;
    float BaseDamage;

    // Colliders and HitBox
    std::vector<sf::Vector2f> ColliderVertices;
    std::vector<sf::Vector2f> HitBoxVertices;
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
    // Accessors
    //////////////////////////////
    Attributes* GetAttribute();
    Collider* GetCollider();
    const sf::Vector2f GetDirection() const;
    const sf::Vector2f GetPosition() const;
    const sf::Vector2i GetPositionGrid(float GridSize) const;
    const sf::Vector2f GetCenter() const;
    const bool AnimFinished() const;

    //////////////////////////////
    // Modifiers
    //////////////////////////////
    void Move(sf::Vector2f I_Direction, const float& DeltaTime);
    void Move(sf::Vector2f MTV);
    void Damage(Collider* Damager, float Damage);
    void ResetVelocity();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    virtual void OnUpdate(const float& DeltaTime);
    virtual void OnDraw(sf::RenderWindow* Window, sf::Shader* Shader = nullptr, bool ShowBox = false);

protected:
    //////////////////////////////
    // State of the Entity
    //////////////////////////////
    enum EState State;
    enum EState LastState;
    sf::Vector2f Direction;

    //////////////////////////////
    // SF Components
    //////////////////////////////
    sf::Sprite Sprite;

    //////////////////////////////
    // Systems
    //////////////////////////////
    std::map<enum EState, Animation*> M_Animations;
    Attributes* M_Attributes;
    Collider* M_Collider;
    Collider* M_HitBox;
    Movement* M_Movement;
};