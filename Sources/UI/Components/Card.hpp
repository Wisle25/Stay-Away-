#pragma once

enum CStates
{
    C_IDLE = 0,
    C_HOVER,
    C_PRESSED
};

struct CArgs
{
    sf::Vector2f Size;
    sf::Vector2f Position;
    sf::Font& Font;
    unsh CharSize;
    String Title;
};

struct CColorArgs
{
    sf::Color IdleColor;
    sf::Color HoverColor;
    sf::Color ActiveColor;
    sf::Color TextColor = sf::Color::White;
};

class Card
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Card(CArgs Args, String ImageFile, std::vector<std::function<void(sf::Event*)>>* EventQueue); /* For Tile */
    Card(CArgs Args, std::vector<sf::Vector2f> I_Vertices, std::vector<std::function<void(sf::Event*)>>* EventQueue); /* For Collision */
    virtual ~Card();

    /////////////////////////////
    // Accessors
    /////////////////////////////
    const sf::Vector2f& GetPosition() const;
    const sf::Vector2f& GetSize() const;
    const String GetName() const;
    const std::map<String, String> GetData() const;
    const std::vector<sf::Vector2f>& GetVertices() const;

    /////////////////////////////
    // Modifiers
    /////////////////////////////
    void SetPosition(const sf::Vector2f& Position);
    void SetColors(CColorArgs Color);
    void SetOutline(sf::Color Color, float Thickness = 1.f);

    /////////////////////////////
    // Lifecycle
    /////////////////////////////
    void OnInput(sf::Event* Event);
    void OnClick(std::function<void()> Callback);
    void OnUpdate(const sf::Vector2s& MousePosition);
    void OnDraw(sf::RenderTexture* Texture, sf::RenderWindow* Window);

private:
    /////////////////////////////
    // SF Components
    /////////////////////////////
    sf::Cursor HandCursor, ArrowCursor;
    sf::RectangleShape Container;
    sf::RectangleShape Image;
    sf::Texture ImageTexture;
    sf::Text Title;
    sf::Text Detail;
    sf::Color IdleColor, HoverColor, ActiveColor;
    String File;
    std::vector<sf::Vector2f> Vertices;

    /////////////////////////////
    // Variables
    /////////////////////////////
    enum CStates State;
    bool Active;
};