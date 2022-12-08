#include "stdpch.hpp"
#include "Checklist.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Checklist::Checklist(sf::Vector2f Size, sf::Vector2f Position, std::vector<std::function<void(sf::Event*)>>* EventQueue):
    IsCheckList(false)
{
    // *** Initializing Box *** //
    Box.setSize(Size);
    Box.setFillColor(sf::Color::Transparent);
    Box.setOutlineColor(sf::Color::White);
    Box.setOutlineThickness(1.f);
    Box.setOrigin(
        Box.getGlobalBounds().left + Box.getGlobalBounds().width / 2.f,
        Box.getGlobalBounds().top + Box.getGlobalBounds().height / 2.f
    );
    Box.setPosition(Position);

    // *** Initializing Content *** //
    Content.setSize(Size * 0.95f);
    Content.setFillColor(sf::Color::Transparent);
    Content.setOutlineColor(sf::Color::White);
    Content.setOutlineThickness(1.f);
    Content.setOrigin(
        Content.getGlobalBounds().left + Content.getGlobalBounds().width / 2.f,
        Content.getGlobalBounds().top + Content.getGlobalBounds().height / 2.f
    );
    Content.setPosition(Position);

    // *** Initializing Mouse *** //
    ArrowCursor.loadFromSystem(sf::Cursor::Arrow);
    HandCursor.loadFromSystem(sf::Cursor::Hand);

    // Enqueue On Input methods to Event Queue
    EventQueue->push_back(std::bind(&OnInput, this, std::placeholders::_1));
}

Checklist::~Checklist()
{

}

///////////// Private Methods /////////////

///////////// Lifecycle /////////////////

// \brief Handling input
void Checklist::OnInput(sf::Event* Event)
{
    if (Event->type == sf::Event::MouseButtonPressed &&
        Event->mouseButton.button == sf::Mouse::Left &&
        IsActive
    )
        IsCheckList = !IsCheckList;
}

// \brief Called every frame, apply game logic here
void Checklist::OnUpdate(const sf::Vector2s& MousePosition, bool& Value)
{
    if (Box.getGlobalBounds().contains(sf::Vector2f(MousePosition)))
    {
        // Changing the value depends on it's checked or not
        Value = IsCheckList;

        IsActive = true;
    }
    else
        IsActive = false;
}

// \brief Draw SF drawable components to screen
void Checklist::OnDraw(sf::RenderWindow* Window)
{
    switch (IsActive)
    {
    case false:
        Window->setMouseCursor(ArrowCursor);
        break;

    case true:
        Window->setMouseCursor(HandCursor);
        break;
    }

    Window->draw(Box);
    Window->draw(Content);
}