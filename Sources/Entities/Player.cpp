#include "stdpch.hpp"

#include "Inventory.hpp"
#include "Collectable/Collectable.hpp"
#include "UI/Converter.hpp"

#include "Player.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Player::Player(
    EArgs Args,
    Converter& Cvt,
    sf::Font& Font,
    std::vector<Collectable*>* I_UsedItem, std::vector<std::function<void(sf::Event*)>>* EventQueue
):
    Entity(Args)
{
    // *** Creating Animations *** //
    M_Animations[WALK_UP] = new Animation(Sprite, "../Resources/Sprites/MC/mc_backwalk.png",15.5f, 64);
    M_Animations[WALK_X] = new Animation(Sprite, "../Resources/Sprites/MC/mc_walkleft.png", 15.5f, 64);
    M_Animations[WALK_DOWN] = new Animation(Sprite, "../Resources/Sprites/MC/mc_frontwalk.png", 15.5f, 64);
    M_Animations[IDLE_UP] = new Animation(Sprite, "../Resources/Sprites/MC/mc_idle_back.png", 42.f, 64);
    M_Animations[IDLE_X] = new Animation(Sprite, "../Resources/Sprites/MC/mc_leftidle.png", 42.f, 64);
    M_Animations[IDLE_DOWN] = new Animation(Sprite, "../Resources/Sprites/MC/mc_frontidle.png", 42.f, 64);
    M_Animations[ATTACK_X] = new Animation(Sprite, "../Resources/Sprites/MC/mc_throw_left.png", 5.1f, 64);
    M_Animations[ATTACK_UP] = new Animation(Sprite, "../Resources/Sprites/MC/mc_throw_back.png", 5.1f, 64);
    M_Animations[ATTACK_DOWN] = new Animation(Sprite, "../Resources/Sprites/MC/mc_throw_front.png", 5.1f, 64);
    M_Animations[PROGRESS_X] = new Animation(Sprite, "../Resources/Sprites/MC/mc_progress_left.png", 24.f, 64);
    M_Animations[PROGRESS_UP] = new Animation(Sprite, "../Resources/Sprites/MC/mc_progress_back.png", 24.f, 64);
    M_Animations[PROGRESS_DOWN] = new Animation(Sprite, "../Resources/Sprites/MC/mc_progress_front.png", 24.f, 64);

    // *** Inventory *** //
    M_Inventory = new Inventory(Cvt.P2PX(4.3f), { Cvt.P2PX(38.7f), Cvt.P2PY(94.f) }, Font, I_UsedItem, EventQueue);
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
    // Change the state based on the item used
    if (M_Inventory->GetItemName() != "" )
    {
        // Player can't move
        ResetVelocity();

        if (M_Inventory->GetItemName() != "SandBag")
            if (Direction.x != 0.f)
                State = ATTACK_X;
            else if (Direction.y < 0.f)
                State = ATTACK_UP;
            else if (Direction.y > 0.f)
                State = ATTACK_DOWN;
    }

    // Use the item
    M_Inventory->UseItem(Sprite.getPosition(), Direction);
}

void Player::OnProgress(const bool Value)
{
    if (Value)
    {
        if (Direction.x != 0.f)
            State = PROGRESS_X;
        else if (Direction.y < 0.f)
            State = PROGRESS_UP;
        else if (Direction.y > 0.f)
            State = PROGRESS_DOWN;
    }
}

void Player::SetScale(const sf::Vector2f& Scale)
{
    Sprite.setScale(Scale);
}

void Player::SetState(enum EState I_State)
{
    State = I_State;
}

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void Player::OnUpdate(const float& DeltaTime)
{
    // Inheritance
    Entity::OnUpdate(DeltaTime);

    // *** Updating the Holding item *** //
    M_Inventory->OnUpdate(DeltaTime, GetPositionGrid(64.f), 64.f);

    // *** If the state is attacking, we will wait for the animation to finished *** //
    if (State == ATTACK_UP || State == ATTACK_DOWN || State == ATTACK_X)
        if (!M_Animations[State]->IsFinished())
            return;

    // *** Updating Idling State *** //
    if (M_Movement->GetVelocity() == sf::Vector2f() && Direction.y > 0.f)
        State = IDLE_DOWN;
    else if (M_Movement->GetVelocity() == sf::Vector2f() && Direction.y < 0.f)
        State = IDLE_UP;
    else if (M_Movement->GetVelocity() == sf::Vector2f() && Direction.x != 0.f)
        State = IDLE_X;
}

// \brief Draw SF drawable components to screen
void Player::OnDraw(sf::RenderWindow* Window, sf::Shader* Shader, bool ShowBox)
{
    Window->draw(Sprite);

    // Inheritance
    Entity::OnDraw(Window, Shader, ShowBox);
}

void Player::DrawInventory(sf::RenderWindow* Window)
{
    M_Inventory->OnDraw(Window);
}