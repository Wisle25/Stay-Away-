#include "stdpch.hpp"

#include "Core/Vector.hpp"
#include "Skillchecks/Body.hpp"

#include "Kuyang.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Kuyang::Kuyang(EArgs Args, Converter& Cvt, sf::Font& Font):
    Ghost(Args),
    IsCleaned(false)
{
    // Randomize direction
    sf::Vector2f R_Direction[4] = {
        { 1.f, 0.f },
        { -1.f, 0.f },
        { 0.f, 1.f },
        { 0.f, -1.f}
    };

    // Set the direction randomly
    Direction = R_Direction[0 + rand() % (3 - 0 + 1)];

    // *** Initializing Name and Animation *** //
    Name = "Kuyang";

    M_Animations[IDLE_DOWN] = new Animation(Sprite, "../Resources/Sprites/Kuyang/kuyang_front.png", 15.f, 64);
    M_Animations[WALK_UP] = new Animation(Sprite, "../Resources/Sprites/Kuyang/kuyang_back.png", 15.f, 64);
    M_Animations[WALK_DOWN] = new Animation(Sprite, "../Resources/Sprites/Kuyang/kuyang_front.png", 15.f, 64);
    M_Animations[WALK_X] = new Animation(Sprite, "../Resources/Sprites/Kuyang/kuyang_left.png", 15.f, 64);

    // *** Initializing the body *** //
    M_Body = new Body(Cvt, Font, { 0.8f, 0.8f }, Args.Position);
}

Kuyang::~Kuyang()
{
    delete M_Body;
}

///////////// Accessors /////////////

Body* Kuyang::GetBody() const
{
    return M_Body;
}

///////////// Modifiers /////////////

void Kuyang::SetCleaned(bool Value)
{
    IsCleaned = Value;
}

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void Kuyang::OnUpdate(const float& DeltaTime, const sf::Vector2f& PlayerPosition)
{
    // Inheritance
    Ghost::OnUpdate(DeltaTime, PlayerPosition);

    // *** Install kill kuyang once the body is cleaned *** //
    if (M_Body->IsCleaned())
    {
        IsCleaned = false;
        M_Attributes->LoseHP(101.f);
    }

    // *** Updating Body cleaning *** //
    if (IsCleaned)
        M_Body->OnUpdate(DeltaTime);
}

// \brief Draw SF drawable components to screen
void Kuyang::OnDraw(sf::RenderWindow* Window, sf::Shader* Shader, bool ShowBox)
{
    M_Body->OnDraw(Window, IsCleaned);

    Window->draw(Sprite);

    // Inheritance
    Ghost::OnDraw(Window, Shader, ShowBox);
}