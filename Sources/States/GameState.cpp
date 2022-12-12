#include "stdpch.hpp"

#include "Collectable/SandBag.hpp"
#include "Core/Vector.hpp"
#include "Core/Randomizer.hpp"
#include "Entities/Pocong.hpp"
#include "Map/TileMap.hpp"
#include "Skillchecks/Objective.hpp"
#include "Systems/Collision/Collision.hpp"
#include "UI/Custom/PlayerGUI.hpp"

#include "Hatch.hpp"
#include "GameState.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
GameState::GameState(Context* I_Ctx):
    State(I_Ctx),
    GhostAttackTimer(0.f),
    GhostAttackTimerMax(3.1f),
    GhostSpawnerTimer(0.f),
    GhostSpawnerTimerMax(15.f),
    ItemSpawnerTimer(0.f),
    ItemSpawnerTimerMax(20.f),
    Finished(false),
    M_Hatch(nullptr)
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

    for (auto& M_Ghost : Ghosts)
        delete M_Ghost;

    for (auto& M_Jumpscare : Jumpscares)
        delete M_Jumpscare.second;
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
    // *** Pure Map *** //
    Map = new TileMap("beautiful_revisi");

    // *** Objectives *** //
    for (unsh i = 0; i < 3; ++i)
    {
        Objectives.push_back(
            new Objective(
                Cvt,
                Ctx->SecondFont,
                { 0.9f, 0.9f },
                RandomizePosition(Map->GetMaxSize() * Ctx->GridSize)
            )
        );
    }
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
        .Position = RandomizePosition(Map->GetMaxSize() * Ctx->GridSize),

        // Attributes
        .HP = 100.f,
        .MaxHP = 100.f,
        .BaseDamage = 13.f,

        // Collider and HitBox
        .ColliderVertices = { { 0.f, 0.f }, { 23.f, 0.f }, { 23.f, 11.f }, { 0.f, 11.f } },
        .HitBoxVertices = { { 0.f, 0.f }, { 25.f, 0.f }, { 25.f, 55.f }, { 0.f, 55.f } }
    }, Cvt, Ctx->MainFont, &UsedItem, &EventQueue);

    // *** Initializing Enemies *** //
    // NOTE: Total of enemy is 9, so each enemy is 3
    /* Kuyang */
    for (unsh i = 0; i < 3; ++i)
    {
        // Kunti
        Ghosts.push_back(new Kunti({
            // Movement System (Assume 1 meter is equal to grid size)
            .MaxVelocity = 45.f,
            .Acceleration = 800.f,
            .Deceleration = 600.f,

            // Start Position
            .Position = RandomizePosition(Map->GetMaxSize() * Ctx->GridSize),

            // Attributes
            .HP = 100.f,
            .MaxHP = 100.f,
            .BaseDamage = 15.f,

            // Collider and HitBox
            .ColliderVertices = { { 0.f, 0.f }, { 24.f, 0.f }, { 24.f, 11.f }, { 0.f, 11.f } },
            .HitBoxVertices = { { 0.f, 0.f }, { 25.f, 0.f }, { 25.f, 55.f }, { 0.f, 55.f } }
        }));

        // Kuyang
        Ghosts.push_back(new Kuyang({
            // Movement System (Assume 1 meter is equal to grid size)
            .MaxVelocity = 49.f,
            .Acceleration = 800.f,
            .Deceleration = 600.f,

            // Start Position
            .Position = RandomizePosition(Map->GetMaxSize() * Ctx->GridSize),

            // Attributes
            .HP = 100.f,
            .MaxHP = 100.f,
            .BaseDamage = 11.f,

            // Collider and HitBox
            .ColliderVertices = { { 0.f, 0.f }, { 24.f, 0.f }, { 24.f, 11.f }, { 0.f, 11.f } },
            .HitBoxVertices = { { 0.f, 0.f }, { 25.f, 0.f }, { 25.f, 55.f }, { 0.f, 55.f } }
        }, Cvt, Ctx->SecondFont));

        Ghosts.push_back(new Pocong({
            // Movement System (Assume 1 meter is equal to grid size)
            .MaxVelocity = 39.f,
            .Acceleration = 800.f,
            .Deceleration = 600.f,

            // Start Position
            .Position = RandomizePosition(Map->GetMaxSize() * Ctx->GridSize),

            // Attributes
            .HP = 100.f,
            .MaxHP = 100.f,
            .BaseDamage = 19.5f,

            // Collider and HitBox
            .ColliderVertices = { { 0.f, 0.f }, { 24.f, 0.f }, { 24.f, 11.f }, { 0.f, 11.f } },
            .HitBoxVertices = { { 0.f, 0.f }, { 25.f, 0.f }, { 25.f, 55.f }, { 0.f, 55.f } }
        }));
    }
}

