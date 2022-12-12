#include "stdpch.hpp"
#include "Bar.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Bar::Bar(BaArgs Args)
{
    // Initializing Container
    Container.setSize(Args.Size);
    Container.setPosition(Args.Position);
    Container.setFillColor(sf::Color::Transparent);

    Content.setSize(sf::Vector2f(Container.getSize()));
    Content.setPosition(Container.getPosition());

    // Initializing Text
    Text = new sf::Text();
    Text->setFont(Args.Font);
    Text->setCharacterSize(Args.CharSize);
    Text->setString("INITALIZE");
    Text->setOrigin(
        Text->getLocalBounds().left + Text->getLocalBounds().width / 2.f,
        Text->getLocalBounds().top + Text->getLocalBounds().height / 2.f
    );
    Text->setPosition( // Center of hp Container
        static_cast<int>(Container.getPosition().x + Container.getGlobalBounds().width / 2.f),
        static_cast<int>(Container.getPosition().y + (Container.getGlobalBounds().height - Container.getOutlineThickness() * 2) / 2.f)
    );
    Text->setFillColor(Args.TextColor);
}

Bar::Bar(const sf::Vector2f& Size, const sf::Vector2f& Position):
    Text(nullptr)
{
    // Initializing Container
    Container.setSize(Size);
    Container.setPosition(Position);
    Container.setFillColor(sf::Color::Transparent);

    Content.setSize(Size);
    Content.setPosition(Container.getPosition());
}

Bar::~Bar()
{
    delete Text;
}

///////////// Modifiers /////////////

void Bar::SetContainerOutline(sf::Color Color, short Thickness)
{
    Container.setOutlineColor(Color);
    Container.setOutlineThickness(Thickness);
}

void Bar::SetContentColor(sf::Color Color)
{
    Content.setFillColor(Color);
}

void Bar::SetPosition(const sf::Vector2f& Position)
{
    Container.setPosition(Position);
    Content.setPosition(Position);
}

/////////////// Lifecycle ///////////////

// \brief Called every frame, apply game logic here
void Bar::OnUpdate(float Current, float Max, const String& bar_title)
{
    // ******** Getting the Percentage for the size of the Content ******** //
    float Percentage = Current / Max;
    Content.setSize(sf::Vector2f(Container.getSize().x * Percentage, Container.getSize().y));

    // ******** Set the text bar of current and max by string stream ******** //
    std::stringstream ss;
    ss << bar_title << ": " << Current << " / " << Max;

    Text->setString(ss.str());
    Text->setOrigin(
        Text->getLocalBounds().left + Text->getLocalBounds().width / 2.f,
        Text->getLocalBounds().top + Text->getLocalBounds().height / 2.f
    );
    Text->setPosition( // Center of hp Container
        static_cast<int>(Container.getPosition().x + Container.getGlobalBounds().width / 2.f),
        static_cast<int>(Container.getPosition().y + (Container.getGlobalBounds().height - Container.getOutlineThickness() * 2) / 2.f)
    );
}

void Bar::OnUpdate(float Current, float Max)
{
    // ******** Getting the Percentage for the size of the Content ******** //
    float Percentage = Current / Max;
    Content.setSize(sf::Vector2f(Container.getSize().x * Percentage, Container.getSize().y));
}

// \brief Draw SF drawable components to screen
void Bar::OnDraw(sf::RenderWindow* Window)
{
    Window->draw(Container);
    Window->draw(Content);

    if (Text)
        Window->draw(*Text);
}