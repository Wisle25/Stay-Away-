#include "stdpch.hpp"
#include "TextField.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
TextField::TextField(TFArgs Args, std::vector<std::function<void(sf::Event*)>>* EventQueue):
    Active(false),
    State(IDLE),
    DefaultText(Args.DefaultText)
{
    // Initialize Container
    Container.setSize(Args.Size);
    Container.setOrigin(
        Container.getLocalBounds().left + Container.getLocalBounds().width / 2.f,
        Container.getLocalBounds().top + Container.getLocalBounds().height / 2.f
    );
    Container.setPosition(Args.Position);
    Container.setFillColor(sf::Color::Transparent);
    Container.setOutlineColor(sf::Color(239, 91, 12));
    Container.setOutlineThickness(1.6f);

    InputText.setFont(Args.Font);
    InputText.setCharacterSize(Args.CharSize);
    InputText.setString(Args.DefaultText);
    InputText.setOrigin(
        0,
        InputText.getLocalBounds().top + InputText.getLocalBounds().height / 2.f
    );
    InputText.setPosition(Container.getGlobalBounds().left + 5.f, Container.getPosition().y);

    // Initializing Mouse CUrsor
    ArrowCursor.loadFromSystem(sf::Cursor::Arrow);
    TextCursor.loadFromSystem(sf::Cursor::Text);

    // Enqueue On Input methods to Event Queue
    EventQueue->push_back(std::bind(&OnChange, this, std::placeholders::_1));
}

TextField::~TextField()
{

}

///////////// Accessors /////////////

// \brief Get the input that's submited by user
const String TextField::GetInput()
{
    String InputTemp = Input;
    Reset();

    return InputTemp;
}

const sf::Vector2f& TextField::GetPosition() const
{
    return Container.getPosition();
}

const sf::FloatRect TextField::GetBounds() const
{
    return Container.getGlobalBounds();
}

const enum TFStates& TextField::GetState() const
{
    return State;
}

///////////// Modifiers /////////////

// \brief Change Text Field Input with this function
void TextField::SetInput(String Value)
{
    Input = Value;
    InputText.setString(Input);
}

void TextField::SetSize(const sf::Vector2f& Size)
{
    Container.setSize(Size);
}

void TextField::Reset()
{
    Input = "";
    InputText.setString(DefaultText);
}

///////////// Private Methods /////////////

///////////// Lifecycle /////////////////

// \brief Handling input
void TextField::OnChange(sf::Event* Event)
{
    if (Event->type == sf::Event::TextEntered && Active)
    {
        // If the input is not empty and to delete the input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !Input.empty())
            Input.erase(Input.begin() + Input.length() - 1, Input.end());
        else
            Input += Event->text.unicode;

        // Updating the client Text and it's position
        InputText.setString(Input);
    }
}

// \brief Called every frame, apply game logic here
void TextField::OnUpdate(const sf::Vector2s& MousePosition)
{
    // Active the Text field by clicking the Text field
    if (Container.getGlobalBounds().contains(sf::Vector2f(MousePosition)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        Active = true;
        State = ONCHANGE;
    }

    if (!Container.getGlobalBounds().contains(sf::Vector2f(MousePosition)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        Active = false;
        State = IDLE;
    }
}

// \brief Draw SF drawable components to screen
void TextField::OnDraw(sf::RenderWindow* Window)
{
    switch (State)
    {
    case IDLE:
        Container.setFillColor(sf::Color::Transparent);
        if (Active) { Window->setMouseCursor(ArrowCursor); Active = false; }
        break;

    case ONCHANGE:
        Container.setFillColor(sf::Color(243, 239, 224, 25));
        if (Active) Window->setMouseCursor(TextCursor);
        break;

    default:
        Container.setFillColor(sf::Color::Transparent);
        break;
    }

    Window->draw(Container);
    Window->draw(InputText);
}