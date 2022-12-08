#include "stdpch.hpp"
#include "Entity.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Entity::Entity(EArgs Args):
    State(IDLE_DOWN),
    LastState(State)
{
    // Starting spawn position
    Sprite.setOrigin(32.f, 64.f);
    Sprite.setPosition(Args.Position);

    // *** Initializing Systems *** //
    M_Movement = new Movement(Sprite, Args.MaxVelocity, Args.Acceleration, Args.Deceleration);

    M_Attributes = new Attributes({
        .HP = Args.HP,
        .MaxHP = Args.MaxHP,
        .BaseDamage = Args.BaseDamage
    });

    M_Collider = new Collider(Args.ColliderVertices);
    M_Collider->SetColor(sf::Color::Green);
    M_Collider->SetPosition({ Sprite.getPosition().x, Sprite.getPosition().y - 8.f});

    M_HitBox = new Collider(Args.HitBoxVertices);
    M_HitBox->SetColor(sf::Color::Blue);
    M_HitBox->SetPosition({ Sprite.getPosition().x, Sprite.getPosition().y - 32.f});
}

Entity::~Entity()
{
    for (auto& Anim : M_Animations)
        delete Anim.second;

    delete M_Attributes;
    delete M_Collider;
    delete M_HitBox;
    delete M_Movement;
}

///////////// Accessors /////////////

Attributes* Entity::GetAttribute()
{
    return M_Attributes;
}

Collider* Entity::GetCollider()
{
    return M_Collider;
}

const sf::Vector2f Entity::GetDirection() const
{
    return Direction;
}

const sf::Vector2f Entity::GetPosition() const
{
    return Sprite.getPosition();
}

const sf::Vector2i Entity::GetPositionGrid(float GridSize) const
{
    return sf::Vector2i(Sprite.getPosition() / GridSize);
}

const sf::Vector2f Entity::GetCenter() const
{
    return M_HitBox->GetPosition();
}

const bool Entity::AnimFinished() const
{
    return M_Animations.at(State)->IsFinished();
}

///////////// Private Methods /////////////

void Entity::Move(sf::Vector2f I_Direction, const float& DeltaTime)
{
    M_Movement->Move(I_Direction, DeltaTime);
    Direction = I_Direction;
}

void Entity::Move(sf::Vector2f MTV)
{
    Sprite.setPosition(Sprite.getPosition() + MTV);
    M_HitBox->Move(MTV);
    M_Collider->Move(MTV);
}

void Entity::Damage(Collider* Damager, float Damage)
{
    if (Collision(M_HitBox, Damager))
        M_Attributes->LoseHP(Damage);
}

void Entity::ResetVelocity()
{
    M_Movement->SetVelocity();
    State = IDLE_DOWN;
}

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void Entity::OnUpdate(const float& DeltaTime)
{
    // Updating States
    if (M_Movement->GetVelocity().y < 0.f)
        State = WALK_UP;
    else if (M_Movement->GetVelocity().y > 0.f)
        State = WALK_DOWN;
    else if (M_Movement->GetVelocity().x != 0.f)
        State = WALK_X;

    // Animating
    M_Animations[State]->OnUpdate(DeltaTime);

    // Movement
    M_Movement->OnUpdate(DeltaTime);
    M_Collider->SetPosition({ Sprite.getPosition().x, Sprite.getPosition().y - 8.f});
    M_HitBox->SetPosition({ Sprite.getPosition().x, Sprite.getPosition().y - 32.f});

    // If the lastest status is not equal to current
    if (LastState != State)
    {
        M_Animations.at(LastState)->Reset();
        LastState = State;
    }
}

void Entity::OnDraw(sf::RenderWindow* Window, sf::Shader* Shader, bool ShowBox)
{
    if (Direction.x > 0)
        M_Animations[State]->SetFlipped(false);
    else if (Direction.x < 0)
        M_Animations[State]->SetFlipped(true);

    if (ShowBox)
    {
        M_HitBox->OnDraw(*Window);
        M_Collider->OnDraw(*Window);
    }
}