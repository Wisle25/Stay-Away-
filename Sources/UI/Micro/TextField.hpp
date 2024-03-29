#pragma once

enum TFStates
{
    IDLE = 0,
    ONCHANGE
};

struct TFArgs
{
    sf::Vector2f Size;
    sf::Vector2f Position;
    sf::Font& Font;
    unsh CharSize;
    String DefaultText;
};

class TextField
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    TextField(TFArgs Args, std::vector<std::function<void(sf::Event*)>>* EventQueue);
    virtual ~TextField();

    /////////////////////////////
    // Accessors
    /////////////////////////////
    const String GetInput();
    const sf::Vector2f& GetPosition() const;
    const sf::FloatRect GetBounds() const;
    const enum TFStates& GetState() const;

    /////////////////////////////
    // Modifiers
    /////////////////////////////
    void SetInput(String Value);
    void SetSize(const sf::Vector2f& Size);
    void Reset();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnChange(sf::Event* Event);
    void OnUpdate(const sf::Vector2s& MousePosition);
    void OnDraw(sf::RenderWindow* Window);

private:
    /////////////////////////////
    // SF Components
    /////////////////////////////
    sf::RectangleShape Container;
    sf::Text InputText;
    sf::Cursor ArrowCursor;
    sf::Cursor TextCursor;

    String Input;
    String DefaultText;

    /////////////////////////////
    // Variables
    /////////////////////////////
    bool Active;
    enum TFStates State;
};