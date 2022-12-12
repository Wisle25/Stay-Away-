#include "stdpch.hpp"
#include "Kunti.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Kunti::Kunti(EArgs Args):
    Ghost(Args)
{
    srand(6);
    // Randomize direction
    sf::Vector2f R_Direction[4] = {
        { 1.f, 0.f },
        { -1.f, 0.f },
        { 0.f, 1.f },
        { 0.f, -1.f}
    };

    // Set the direction randomly
    Direction = R_Direction[0 + rand() % (3 - 0 + 1)];

    // Name
    Name = "Kunti";

    // Adding Animations
    M_Animations[IDLE_DOWN] = new Animation(Sprite, "../Resources/Sprites/Kunti/kunti_front.png", 15.f, 64);
    M_Animations[WALK_UP] = new Animation(Sprite, "../Resources/Sprites/Kunti/kunti_back.png", 15.f, 64);
    M_Animations[WALK_DOWN] = new Animation(Sprite, "../Resources/Sprites/Kunti/kunti_left.png", 15.f, 64);
    M_Animations[WALK_X] = new Animation(Sprite, "../Resources/Sprites/Kunti/kunti_left.png", 15.f, 64);
}

Kunti::~Kunti()
{

}

///////////// Private Methods /////////////

///////////// Lifecycle /////////////////

// \brief Draw SF drawable components to screen
void Kunti::OnDraw(sf::RenderWindow* Window, sf::Shader* Shader, bool ShowBox)
{
    Window->draw(Sprite);

    // Inheritance
    Ghost::OnDraw(Window, Shader, ShowBox);
}