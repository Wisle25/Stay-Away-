#include "stdpch.hpp"
#include "Pocong.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Pocong::Pocong(EArgs Args):
    Ghost(Args)
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

    // Name
    Name = "Pocong";

    // Adding Animations
    M_Animations[IDLE_DOWN] = new Animation(Sprite, "../Resources/Sprites/Pocong/pocong_front.png", 24.f, 64);
    M_Animations[WALK_UP] = new Animation(Sprite, "../Resources/Sprites/Pocong/pocong_back.png", 24.f, 64);
    M_Animations[WALK_DOWN] = new Animation(Sprite, "../Resources/Sprites/Pocong/pocong_front.png", 24.f, 64);
    M_Animations[WALK_X] = new Animation(Sprite, "../Resources/Sprites/Pocong/pocong_left.png", 24.f, 64);
}

Pocong::~Pocong()
{

}

///////////// Lifecycle /////////////////

// \brief Draw SF drawable components to screen
void Pocong::OnDraw(sf::RenderWindow* Window, sf::Shader* Shader, bool ShowBox)
{
    Window->draw(Sprite);

    // Inheritance
    Ghost::OnDraw(Window, Shader, ShowBox);
}