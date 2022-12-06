#include "stdpch.hpp"
#include "State.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
State::State(Context* I_Ctx):
    Ctx(I_Ctx),
    Paused(false),
    Is_Quit(false),
    Camera(nullptr),
    Cvt(I_Ctx->Settings->Resolution)
{
    // Set the Mouse cursor to default
    sf::Cursor Cursor;
    Cursor.loadFromSystem(sf::Cursor::Arrow);
    Ctx->Window->setMouseCursor(Cursor);

    // Queued OnInput method to Event Queue
    EventQueue.push_back(std::bind(&State::OnInput, this, std::placeholders::_1));
}

State::~State()
{

}

///////////// Accessors /////////////
const bool& State::isQuit() const
{
    return Is_Quit;
}

const bool& State::isPaused() const
{
    return Paused;
}

///////////// Public Methods /////////////

// \brief Execute each event that's been queued
void State::RunEvent()
{
    if (Ctx->Event->type == sf::Event::Closed)
        Ctx->Window->close();

    for (auto& Event : EventQueue)
        Event(Ctx->Event);
}

void State::Quit()
{
    Is_Quit = true;
}

///////////// Private Methods /////////////

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void State::OnUpdate(const float& DeltaTime)
{
    // Updating Mouse Position
    /* Mouse refering to window size */
    MouseWindow = sf::Vector2s(sf::Mouse::getPosition(*Ctx->Window));
    /* Mouse refering to camera */
    if (Camera != nullptr)
    {
        Ctx->Window->setView(*Camera);
        MouseView = Ctx->Window->mapPixelToCoords(sf::Mouse::getPosition(*Ctx->Window));
        Ctx->Window->setView(Ctx->Window->getDefaultView());
    }
}