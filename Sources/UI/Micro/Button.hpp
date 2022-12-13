#pragma once

// Some states for the button
enum BtnStates
{
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_PRESSED
};

// Arguments for Button Constructor
struct BArgs
{
    sf::Vector2f Size;
    sf::Vector2f Position;
    sf::Font& Font;
    unsh CharSize;
    String Text;
};

// Arguments for Button color function
struct BColorArgs
{
    sf::Color IdleColor;
    sf::Color HoverColor;
    sf::Color ActiveColor;
    sf::Color TextColor = sf::Color::White;
};

class Button
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Button(BArgs Args, std::vector<std::function<void(sf::Event*)>>* EventQueue);
    virtual ~Button();

    /////////////////////////////
    // Accessors
    /////////////////////////////
    const sf::Text GetText() const;
    const unsh& GetId() const;
    const sf::Vector2f& GetPosition() const;
    const sf::FloatRect GetGlobalBounds() const;

    /////////////////////////////
    // Modifier
    /////////////////////////////
    void SetText(const String String, unsh CharSize = 10.f);
    void SetId(unsh I_Id);
    void SetColors(BColorArgs Color);
    void SetOutline(sf::Color Color, float Thickness = 1.f);

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnInput(sf::Event* Event);
    void OnClick(std::function<void()> Callback);
    void OnUpdate(const sf::Vector2s& MousePosition);
    void OnDraw(sf::RenderWindow* Window);

protected:
    /////////////////////////////
    // SF Components
    /////////////////////////////
    sf::Cursor HandCursor, ArrowCursor;
    sf::RectangleShape Container;
    sf::Text Text;
    sf::Color IdleColor, HoverColor, ActiveColor;

    /////////////////////////////
    // Variables
    /////////////////////////////
    enum BtnStates State;
    unsh Id;
    bool Active;
};