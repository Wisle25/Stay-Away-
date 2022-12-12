#include "stdpch.hpp"

#include "EditorState.hpp"
#include "GameState.hpp"
#include "SettingsState.hpp"
#include "MainMenuState.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
MainMenuState::MainMenuState(Context* I_Ctx):
    State(I_Ctx)
{
    // *** Initializing UI Components *** //
    // New Game button
    Buttons["GAMESTATE_BTN"] = new Button({
        .Size = sf::Vector2f(Cvt.P2PX(8.f), Cvt.P2PY(5.f)),
        .Position = sf::Vector2f(Cvt.P2PX(50.f), Cvt.P2PY(30.f)),
        .Font = Ctx->SecondFont,
        .CharSize = Cvt.P2PChar(111),
        .Text = "Start Game"
    }, &EventQueue);

    Buttons["EDITORSTATE_BTN"] = new Button({
        .Size = sf::Vector2f(Cvt.P2PX(8.f), Cvt.P2PY(5.f)),
        .Position = sf::Vector2f(Cvt.P2PX(50.f), Cvt.P2PY(44.f)),
        .Font = Ctx->SecondFont,
        .CharSize = Cvt.P2PChar(111),
        .Text = "Game Editor"
    }, &EventQueue);

    Buttons["SETTINGSTATE_BTN"] = new Button({
        .Size = sf::Vector2f(Cvt.P2PX(8.f), Cvt.P2PY(5.f)),
        .Position = sf::Vector2f(Cvt.P2PX(50.f), Cvt.P2PY(58.f)),
        .Font = Ctx->SecondFont,
        .CharSize = Cvt.P2PChar(111),
        .Text = "Settings"
    }, &EventQueue);

    Buttons["QUIT_BTN"] = new Button({
        .Size = sf::Vector2f(Cvt.P2PX(8.f), Cvt.P2PY(5.f)),
        .Position = sf::Vector2f(Cvt.P2PX(50.f), Cvt.P2PY(72.f)),
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

///////////// Lifecycle /////////////////
void MainMenuState::OnInput(sf::Event* Event)
{

}

// \brief Called every frame, apply game logic here
void MainMenuState::OnUpdate(const float& DeltaTime)
{
    // Inheritance
    State::OnUpdate(DeltaTime);

    // Handling Buttons
    Buttons["GAMESTATE_BTN"]->OnClick([this]() {
        Ctx->States->push(new GameState(Ctx));
    });

    Buttons["EDITORSTATE_BTN"]->OnClick([this]() {
        Ctx->States->push(new EditorState(Ctx));
    });

    Buttons["SETTINGSTATE_BTN"]->OnClick([this]() {
        Ctx->States->push(new SettingsState(Ctx));
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
    // ...(Code Your Program Here!)
    for (auto& Btn : Buttons)
        Btn.second->OnDraw(Window);
}