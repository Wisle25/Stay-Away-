#pragma once

struct BArgs;
struct BColorArgs;
class Button;

class Dropdown
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Dropdown(
        BArgs Args,
        BColorArgs CArgs,
        std::vector<String>& I_Lists,
        std::vector<std::function<void(sf::Event*)>>* EventQueue
    );
    virtual ~Dropdown();

    /////////////////////////////
    // Accessors
    /////////////////////////////
    const unsh& GetActiveId() const;
    const bool& GetShow() const;

    /////////////////////////////
    // Modifiers
    /////////////////////////////
    void SetActiveText(String Text = "");
    void SetColors(BColorArgs Colors);
    void SetOutline(sf::Color Color, float Thickness);

    /////////////////////////////
    // Lifecycle
    /////////////////////////////
    void OnUpdate(const sf::Vector2s& MousePosition);
    void OnDraw(sf::RenderWindow* Window);

private:
    /////////////////////////////
    // Components of Buttons
    /////////////////////////////
    Button* ActiveList;
    std::vector<Button*> Lists;

    bool Show;
};