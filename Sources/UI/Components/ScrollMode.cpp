#include "stdpch.hpp"
#include "Card.hpp"
#include "ScrollMode.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
ScrollMode::ScrollMode(sf::Vector2f Size,
        sf::Vector2f Position,
        sf::Color Color,
        std::vector<Card*>* I_Cards,
        sf::VideoMode& ScreenSize,
        std::vector<std::function<void(sf::Event*)>>* EventQueue
):
    Cards(I_Cards)
{
    // *** Initializing Container *** //
    Container.setSize(Size);
    Container.setOrigin(
        Container.getLocalBounds().left + Container.getLocalBounds().width / 2.f,
        Container.getLocalBounds().top + Size.y / 2.f
    );
    Container.setPosition(Position);
    Container.setOutlineThickness(3.f);
    Container.setOutlineColor(Color);

    // *** Initializing Render Texture and the Range *** //
    RenderTexture.create(ScreenSize.width, ScreenSize.height);
    Range.left = static_cast<int>(Container.getPosition().x - Container.getOrigin().x);
    Range.top = static_cast<int>(Container.getPosition().y - Container.getOrigin().y);
    Range.width = static_cast<int>(Size.x);
    Range.height = static_cast<int>(Size.y);

    // Set the Container texture to the render texture
    Container.setTexture(&RenderTexture.getTexture());
    Container.setTextureRect(Range);

    // *** Initializing limit *** //
    Top = Position.y;
        // Bottom value is the bottom position of Container (which is equal to top - 5 + it's height),
        // but since Container origin is added to the half of card size (look up at line 12),
        // we need to substract it by the Container origin (which is full card size) and the original position (look up at line 16)
    Bottom = Top + Size.y - 10.f;

    // *** Enqueue On Input method to Event Queue *** //
    EventQueue->push_back(std::bind(&Scroll, this, std::placeholders::_1));
}

// \brief Called once when at the first start
ScrollMode::ScrollMode(
    sf::Vector2f Size,
    sf::Color Color,
    std::vector<Card*>* I_Cards,
    sf::VideoMode& ScreenSize,
    std::vector<std::function<void(sf::Event*)>>* EventQueue
):
    Cards(I_Cards)
{
    // *** Initializing Container *** //
    Container.setSize(Size);
    Container.setOrigin(
        Container.getLocalBounds().left + Container.getLocalBounds().width / 2.f,
        Container.getLocalBounds().top + Cards->at(0)->GetSize().y / 2.f
    );
    Container.setPosition( // Set the position based on the card position
        Cards->at(0)->GetPosition().x,
        Cards->at(0)->GetPosition().y - 5.f
    );
    Container.setOutlineThickness(3.f);
    Container.setOutlineColor(Color);

    // *** Initializing Render Texture and the Range *** //
    RenderTexture.create(ScreenSize.width, ScreenSize.height);
    Range.left = static_cast<int>(Container.getPosition().x - Container.getOrigin().x);
    Range.top = static_cast<int>(Container.getPosition().y - Container.getOrigin().y);
    Range.width = static_cast<int>(Size.x);
    Range.height = static_cast<int>(Size.y);

    // Set the Container texture to the render texture
    Container.setTexture(&RenderTexture.getTexture());
    Container.setTextureRect(Range);

    // *** Initializing limit *** //
    Top = Cards->at(0)->GetPosition().y;
        // Bottom value is the bottom position of Container (which is equal to top - 5 + it's height),
        // but since Container origin is added to the half of card size (look up at line 12),
        // we need to substract it by the Container origin (which is full card size) and the original position (look up at line 16)
    Bottom = Top + Size.y - Cards->at(0)->GetSize().y - 10.f;

    // *** Enqueue On Input method to Event Queue *** //
    EventQueue->push_back(std::bind(&Scroll, this, std::placeholders::_1));
}

ScrollMode::~ScrollMode()
{
}

///////////// Accessors /////////////////

// \brief Returning Data that it got from the card
const std::map<std::string, std::string>& ScrollMode::GetData() const
{
    return Data;
}

///////////// Modifiers /////////////////

// \brief Set a new data of Cards
void ScrollMode::SetData(std::vector<Card*>* I_Cards)
{
    // Reset scroll and update a new data
    Cards = I_Cards;
}

///////////// Public Methods /////////////////

// \brief A Method to scroll
void ScrollMode::Scroll(sf::Event* Event)
{
    if (Event->type == sf::Event::MouseWheelScrolled && Active)
    {
        // Reset active status to false so it wont scroll anytime
        Active = false;

        // Checking the current position of top and bottom's card after scrolled
        float currentTop = Cards->at(0)->GetPosition().y + 15.f * -Event->mouseWheelScroll.delta;
        float currentBottom = Cards->at(Cards->size() - 1)->GetPosition().y + 15.f * -Event->mouseWheelScroll.delta;

        // It gonna scroll once the position after scrolled are not beyond the limit
        if (currentTop <= Top && Bottom <= currentBottom)
            for (auto& card : *Cards)
            {
                // Getting each card position then updating the position
                sf::Vector2f position = card->GetPosition();
                position.y += 15.f * -Event->mouseWheelScroll.delta;

                card->SetPosition(position);
            }
    }
}

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void ScrollMode::OnUpdate(const sf::Vector2s& MousePosition)
{
    Active = Container.getGlobalBounds().contains(sf::Vector2f(MousePosition));

    for (auto& Card : *Cards)
        Card->OnClick([&]() {
            Data = Card->GetData();
        });

    // *** Updating Cards *** //
    for (auto& Card : *Cards)
        Card->OnUpdate(MousePosition);
}

// \brief Draw SF drawable components to screen
void ScrollMode::OnDraw(sf::RenderWindow* Window)
{
    for (auto& Card : *Cards)
        Card->OnDraw(&RenderTexture, Window);

    RenderTexture.display();

    Window->draw(Container);

    RenderTexture.clear();
}