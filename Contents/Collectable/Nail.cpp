#include "stdpch.hpp"

#include "Systems/Collision/Collider.hpp"
#include "Systems/SoundManager.hpp"

#include "Nail.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Nail::Nail(sf::Vector2f Scale, sf::Vector2f Position, float Rotate):
    Collectable("../Resources/item/nail.png", Scale, Position, Rotate)
{
    // *** Initializing Name and Damage *** //
    Name = "Nail";
    Damage = 13.f;

    // *** Initializing HitBox *** //
    std::vector<sf::Vector2f> Vertices{
        { 0.f, 0.f }, { 24.f, 0.f }, { 24.f, 9.f }, { 0.f, 9.f }
    };
    M_HitBox = new Collider(Vertices);
    M_HitBox->SetColor(sf::Color::Blue);
    M_HitBox->SetPosition({ Position.x + 4.f, Position.y });

    // *** Sounds *** //
    Sounds["THROW"] = new SoundManager("../Resources/sounds/enviroment/knife_throw.wav");
}

Nail::~Nail()
{
    delete M_HitBox;
}

Collider* Nail::GetHitbox()
{
    return M_HitBox;
}

///////////// Modifiers /////////////////

void Nail::SetPosition(const sf::Vector2f& Position)
{
    M_Sprite.setPosition(Position);
    M_HitBox->SetPosition(Position);
}

void Nail::SetScale(const sf::Vector2f& Scale)
{
    M_Sprite.setScale(Scale);
}

void Nail::SetRotation(float Angle)
{
    M_Sprite.setRotation(Angle);
    M_HitBox->SetRotation(Angle);
}

void Nail::UseItem(const sf::Vector2f& Position, const sf::Vector2f& I_Direction)
{
    // Set the rotation based on the direction
    // Set the rotation based on the direction
    if (I_Direction.x < 0.f)
    {
        /* Left */
        SetRotation(180.f);
        SetPosition({ Position.x - 3.f, Position.y - 33.f }); /* The position of player's hand */
        SetDirection({ -1.f, 0.f });
    }
    else if (I_Direction.x > 0.f)
    {
        /* Right */
        SetRotation(0.f);
        SetPosition({ Position.x + 3.f, Position.y - 33.f }); /* The position of player's hand */
        SetDirection({ 1.f, 0.f });
    }
    else if (I_Direction.y < 0.f)
    {
        /* Down */
        SetRotation(-90.f);
        SetPosition({ Position.x - 20.f, Position.y - 38.f });
        SetDirection({ 0.f, -1.f });
    }
    else if (I_Direction.y > 0.f)
    {
        /* Up */
        SetRotation(90.f);
        SetPosition({ Position.x + 20.f, Position.y - 10.f });
        SetDirection({ 0.f, 1.f });
    }

    SetScale(GetDefaultScale());

    // Sounds
    Sounds["THROW"]->Play(0.5f);
}

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void Nail::OnUpdate(const float& DeltaTime)
{
    float Velocity = 950.f;

    M_Sprite.move(Direction * Velocity * DeltaTime);
    M_HitBox->SetPosition(M_Sprite.getPosition());
}
