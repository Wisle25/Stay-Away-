#include "stdpch.hpp"

#include "Map/TileSelector.hpp"
#include "UI/Components/Modal.hpp"

#include "EditorState.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
EditorState::EditorState(Context* I_Ctx):
    State(I_Ctx),
    ShowGrid(true),
    ShowSelector(true),
    ShowModal(false),
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
            Grid[x][y].setOutlineColor(sf::Color::White);
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
    Tileselector = new TileSelector(Cvt, Ctx->GridSize, Ctx->MainFont, &EventQueue);

    // Selector
    Selector.setSize(sf::Vector2f(Ctx->GridSize, Ctx->GridSize));
    Selector.setFillColor(sf::Color(255, 255, 255, 75));
    Selector.setOutlineThickness(2.f);
    Selector.setOutlineColor(sf::Color::Blue);
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
        if (Tileselector->IsActive() && ShowSelector)
        {
            // Getting data from tile selector
            std::map<std::string, std::string> TileData = Tileselector->GetData();

            // Parsing the data and pass it to the variable
            TextureFile = TileData["Texture"];
        }
        else
            Map->AddTile(MouseView, TextureFile, Type);
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
    switch (Event->key.code)
    {
    // Quit From State
    case sf::Keyboard::Escape:
        Is_Quit = true;
        break;

    // Show or unshow Tileselector
    case sf::Keyboard::H:
        ShowSelector = !ShowSelector;
        std::cout << ShowSelector << std::endl;
        break;
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

void EditorState::HandleButtons()
{
    // Quit btn
    Buttons["QUIT_BTN"]->OnClick([this]() {
        Quit();
        std::cout << "Im pressed" << std::endl;
    });
}

///////////// Lifecycle /////////////////

// \brief Handling input
void EditorState::OnInput(sf::Event* Event)
{
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
    HandleButtons();

    // Updating Selector and Preview posiiton
    Selector.setPosition(sf::Vector2f(MouseGrid) * Ctx->GridSize);

    // Updating Components
    Tileselector->OnUpdate(MouseWindow);

    for (auto& Btn : Buttons)
        Btn.second->OnUpdate(MouseWindow);
}

// \brief Draw SF drawable components to screen
void EditorState::OnDraw(sf::RenderWindow* Window)
{
    // *** Camera Based Position *** //
    Window->setView(*Camera);
    /* Draw Grid */
    for (unsh x = 0; x < MaxWorldSize.x; ++x)
        for (unsh y = 0; y < MaxWorldSize.y; ++y)
            Window->draw(Grid[x][y]);

    /* Map */
    Map->OnDraw(Window, MouseGrid);
    Map->DrawDefered(Window);

    /* Draw Selector */
    Window->draw(Selector);

    // *** Fixed Camera Based Position *** //
    Window->setView(Window->getDefaultView());
    if (ShowSelector) Tileselector->OnDraw(Window);

    for (auto& Btn : Buttons)
        Btn.second->OnDraw(Window);
}