void GameState::InitializeGUI()
{
    // *** Player GUI *** //
    M_PlayerGUI = new PlayerGUI(Cvt, Ctx->SecondFont);

    // *** Jumpscare *** //
    Jumpscares["Kunti"] = new Jumpscare(Cvt, "../Resources/Sprites/Jumpscare/jumpscare_Kunti.png", { Cvt.P2PX(28.f), Cvt.P2PY(32.f) });
    Jumpscares["Kuyang"] = new Jumpscare(Cvt, "../Resources/Sprites/Jumpscare/jumpscare_Kuyang.png", { Cvt.P2PX(28.f), Cvt.P2PY(32.f) });
    Jumpscares["Pocong"] = new Jumpscare(Cvt, "../Resources/Sprites/Jumpscare/jumpscare_Pocong.png", { Cvt.P2PX(22.f), Cvt.P2PY(26.8f) });
}

void GameState::InitializeItems()
{
    // *** NOTE: Each items can be found in 5 random location *** //
    for (unsh i = 0; i < 5; ++i)
    {
        // *** Knife *** //
        std::vector<Collectable*> Knifes;

        for (unsh j = 0; j < 15; ++j)
            Knifes.push_back(new Knife(
                { 0.65f, 0.65f }, // Scaling
                RandomizePosition(Map->GetMaxSize() * Ctx->GridSize),
                Randomize<float>(0.f, 360.f) // Rotation Angle
            ));

        Items.push_back(Knifes);

        // *** Nail *** //
        std::vector<Collectable*> Nails;

        for (unsh j = 0; j < 15; ++j)
            Nails.push_back(new Nail(
                { 0.85f, 0.85f },
                RandomizePosition(Map->GetMaxSize() * Ctx->GridSize),
                Randomize<float>(0.f, 360.f) // Rotation Angle
            ));

        Items.push_back(Nails);

                // *** Nail *** //
        std::vector<Collectable*> SandBags;

        for (unsh j = 0; j < 15; ++j)
            SandBags.push_back(new SandBag(
                { 0.65f, 0.65f },
                RandomizePosition(Map->GetMaxSize() * Ctx->GridSize),
                Randomize<float>(0.f, 360.f) // Rotation Angle
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
            Event->key.code == sf::Keyboard::F               &&
            !M_Player->IsFull() /* We will add the item if it's not full */
        )
        {
            M_Player->AddItem(Items[i]);
            Items.erase(Items.begin() + i);
        }
    }
}

void GameState::HandleInputPlayer(const float& DeltaTime)
{
    // If the player is on attacking or progress doing something, he can't move
    if (M_Player->GetState() >= 6 && M_Player->GetState() <= 11)
        return;

    // Sprinting
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
        M_Player->GetAttribute()->Stamina >= 0.f
    )
    {
        // Add max velocity and also decreasing the stamina
        M_Player->SetMaxVelocity(210.f);
        M_Player->GetAttribute()->Stamina -= std::clamp(10.f * DeltaTime, 0.f, 100.f);
    }
    else
    {
        // Reset to default max velocity and increasing stamina
        M_Player->SetMaxVelocity(0.f);

        if (M_Player->GetAttribute()->Stamina <= 100.f)
            M_Player->GetAttribute()->Stamina += std::clamp(15.f * DeltaTime, 0.f, 100.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        M_Player->Move({ 0.f, -1.f }, DeltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        M_Player->Move({ 0.f, 1.f }, DeltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        M_Player->Move({ 1.f, 0.f }, DeltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        M_Player->Move({ -1.f, 0.f }, DeltaTime);
}

void GameState::UpdateInteractable(const float& DeltaTime)
{
    // *** Checking for the interactable object *** //
    /* Kuyang Body */
    for (unsh i = 0; i < Ghosts.size(); ++i)
    {
        if (Ghosts[i]->GetName() == "Kuyang"                          &&
            M_Player->GetItemName() == "SandBag"                      &&
            sf::Mouse::isButtonPressed(sf::Mouse::Left)               &&
            Ghosts[i]->GetBody()->InBoundary(M_Player->GetPosition())
        )
        {
            Ghosts[i]->SetCleaned(true);

            M_Player->ResetVelocity();
            M_Player->OnProgress(true);
        }
        else
        {
            M_Player->OnProgress(false);
            Ghosts[i]->SetCleaned(false);
        }
    }

    /* Objectives */
    for (unsh i = 0; i < Objectives.size(); ++i)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)               &&
            Objectives[i]->InBoundary(M_Player->GetPosition())
        )
        {
            M_Player->ResetVelocity();
            M_Player->OnProgress(true);

            Objectives[i]->SetOnProgress(true);
            Objectives[i]->OnUpdate(DeltaTime);

            // We will remove the objective once the player successfully remove it
            if (Objectives[i]->IsCompleted())
            {
                delete Objectives[i];
                Objectives.erase(Objectives.begin() + i);
            }
        }
        else
        {
            M_Player->OnProgress(false);
            Objectives[i]->SetOnProgress(false);
        }
    }
}

// \brief Handling Combat System
void GameState::HandleCombat(const float& DeltaTime)
{
    // Player Attacking
    for (unsh i = 0; i < UsedItem.size(); ++i)
        for (auto& M_Ghost : Ghosts)
            if (M_Ghost    ->GetName()     != "Kuyang"                   &&
                UsedItem[i]->GetName()     != "SandBag"                  &&
                Collision(UsedItem[i]->GetHitbox(), M_Ghost->GetHitBox())
            )
            {
                // Get Damage from player and item
                float BaseDamage = M_Player->GetAttribute()->BaseDamage;
                float ItemDamage = UsedItem[i]->GetDamage();

                // Randomize damage
                float RandBaseDamage = (BaseDamage - 7) + (rand() % short((BaseDamage + 8) - (BaseDamage - 7) + 1));
                float RandItemDamage = (ItemDamage - 7) + (rand() % short((ItemDamage + 8) - (ItemDamage - 7) + 1));

                M_Ghost->GetAttribute()->LoseHP(RandBaseDamage);

                // Will have crit damage if the item is ghost's weakness
                if (UsedItem[i]->GetName() == "Nail" && M_Ghost->GetName() == "Kunti")
                    M_Ghost->GetAttribute()->LoseHP(RandItemDamage * 1.3f);

                if (UsedItem[i]->GetName() == "Knife" && M_Ghost->GetName() == "Pocong")
                    M_Ghost->GetAttribute()->LoseHP(RandItemDamage * 1.3f);

                // delete the item that hit the ghost
                delete UsedItem[i];
                UsedItem.erase(UsedItem.begin() + i);
                break;
            }

    // Ghost Attacking
    if (GhostAttackTimer <= GhostAttackTimerMax)
        GhostAttackTimer += 1.f * DeltaTime;

    for (auto& M_Ghost : Ghosts)
        if (GhostAttackTimer >= GhostAttackTimerMax)
            if (Collision(M_Player->GetHitBox(), M_Ghost->GetHitBox()))
            {
                // Get Damage from player and item
                float BaseDamage = M_Ghost->GetAttribute()->BaseDamage;
                float RandBaseDamage = (BaseDamage - 7) + (rand() % short((BaseDamage + 8) - (BaseDamage - 7) + 1));

                M_Player->GetAttribute()->LoseHP(RandBaseDamage);

                GhostName = M_Ghost->GetName();

                // Reset the timer
                GhostAttackTimer = 0.f;
            }
}

void GameState::HandleCamera()
{
    // ******** Updating Camera so it always follow player and the cursor ******** //
    // Screen size
    sf::Vector2f Screen(Ctx->Settings->Resolution.width, Ctx->Settings->Resolution.height);

    // Updating camera center
    float Camera_x = M_Player->GetPosition().x + (static_cast<float>(MouseWindow.x) - Screen.x / 2.f) / 7.f;
    float Camera_y = M_Player->GetPosition().y + (static_cast<float>(MouseWindow.y) - Screen.y / 2.f) / 7.f;

    // We're using clamp so the Camera will not going out of the world boundaries
    Camera->setCenter(
        std::floor(std::clamp(Camera_x, Camera->getSize().x / 2.f, Map->GetMaxSize().x * Ctx->GridSize - Camera->getSize().x / 2.f)),
        std::floor(std::clamp(Camera_y, Camera->getSize().y / 2.f, Map->GetMaxSize().y * Ctx->GridSize - Camera->getSize().y / 2.f))
    );
    // ******** END ******** //
}

// \brief A Function to handle ghost spawning
void GameState::SpawnGhost(const float& DeltaTime)
{
    if (GhostSpawnerTimer <= GhostSpawnerTimerMax)
        GhostSpawnerTimer += 1.f * DeltaTime;
    else if (Ghosts.size() < 9)
    {
        // Spawn a random type of ghost
        unsh Type = Randomize<unsh>(1, 3);

        // Reset the timer
        GhostSpawnerTimer = 0.f;

        switch (Type)
        {
        case 1:
            // Kunti
            Ghosts.push_back(new Kunti({
                // Movement System (Assume 1 meter is equal to grid size)
                .MaxVelocity = 45.f,
                .Acceleration = 800.f,
                .Deceleration = 600.f,

                // Start Position
                .Position = RandomizePosition(Map->GetMaxSize() * Ctx->GridSize),

                // Attributes
                .HP = 100.f,
                .MaxHP = 100.f,
                .BaseDamage = 15.f,

                // Collider and HitBox
                .ColliderVertices = { { 0.f, 0.f }, { 24.f, 0.f }, { 24.f, 11.f }, { 0.f, 11.f } },
                .HitBoxVertices = { { 0.f, 0.f }, { 25.f, 0.f }, { 25.f, 55.f }, { 0.f, 55.f } }
            }));
            break;

        case 2:
            // Kuyang
            Ghosts.push_back(new Kuyang({
                // Movement System (Assume 1 meter is equal to grid size)
                .MaxVelocity = 49.f,
                .Acceleration = 800.f,
                .Deceleration = 600.f,

                // Start Position
                .Position = RandomizePosition(Map->GetMaxSize() * Ctx->GridSize),

                // Attributes
                .HP = 100.f,
                .MaxHP = 100.f,
                .BaseDamage = 11.f,

                // Collider and HitBox
                .ColliderVertices = { { 0.f, 0.f }, { 24.f, 0.f }, { 24.f, 11.f }, { 0.f, 11.f } },
                .HitBoxVertices = { { 0.f, 0.f }, { 25.f, 0.f }, { 25.f, 55.f }, { 0.f, 55.f } }
            }, Cvt, Ctx->SecondFont));
            break;

        case 3:
            // Pocong
            Ghosts.push_back(new Pocong({
                // Movement System (Assume 1 meter is equal to grid size)
                .MaxVelocity = 39.f,
                .Acceleration = 800.f,
                .Deceleration = 600.f,

                // Start Position
                .Position = RandomizePosition(Map->GetMaxSize() * Ctx->GridSize),

                // Attributes
                .HP = 100.f,
                .MaxHP = 100.f,
                .BaseDamage = 19.5f,

                // Collider and HitBox
                .ColliderVertices = { { 0.f, 0.f }, { 24.f, 0.f }, { 24.f, 11.f }, { 0.f, 11.f } },
                .HitBoxVertices = { { 0.f, 0.f }, { 25.f, 0.f }, { 25.f, 55.f }, { 0.f, 55.f } }
            }));
            break;
        }
    }

}

// \brief A Function to handle items spawning
void GameState::SpawnItem(const float& DeltaTime)
{
    if (ItemSpawnerTimer <= ItemSpawnerTimerMax)
        ItemSpawnerTimer += 1.f * DeltaTime;
    else if (Items.size() < 15)
    {
        // Spawn a random type of ghost
        unsh Type = Randomize<unsh>(1, 3);

        // Reset the timer
        GhostSpawnerTimer = 0.f;

        switch (Type)
        {
        case 1:
        {
            // *** Knife *** //
            std::vector<Collectable*> Knifes;

            for (unsh j = 0; j < 15; ++j)
                Knifes.push_back(new Knife(
                    { 0.65f, 0.65f }, // Scaling
                    RandomizePosition(Map->GetMaxSize() * Ctx->GridSize),
                    Randomize<float>(0.f, 360.f) // Rotation Angle
                ));

            Items.push_back(Knifes);
            break;
        }

        case 2:
        {
            // *** Nail *** //
            std::vector<Collectable*> Nails;

            for (unsh j = 0; j < 15; ++j)
                Nails.push_back(new Nail(
                    { 0.85f, 0.85f },
                    RandomizePosition(Map->GetMaxSize() * Ctx->GridSize),
                    Randomize<float>(0.f, 360.f) // Rotation Angle
                ));

            Items.push_back(Nails);
            break;
        }

        case 3:
        {
            // *** Nail *** //
            std::vector<Collectable*> SandBags;

            for (unsh j = 0; j < 15; ++j)
                SandBags.push_back(new SandBag(
                    { 0.65f, 0.65f },
                    RandomizePosition(Map->GetMaxSize() * Ctx->GridSize),
                    Randomize<float>(0.f, 360.f) // Rotation Angle
                ));

            Items.push_back(SandBags);
            break;
        }
        }
    }
}

// \brief A Function to handle hatch spawning and updating it
void GameState::SpawnHatch()
{
    // We will spawn the hatch once the objective is clear
    if (Objectives.size() <= 0)
        M_Hatch = new Hatch({1.f, 1.f}, RandomizePosition(Map->GetMaxSize() * Ctx->GridSize));

    // If the player entering the hatch by pressinf F
    if (M_Hatch                                      &&
        M_Hatch->InBoundary(M_Player->GetPosition()) &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::F)
    )
        Finished = true;
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
    if (M_Player->GetAttribute()->Dead())
    {
        if (Jumpscares[GhostName]->OnUpdate(DeltaTime))
        {
            Quit();
            Ctx->Window->setMouseCursorVisible(true);
        }

        return;
    }

    // Inheritance
    State::OnUpdate(DeltaTime);

    // *** Handling Input to control player *** //
    HandleCamera     ();
    HandleInputPlayer(DeltaTime);
    HandleCombat     (DeltaTime);
    SpawnGhost       (DeltaTime);
    SpawnItem        (DeltaTime);
    SpawnHatch       ();

    // *** Updating Entities and Collision *** //
    /* Player */
    M_Player->OnUpdate(DeltaTime);

    sf::Vector2f P_MTV;

    Map->OnCollision(M_Player, P_MTV);

    /* Ghosts */
    for (unsh i = 0; i < Ghosts.size(); ++i)
    {
        Ghosts[i]->OnUpdate(DeltaTime, M_Player->GetPosition());

        // If ghost is dead we will simply delete the ghost from the world :)
        if (Ghosts[i]->GetAttribute()->Dead())
        {
            Ghosts[i]->SetOpacity(240.f * DeltaTime);

            if (Ghosts[i]->GetOpacity() <= 1)
            {
                delete Ghosts[i];
                Ghosts.erase(Ghosts.begin() + i);

                continue;
            }
        }

        // If the ghost hit collision, we will change the direction based on the MTV
        sf::Vector2f G_MTV;
        if (Map->OnCollision(Ghosts[i], G_MTV))
            Ghosts[i]->SetDirection(G_MTV);
    }
    // *** END *** //

    // *** Updating Items *** //
    UpdateInteractable(DeltaTime);

    // *** Updating GUI *** //
    M_PlayerGUI->OnUpdate(M_Player->GetAttribute());
}

// \brief Draw SF drawable components to screen
void GameState::OnDraw(sf::RenderWindow* Window)
{
    // *** Camera Based Position *** //
    /* If the player is dead, we will draw the jumpscare */
    if (M_Player->GetAttribute()->Dead())
    {
        Jumpscares[GhostName]->OnDraw(Window);
        return;
    }

    Window->setView(*Camera);

    /* Drawing Map */
    Map->OnDraw(
        Window,
        nullptr,
        sf::Vector2s(Camera->getCenter() / Ctx->GridSize),
        M_Player->GetCenter()
    );

    /* Items */
    for (auto& M_Item : Items)
        M_Item[0]->OnDraw(Window);

    /* Ghosts */
    for (auto& M_Ghost : Ghosts)
        M_Ghost->OnDraw(Window, nullptr, false);

    /* Objectives (Grave) */
    for (auto& M_Objective : Objectives)
        M_Objective->OnDraw(Window);

    /* Hatch */
    if (M_Hatch)
        M_Hatch->OnDraw(Window);

    /* Player */
    M_Player->OnDraw(Window, nullptr, false);

    Map->DrawDefered(
        Window,
        nullptr,
        M_Player->GetCenter()
    );

    // *** Window Based Position *** //
    Window->setView(Window->getDefaultView());
    M_PlayerGUI->OnDraw(Window);
    M_Player->DrawInventory(Window);
}