#pragma once

class Card;

class ScrollMode
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    ScrollMode(
        sf::Vector2f Size,
        sf::Vector2f Position,
        sf::Color Color,
        std::vector<Card*>* I_Cards,
        sf::VideoMode& ScreenSize,
        std::vector<std::function<void(sf::Event*)>>* EventQueue
    );
    ScrollMode(
        sf::Vector2f Size,
        sf::Color Color,
        std::vector<Card*>* I_Cards,
        sf::VideoMode& ScreenSize,
        std::vector<std::function<void(sf::Event*)>>* EventQueue
    );
    virtual ~ScrollMode();

    /////////////////////////////
    // Accessors
    /////////////////////////////
    const std::map<std::string, std::string>& GetData() const;

    /////////////////////////////
    // Modifiers
    /////////////////////////////
    void SetData(std::vector<Card*>* I_Cards);

    /////////////////////////////
    // Public Methods
    /////////////////////////////
    void Scroll(sf::Event* Event);

    /////////////////////////////
    // Lifecycle
    /////////////////////////////
    void OnUpdate(const sf::Vector2s& MousePosition);
    void OnDraw(sf::RenderWindow* Window);

private:
    //////////////////////////////
    // \brief SF Components
    //
    //  Detail: We're using Render Texture to set the Texture Rect which is similar to how scroll works.
    //  NOTE: Scroll Mode is only for cards
    /////////////////////////////
    sf::RectangleShape Container;
    sf::RenderTexture RenderTexture;
    sf::IntRect Range;

    /////////////////////////////
    // A Data that scroll needs, As mentioned before, the data of scroll mode is cards
    /////////////////////////////
    std::map<std::string, std::string> Data;
    std::vector<Card*>* Cards;

    /////////////////////////////
    // Variables to limit the range of the scrolling
    /////////////////////////////
    float Top;
    float Bottom;

    /////////////////////////////
    // Variables
    /////////////////////////////
    bool Active;
};