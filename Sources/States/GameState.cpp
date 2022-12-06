#include "stdpch.hpp"

#include "Core/Vector.hpp"

#include "Map/TileMap.hpp"

// It also include Knife, Nail
#include "Collectable/SandBag.hpp"

#include "Entities/Player.hpp"

#include "UI/Custom/PlayerGUI.hpp"

#include "GameState.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
GameState::GameState(Context* I_Ctx):
    State(I_Ctx)
{
    // Remove mouse cursor
    Ctx->Window->setMouseCursorVisible(false);

    InitializeCamera();
    InitializeMap();
    InitializeEntities();
    InitializeGUI();
    InitializeItems();
}

GameState::~GameState()
{
    delete Camera;
    delete Map;
    delete M_Player;
    delete M_PlayerGUI;

    for (unsh i = 0; i < Items.size(); ++i)
        for (unsh j = 0; j < Items[i].size(); ++j)
            delete Items[i][j];
}

///////////// Private Methods (Initializer) /////////////

// \brief Initializing Entities such as Player, Enemy, etc

void GameState::InitializeCamera()
{
    Camera = new sf::View();
    Camera->setSize(Ctx->Settings->Resolution.width, Ctx->Settings->Resolution.height);
    Camera->setCenter(
        Ctx->Settings->Resolution.width / 2.f,
        Ctx->Settings->Resolution.height / 2.f
    );
}

void GameState::InitializeMap()
{
    Map = new TileMap("Test");
}

void GameState::InitializeEntities()
{
    // *** Initializing Player *** //
    M_Player = new Player({
        // Movement System (Assume 1 meter is equal to grid size)
        .MaxVelocity = 120.f,
        .Acceleration = 1000.f,
        .Deceleration = 800.f,

        // Start Position
        .Position = { 862.f, 420.f },

        // Attributes
        .HP = 100.f,
        .MaxHP = 100.f,
        .BaseDamage = 13.f,

        // Collider and HitBox
        .ColliderVertices = { { 0.f, 0.f }, { 23.f, 0.f }, { 23.f, 11.f }, { 0.f, 11.f } },
        .HitBoxVertices = { { 0.f, 0.f }, { 25.f, 0.f }, { 25.f, 55.f }, { 0.f, 55.f } }
    }, Cvt, Ctx->MainFont, &EventQueue);
}

void GameState::InitializeGUI()
{
    // *** Player GUI *** //
    M_PlayerGUI = new PlayerGUI(Cvt, Ctx->SecondFont);
}

void GameState::InitializeItems()
{
    // *** NOTE: Each items can be found in 10 random location *** //

    for (unsh i = 0; i < 1; ++i)
    {
        // *** Knife *** //
        std::vector<Collectable*> Knifes;

        for (unsh j = 0; j < 15; ++j)
            Knifes.push_back(new Knife(
                { 0.65f, 0.65f },
                { 800.f, 470.f },
                30
            ));

        Items.push_back(Knifes);

        // *** Nail *** //
        std::vector<Collectable*> Nails;

        for (unsh j = 0; j < 15; ++j)
            Nails.push_back(new Nail(
                { 0.85f, 0.85f },
                { 800.f, 360.f },
                30
            ));

        Items.push_back(Nails);

                // *** Nail *** //
        std::vector<Collectable*> SandBags;

        for (unsh j = 0; j < 1; ++j)
            SandBags.push_back(new SandBag(
                { 0.35f, 0.35f },
                { 820.f, 370.f },
                80
            ));

        Items.push_back(SandBags);
    }
}

///////////// Private Methods (Input Handler) /////////////

// \brief Handling Input from Mouse Device
void GameState::MouseInputHandler(sf::Event* Event)
{
    if (Event->mouseButton.button == sf::Mouse::Left)
    {
        M_Player->UseItem();
    }
}

// \brief Handling Input from Keyboard Device
void GameState::KeyboardInputHandler(sf::Event* Event)
{
    // *** Picking up the Item *** //
    for (unsh i = 0; i < Items.size(); ++i)
    {
        // We will pick it once the player is in the item boundary
        if (Items[i][0]->InBoundary(M_Player->GetPosition()) &&
            Event->key.code == sf::Keyboard::F
        )
        {
            M_Player->AddItem(Items[i]);
            Items.erase(Items.begin() + i);
        }
    }
}

void GameState::HandleInputPlayer(const float& DeltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        M_Player->Move({ 0.f, -1.f }, DeltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        M_Player->Move({ 0.f, 1.f }, DeltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        M_Player->Move({ 1.f, 0.f }, DeltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        M_Player->Move({ -1.f, 0.f }, DeltaTime);
}

void GameState::HandleUpdateItems()
{
}

///////////// Lifecycle /////////////////

// \brief Handling input
void GameState::OnInput(sf::Event* Event)
{
    if (Event->type == sf::Event::MouseButtonPressed)
        MouseInputHandler(Event);
    else if (Event->type == sf::Event::KeyPressed)
        KeyboardInputHandler(Event);
}

// \brief Called every frame, apply game logic here
void GameState::OnUpdate(const float& DeltaTime)
{
    // Inheritance
    State::OnUpdate(DeltaTime);

    // *** Handling Input to control player *** //
    HandleInputPlayer(DeltaTime);

    // *** Updating Entities *** //
    M_Player->OnUpdate(DeltaTime);
    Map->OnCollision(M_Player);

    // *** Updating Items *** //
    HandleUpdateItems();

    // *** Updating GUI *** //
    M_PlayerGUI->OnUpdate(M_Player->GetAttribute());
}

// \brief Draw SF drawable components to screen
void GameState::OnDraw(sf::RenderWindow* Window)
{
    // *** Camera Based Position *** //
    Window->setView(*Camera);

    Map->OnDraw(
        Window,
        sf::Vector2s(Camera->getCenter() / Ctx->GridSize),
        true,
        nullptr,
        M_Player->GetCenter()
    );

    /* Items */
    for (auto& M_Item : Items)
        M_Item[0]->OnDraw(Window);

    M_Player->OnDraw(Window, nullptr, true);

    // *** Window Based Position *** //
    Window->setView(Window->getDefaultView());
    M_PlayerGUI->OnDraw(Window);
}