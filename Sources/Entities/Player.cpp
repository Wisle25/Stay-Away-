#include "stdpch.hpp"

#include "Inventory.hpp"
#include "Collectable/Collectable.hpp"
#include "UI/Converter.hpp"

#include "Player.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Player::Player(EArgs Args, Converter& Cvt, sf::Font& Font, std::vector<std::function<void(sf::Event*)>>* EventQueue):
    Entity(Args)
{
    // *** Creating Animations *** //
    M_Animations[WALK_UP] = new Animation(Sprite, "../Resources/Sprites/MC/Walk_up.png",15.5f, 64);
    M_Animations[WALK_X] = new Animation(Sprite, "../Resources/Sprites/MC/Walk_left.png", 15.5f, 64);
    M_Animations[WALK_DOWN] = new Animation(Sprite, "../Resources/Sprites/MC/Walk_down.png", 15.5f, 64);
    M_Animations[IDLE_UP] = new Animation(Sprite, "../Resources/Sprites/MC/Idle_back.png", 15.5f, 60);
    M_Animations[IDLE_X] = new Animation(Sprite, "../Resources/Sprites/MC/mc_leftidle.png", 38.f, 64);
    M_Animations[IDLE_DOWN] = new Animation(Sprite, "../Resources/Sprites/MC/mc_frontfix.png", 38.f, 64);

    // *** Inventory *** //
    M_Inventory = new Inventory(Cvt.P2PX(4.3f), { Cvt.P2PX(38.7f), Cvt.P2PY(84.f) }, Font, EventQueue);
}

Player::~Player()
{
    delete M_Inventory;
}

///////////// Accessors /////////////

const String Player::GetItemName() const
{
    return M_Inventory->GetItemName();
}

const bool Player::IsFull() const
{
    return M_Inventory->IsFull();
}

///////////// Modifiers /////////////

void Player::AddItem(std::vector<Collectable*> Item)
{
    // Adding item with the default amount
    M_Inventory->AddItem(Item);
}

void Player::UseItem()
{
    M_Inventory->UseItem(Sprite.getPosition(), Direction);
}

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void Player::OnUpdate(const float& DeltaTime)
{
    // Inheritance
    Entity::OnUpdate(DeltaTime);

    // *** Updating Idling State *** //
    if (M_Movement->GetVelocity() == sf::Vector2f() && Direction.y > 0.f)
        State = IDLE_DOWN;
    else if (M_Movement->GetVelocity() == sf::Vector2f() && Direction.y < 0.f)
        State = IDLE_UP;
    else if (M_Movement->GetVelocity() == sf::Vector2f() && Direction.x != 0.f)
        State = IDLE_X;

    // *** Updating the Holding item *** //
    M_Inventory->OnUpdate(DeltaTime, GetPositionGrid(64.f), 64.f);
}

// \brief Draw SF drawable components to screen
void Player::OnDraw(sf::RenderWindow* Window, sf::Shader* Shader, bool ShowBox)
{
    Window->draw(Sprite);

    // *** Components *** //
    Window->setView(Window->getDefaultView());
    M_Inventory->OnDraw(Window);

    Window->setView(Window->getView());
    // Inheritance
    Entity::OnDraw(Window, Shader, true);
}