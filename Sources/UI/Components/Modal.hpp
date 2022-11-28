#pragma once

class TextField;
class Dropdown;
struct BColorArgs;

enum MTypes
{
    TEXT,
    OPTION
};

struct MArgs
{
    sf::Vector2f Size;
    sf::Vector2f Position;
    sf::Font& Font;
    std::string HeaderText;
    std::string ContentText;
};

class Modal
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Modal(MArgs Args, std::vector<std::function<void(sf::Event*)>>* EventQueue, MTypes I_Type = TEXT);
    virtual ~Modal();

    /////////////////////////////
    // Accessors
    /////////////////////////////
    const std::string& GetInput() const;

    /////////////////////////////
    // Modifiers
    /////////////////////////////
    void AddDropdown(std::vector<std::string>* Lists, sf::Font& Font, unsh CharSize, BColorArgs Colors,  std::vector<std::function<void(sf::Event*)>>* EventQueue);
    void SetContainerOutline(sf::Color Color, float Thickness);
    void SetTextContent(std::string& I_Text);

    /////////////////////////////
    // Lifecycle
    /////////////////////////////
    void OnContinue(std::function<void()> Callback);
    void OnCancel(std::function<void()> Callback);
    void OnUpdate(const sf::Vector2s& MousePosition);
    void OnDraw(sf::RenderWindow* Window);

private:
    /////////////////////////////
    // SF Components
    /////////////////////////////
    sf::RectangleShape Container;
    sf::Text HeaderText;
    sf::Text Text;
    std::vector<std::string>* Data;

    /////////////////////////////
    // Variables
    /////////////////////////////
    bool Active;
    enum MTypes Type;

    /////////////////////////////
    // Custom Components
    /////////////////////////////
    std::map<std::string, Button*> Buttons;
    Dropdown* DropDown;
    TextField* Textfield;
};