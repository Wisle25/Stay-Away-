#include "stdpch.hpp"

#include "Map/TileSelector.hpp"
#include "UI/Components/Modal.hpp"
#include "UI/Custom/CollisionAdder.hpp"

#include "EditorState.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
EditorState::EditorState(Context* I_Ctx):
    State(I_Ctx),
    ShowGrid(true),
    ShowSelector(true),
    ShowModal(false),
    Collision(false),
    Type(NORMAL)
{
    // Initializing Variables
    MaxWorldSize.x = 30;
    MaxWorldSize.y = 17;

    // Initializing Components
    InitializeGrid();
    InitializeCamera();
    InitializeSelector();
    InitializeButtons();
    InitializeComponents();
}

EditorState::~EditorState()
{
    delete M_TileSelector;
    delete M_CollisionAdder;
    delete Camera;
    delete Map;

    for (auto& Btn : Buttons)
        delete Btn.second;

    for (auto& M_Modal : Modals)
        delete M_Modal.second;
}

///////////// Private Methods (Initializer) /////////////

void EditorState::InitializeGrid()
{
    // Fill the screen with Grid
    Grid.resize(MaxWorldSize.x, std::vector<sf::RectangleShape>());
    for (unsh x = 0; x < MaxWorldSize.x; ++x)
    {
        for (unsh y = 0; y < MaxWorldSize.y; ++y)
        {
            Grid[x].push_back(sf::RectangleShape());
            Grid[x][y].setSize(sf::Vector2f(Ctx->GridSize, Ctx->GridSize));
            Grid[x][y].setFillColor(sf::Color::Transparent);
            Grid[x][y].setOutlineColor(sf::Color::Green);
            Grid[x][y].setOutlineThickness(-0.5f);
            Grid[x][y].setPosition(sf::Vector2f(x * Ctx->GridSize, y * Ctx->GridSize));
        }
    }
}

void EditorState::InitializeCamera()
{
    Camera = new sf::View();
    Camera->setSize(Ctx->Settings->Resolution.width, Ctx->Settings->Resolution.height);
    Camera->setCenter(
        Ctx->Settings->Resolution.width / 2.f,
        Ctx->Settings->Resolution.height / 2.f
    );
}

void EditorState::InitializeSelector()
{
    // Tile Selector
    M_TileSelector = new TileSelector(Cvt, Ctx->GridSize, Ctx->MainFont, &EventQueue);

    // Selector
    Selector.setSize(sf::Vector2f(Ctx->GridSize, Ctx->GridSize));
    Selector.setFillColor(sf::Color(255, 255, 255, 75));
    Selector.setOutlineThickness(2.f);
    Selector.setOutlineColor(sf::Color::Blue);

    // Selector Text Info
    SelectorInfo.setFont(Ctx->SecondFont);
    SelectorInfo.setCharacterSize(Cvt.P2PChar(136));
    SelectorInfo.setOrigin(
        SelectorInfo.getLocalBounds().left + SelectorInfo.getLocalBounds().width / 2.f,
        SelectorInfo.getLocalBounds().top + SelectorInfo.getLocalBounds().height / 2.f
    );
    SelectorInfo.setPosition({ Cvt.P2PX(80.f), Cvt.P2PY(47.f) });

    // Collision Adder
    M_CollisionAdder = new CollisionAdder(Cvt, Ctx->MainFont, &EventQueue);
}

void EditorState::InitializeButtons()
{
    Buttons["SAVE_BTN"] = new Button({
        .Size = { Cvt.P2PX(10.f), Cvt.P2PY(5.f) },
        .Position = { Cvt.P2PX(70.f), Cvt.P2PY(91.3f) },
        .Font = Ctx->SecondFont,
        .CharSize = Cvt.P2PChar(105),
        .Text = "Save Map"
    }, &EventQueue);

    Buttons["LOAD_BTN"] = new Button({
        .Size = { Cvt.P2PX(10.f), Cvt.P2PY(5.f) },
        .Position = { Cvt.P2PX(81.f), Cvt.P2PY(91.3f) },
        .Font = Ctx->SecondFont,
        .CharSize = Cvt.P2PChar(105),
        .Text = "Load Map"
    }, &EventQueue);

    Buttons["QUIT_BTN"] = new Button({
        .Size = { Cvt.P2PX(10.f), Cvt.P2PY(5.f) },
        .Position = { Cvt.P2PX(92.f), Cvt.P2PY(91.3f) },
        .Font = Ctx->SecondFont,
        .CharSize = Cvt.P2PChar(105),
        .Text = "Quit"
    }, &EventQueue);

    for (auto& Btn : Buttons)
    {
        Btn.second->SetOutline(Ctx->SecondColor, 2.5f);
        Btn.second->SetColors({
            .IdleColor = Ctx->MainColor,
            .HoverColor = sf::Color(166, 35, 73),
            .ActiveColor = sf::Color(99, 6, 6),
            .TextColor = sf::Color::White
        });
    }
}

