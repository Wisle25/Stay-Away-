#include "stdpch.hpp"
#include "Button.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Button::Button(BArgs Args, std::vector<std::function<void(sf::Event*)>>* EventQueue):
    State(BTN_IDLE),
    Id(DEFAULT_ID),
    Active(false)
{
    // *** Initializing Main Components *** //
    Container.setSize(Args.Size);
    Container.setOrigin(
        Container.getLocalBounds().left + Container.getLocalBounds().width / 2.f,
        Container.getLocalBounds().top + Container.getLocalBounds().height / 2.f
    );
    Container.setPosition(Args.Position);
    Container.setOutlineColor(sf::Color(128, 128, 128));
    Container.setFillColor(sf::Color::Transparent); // Idle Color

    // *** Initializing Texts ***
    Text.setFont(Args.Font);
    Text.setCharacterSize(Args.CharSize);
    Text.setString(Args.Text);
    Text.setOrigin(
        Text.getLocalBounds().left + Text.getLocalBounds().width / 2.f,
        Text.getLocalBounds().top + Text.getLocalBounds().height / 2.f
    );
    Text.setPosition(
        static_cast<int>(Container.getPosition().x),
        static_cast<int>(Container.getPosition().y)
    );
    Text.setFillColor(sf::Color::White);

    // *** Initializing Cursor *** //
    ArrowCursor.loadFromSystem(sf::Cursor::Arrow);
    HandCursor.loadFromSystem(sf::Cursor::Hand);

    // *** Enqueue On Input method to Event Queue *** //
    EventQueue->push_back(std::bind(&OnInput, this, std::placeholders::_1));
}

Button::~Button()
{

}

///////////// Accessors /////////////

const sf::Text Button::GetText() const
{
    return Text;
}

const unsh& Button::GetId() const
{
    return Id;
}

const sf::Vector2f& Button::GetPosition() const
{
    return Container.getPosition();
}

const sf::FloatRect Button::GetGlobalBounds() const
{
    return Container.getGlobalBounds();
}

///////////// Modifiers Methods /////////////

void Button::SetText(const std::string String, unsh CharSize)
{
    Text.setString(String);
    Text.setCharacterSize(CharSize);
}

void Button::SetId(unsh I_Id)
{
    Id = I_Id;
}

void Button::SetColors(BColorArgs Color)
{
    // Container Fill Color
    IdleColor = Color.IdleColor;
    HoverColor = Color.HoverColor;
    ActiveColor = Color.ActiveColor;

    // Text Color, only changing if the color is different from the default one
    if (Text.getFillColor() != Color.TextColor)
        Text.setFillColor(Color.TextColor);
}

void Button::SetOutline(sf::Color Color, float Thickness)
{
    Container.setOutlineColor(Color);
    Container.setOutlineThickness(Thickness);
}

///////////// Lifecycle /////////////////

// \brief Handling input
void Button::OnInput(sf::Event* Event)
{
    if (Event->type == sf::Event::MouseButtonPressed &&
        Event->mouseButton.button == sf::Mouse::Left &&
        State == BTN_HOVER
    )
        State = BTN_PRESSED;
}

// \brief Handling what should button do once it's clicked
void Button::OnClick(std::function<void()> Callback)
{
    if (State == BTN_PRESSED)
        Callback();
}

// \brief Called every frame, apply game logic here
void Button::OnUpdate(const sf::Vector2s& MousePosition)
{
    State = BTN_IDLE;

    if (Container.getGlobalBounds().contains(sf::Vector2f(MousePosition)))
    {
        State = BTN_HOVER;
        Active = true;
    }
}

// \brief Draw SF drawable components to screen
void Button::OnDraw(sf::RenderWindow* Window)
{
    // Changing the color container and cursor shape based on the button state
    switch (State)
    {
    case BTN_IDLE:
        Container.setFillColor(IdleColor);
        if (Active) { Window->setMouseCursor(ArrowCursor); Active = false; }
        break;

    case BTN_HOVER:
        Container.setFillColor(HoverColor);
        if (Active) Window->setMouseCursor(HandCursor);
        break;

    default:
        Container.setFillColor(sf::Color::Transparent);
        break;
    }

    Window->draw(Container);
    Window->draw(Text);
}