#include "stdpch.hpp"
#include "App.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
App::App()
{
// *** Initializing windows from config file *** //
    // Getting the settings and set the default settings
    Settings.LoadFromFile("../Config/window.ini");

    Window = new sf::RenderWindow(
        Settings.Resolution,
        "G.E.N Engine",
        (Settings.Fullscreen) ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close,
        Settings.CtxSettings
    );
    Window->setFramerateLimit(Settings.FpsLimit);
    Window->setVerticalSyncEnabled(Settings.VSync);

    // *** Loading Icon *** //
    Icon.loadFromFile("../Resources/icon.png");

    Window->setIcon(Icon.getSize().x, Icon.getSize().y, Icon.getPixelsPtr());

    // *** Initializing Context *** //
    Ctx.Window = Window;
    Ctx.Settings = &Settings;
    Ctx.States = &States;
    Ctx.Event = &Event;
    Ctx.GridSize = 64.f;
    Ctx.MainFont.loadFromFile("../Resources/fonts/Dosis-Light.ttf");
    Ctx.SecondFont.loadFromFile("../Resources/fonts/Dosis-ExtraBold.ttf");
    Ctx.MainColor = sf::Color(124, 22, 46);
    Ctx.SecondColor = sf::Color(28, 23, 46);

    // *** Initializing states *** //
    States.push(new MainMenuState(&Ctx));
}

App::~App()
{
    // Deleting window
    delete this->Window;

    // Deleting each states
    while (!States.empty())
    {
        delete this->States.top();
        this->States.pop();
    }
}

///////////// Private Methods /////////////

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void App::OnUpdate()
{
    // Updating delta time each frame
    DeltaTime = DtClock.restart().asSeconds();

    // Polling Events
    while (Window->pollEvent(Event))
        States.top()->RunEvent();

    // Close the window once the state is empty
    if (!States.empty())
    {
        // Updating current State
        States.top()->OnUpdate(DeltaTime);
        if (States.top()->isQuit())
        {
            delete States.top();
            States.pop();
        }
    }
    else
        Window->close();

}

// \brief Draw SF drawable components to screen
void App::OnDraw()
{
    Window->clear();

    if (!States.empty())
        States.top()->OnDraw(Window);

    Window->display();
}

void App::Run()
{
    // App loop
    while (Window->isOpen())
    {
        OnUpdate();
        OnDraw();
    }
}