void EditorState::InitializeComponents()
{
    // *** Map *** //
    Map = new TileMap(Ctx->GridSize, MaxWorldSize);

    // *** Modals *** //
    Modals["SAVE_MODAL"] = new Modal({
        .Size = { Cvt.P2PX(40.f), Cvt.P2PY(29.6f) },
        .Position = { Cvt.P2PX(50.f), Cvt.P2PY(50.f) },
        .Font = Ctx->MainFont,
        .HeaderText = "Save Map",
        .ContentText = "Save your beautiful map here"
    }, &EventQueue);

    Modals["LOAD_MODAL"] = new Modal({
        .Size = { Cvt.P2PX(40.f), Cvt.P2PY(29.6f) },
        .Position = { Cvt.P2PX(50.f), Cvt.P2PY(50.f) },
        .Font = Ctx->MainFont,
        .HeaderText = "Load Map",
        .ContentText = "Feels want to edit existed map? Load Map here"
    }, &EventQueue);

    for (auto& M_Modal : Modals)
        M_Modal.second->SetContainerOutline(sf::Color(124, 22, 46), 2.f);
}

///////////// Private Methods (Input Handler) /////////////

// \brief Handling Input from Mouse Device
void EditorState::MouseInputHandler(sf::Event* Event)
{
    // ***  Select or Adding Tile *** //
    if (Event->mouseButton.button == sf::Mouse::Left &&
        !Buttons["SAVE_BTN"]->GetGlobalBounds().contains(MouseView) &&
        !Buttons["LOAD_BTN"]->GetGlobalBounds().contains(MouseView) &&
        !Buttons["QUIT_BTN"]->GetGlobalBounds().contains(MouseView)
    )
    {
        if (M_TileSelector->IsActive() && ShowSelector)
        {
            // Getting data from tile selector
            std::map<std::string, std::string> TileData = M_TileSelector->GetData();

            // Parsing the data and pass it to the variable
            std::string Name = TileData["Name"];
            TextureFile = TileData["Texture"];

            // Set the vertices by name
            Map->SetVertices(
                M_CollisionAdder->FindVerticesByName(Name)
            );
        }
        else if (M_CollisionAdder->GetState() < 1 && // The state is either FINISHED or ADDING
                !M_CollisionAdder->GetBounds().contains(MouseView)
        )
            Map->AddTile(MouseView, TextureFile, ShowGrid, Collision, Type);
    }
    // *** END *** //

    // ***  Select or Adding Tile *** //
    if (Event->mouseButton.button == sf::Mouse::Right &&
        !Buttons["SAVE_BTN"]->GetGlobalBounds().contains(MouseView) &&
        !Buttons["LOAD_BTN"]->GetGlobalBounds().contains(MouseView) &&
        !Buttons["QUIT_BTN"]->GetGlobalBounds().contains(MouseView)
    )
        Map->RemoveTile(MouseView);
    // *** END *** //
}

// \brief Handling Input from Keyboard Device
void EditorState::KeyboardInputHandler(sf::Event* Event)
{
    if (Event->key.code == sf::Keyboard::Escape)
        Is_Quit = true;

    // Show or Hide Grid
    if (Event->key.control && Event->key.code == sf::Keyboard::H)
        ShowSelector = !ShowSelector;

    // Show or Hide Grid
    if (Event->key.control && Event->key.code == sf::Keyboard::G)
        ShowGrid = !ShowGrid;

    if (Event->key.alt && Event->key.code == sf::Keyboard::C)
        Collision = !Collision;

    if (Event->key.alt && Event->key.code == sf::Keyboard::F)
    {
        ++Type;
        if (Type > 2)
            Type = 0;
    }
}

///////////// Private Methods (Updater) /////////////

// \brief function that zooms a view at a specified pixel rather than the centre of the window/view.
void EditorState::ZoomCameraAt(sf::Vector2i pixel, float zoom)
{
	const sf::Vector2f beforeCoord{ Ctx->Window->mapPixelToCoords(pixel) };

	Camera->zoom(zoom);

	const sf::Vector2f afterCoord{ Ctx->Window->mapPixelToCoords(pixel) };
	const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };

    Camera->move(offsetCoords);
}

void EditorState::UpdateMousePosition()
{
    MouseGrid = sf::Vector2s(
        static_cast<short>(MouseView.x) / static_cast<short>(Ctx->GridSize),
        static_cast<short>(MouseView.y) / static_cast<short>(Ctx->GridSize)
    );
}

