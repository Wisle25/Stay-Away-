#include "stdpch.hpp"

#include "GameState.hpp"
#include "MainMenuState.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
MainMenuState::MainMenuState(Context* I_Ctx):
    State(I_Ctx),
    MusicPlayed(true)
{
    // *** Initializing Background *** //
    InitializeBackground();

    // *** Initializing UI Components *** //
    // New Game button
    Buttons["GAMESTATE_BTN"] = new Button({
        .Size = sf::Vector2f(Cvt.P2PX(8.f), Cvt.P2PY(5.f)),
        .Position = sf::Vector2f(Cvt.P2PX(30.f), Cvt.P2PY(78.f)),
        .Font = Ctx->SecondFont,
        .CharSize = Cvt.P2PChar(111),
        .Text = "Start Game"
    }, &EventQueue);

    Buttons["QUIT_BTN"] = new Button({
        .Size = sf::Vector2f(Cvt.P2PX(8.f), Cvt.P2PY(5.f)),
        .Position = sf::Vector2f(Cvt.P2PX(78.f), Cvt.P2PY(78.f)),
        .Font = Ctx->SecondFont,
        .CharSize = Cvt.P2PChar(111),
        .Text = "Quit"
    }, &EventQueue);

    // Adjusting each button
    for (auto& Btn : Buttons)
    {
        Btn.second->SetOutline(Ctx->SecondColor, 1.5f);
        Btn.second->SetColors({
            .IdleColor = Ctx->MainColor,
            .HoverColor = sf::Color(166, 35, 73),
            .ActiveColor = sf::Color(99, 6, 6),
            .TextColor = sf::Color::White
        });
    }
}

MainMenuState::~MainMenuState()
{
    for (auto& Btn : Buttons)
        delete Btn.second;
}

///////////// Private Methods (Initalizer) /////////////////
void MainMenuState::InitializeBackground()
{
    // Background
    Background.loadFromFile("../Resources/screen.1mb.png");

    Shape.setTexture(Background);
    Shape.setScale(1.f, 1.f);
    Shape.setPosition(0, 0);

    // Music
    Music.openFromFile("../Resources/sounds/Little-Nightmares-2-Soundtrack-Six_s-Music-Box_2.ogg");
    Music.setLoop(true);
    Music.play();
}

///////////// Lifecycle /////////////////
void MainMenuState::OnInput(sf::Event* Event)
{

}

// \brief Called every frame, apply game logic here
void MainMenuState::OnUpdate(const float& DeltaTime)
{
    // Inheritance
    State::OnUpdate(DeltaTime);

    if (!MusicPlayed)
    {
        Music.play();
        MusicPlayed = true;
    }

    // Handling Buttons
    Buttons["GAMESTATE_BTN"]->OnClick([this]() {
        Ctx->States->push(new GameState(Ctx));

        Music.stop();
        MusicPlayed = false;
    });

    Buttons["QUIT_BTN"]->OnClick([this]() {
        Quit();
    });

    // Updating Buttons
    for (auto& Btn : Buttons)
        Btn.second->OnUpdate(MouseWindow);
}

// \brief Draw SF drawable components to screen
void MainMenuState::OnDraw(sf::RenderWindow* Window)
{
    Window->draw(Shape);

    for (auto& Btn : Buttons)
        Btn.second->OnDraw(Window);
}