void EditorState::UpdateSelectorInfo()
{
    std::stringstream IS; // Info String Stream
    std::string tile_type_str[2] = { "Normal", "Defered" };
    std::string collision_str[2] = { "OFF", "ON" };

    IS << "Position: " << MouseView.x << " x " << MouseView.y << std::endl
       << "Total Layer: " << Map->GetLayerSize(MouseGrid) << std::endl
       << "Current Collision Status: " << collision_str[Collision] << std::endl
       << "Current Tile Type: " << tile_type_str[Type];

    SelectorInfo.setString(IS.str());
}

void EditorState::HandleButtons()
{
    Buttons["SAVE_BTN"]->OnClick([this]() {
        ModalName = "SAVE_MODAL";
        ShowModal = true;
    });

    Buttons["LOAD_BTN"]->OnClick([this]() {
        ModalName = "LOAD_MODAL";
        ShowModal = true;
    });

    // Quit btn
    Buttons["QUIT_BTN"]->OnClick([this]() {
        Quit();
    });
}

void EditorState::HandleModals()
{
    Modals["SAVE_MODAL"]->OnContinue([this]() {
        // Save Map to the file
        std::string MapName = Modals["SAVE_MODAL"]->GetInput();

        Map->SaveToFile(MapName);

        // Reset the modal
        ShowModal = false;
    });

    Modals["LOAD_MODAL"]->OnContinue([this]() {
        // Load Map to the file
        std::string MapName = Modals["LOAD_MODAL"]->GetInput();

        Map->LoadFromFile(MapName);

        // Reset the modal
        ShowModal = false;
    });
    // Do nothing when it's canceled
    Modals[ModalName]->OnCancel([this]() {
        ShowModal = false;
    });
}

///////////// Lifecycle /////////////////

// \brief Handling input
void EditorState::OnInput(sf::Event* Event)
{
    if (ShowModal)
        return;

    if (Event->type == sf::Event::MouseButtonPressed)
        MouseInputHandler(Event);
    else if (Event->type == sf::Event::MouseWheelScrolled)
    {
        // *** Zoom in-out Camera *** //
        if (Event->mouseWheelScroll.delta > 0)
            ZoomCameraAt({ Event->mouseWheelScroll.x, Event->mouseWheelScroll.y }, 1.f / 1.05);
        else if (Event->mouseWheelScroll.delta < 0)
            ZoomCameraAt({ Event->mouseWheelScroll.x, Event->mouseWheelScroll.y }, 1.05);
    }
    else if (Event->type == sf::Event::KeyPressed)
        KeyboardInputHandler(Event);
}

// \brief Called every frame, apply game logic here
void EditorState::OnUpdate(const float& DeltaTime)
{
    // Inheritance
    State::OnUpdate(DeltaTime);

    // *** Updating Modals *** //
    if (ShowModal)
    {
        HandleModals();
        Modals[ModalName]->OnUpdate(MouseWindow);

        return;
    }

    // If Collision adder's state is finished, then we wont update editor state
    if (M_CollisionAdder->GetState() == FINISHED)
    {
        // But keep updating Collision Adder
        M_CollisionAdder->OnUpdate(MouseWindow, MouseView);
        return;
    }

    // Camera moving directions
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        Camera->move(550.f * -1.f * DeltaTime, 0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        Camera->move(550.f * 1.f * DeltaTime, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        Camera->move(0, 550.f * -1.f * DeltaTime);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        Camera->move(0, 550.f * 1.f * DeltaTime);

    UpdateMousePosition();
    UpdateSelectorInfo();
    HandleButtons();

    // Updating Selector and Preview posiiton
    Selector.setPosition(sf::Vector2f(MouseGrid) * Ctx->GridSize);

    // Updating Components
    M_TileSelector->OnUpdate(MouseWindow);
    M_CollisionAdder->OnUpdate(MouseWindow, MouseView);

    for (auto& Btn : Buttons)
        Btn.second->OnUpdate(MouseWindow);
}

// \brief Draw SF drawable components to screen
void EditorState::OnDraw(sf::RenderWindow* Window)
{
    // *** Camera Based Position *** //
    Window->setView(*Camera);
    /* Draw Grid */
    if (ShowGrid)
        for (unsh x = 0; x < MaxWorldSize.x; ++x)
            for (unsh y = 0; y < MaxWorldSize.y; ++y)
                Window->draw(Grid[x][y]);

    /* Map */
    Map->OnDraw(Window, MouseGrid, true);
    Map->DrawDefered(Window);

    /* Draw Selector */
    Window->draw(Selector);

    // *** Fixed Camera Based Position *** //
    Window->setView(Window->getDefaultView());

    if (ShowSelector)
    {
        M_TileSelector->OnDraw(Window);
        M_CollisionAdder->OnDraw(Window, Camera);
        Window->draw(SelectorInfo);
    }

    for (auto& Btn : Buttons)
        Btn.second->OnDraw(Window);

    if (ShowModal)
            Modals[ModalName]->OnDraw(Window);
}