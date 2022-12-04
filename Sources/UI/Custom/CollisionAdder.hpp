#pragma once

class Button;
class Card;
class Collider;
class ScrollMode;
class Modal;
struct Converter;

enum CAStates
{
    CA_IDLE,
    ADDING,
    FINISHED
};

class CollisionAdder
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    CollisionAdder(Converter& I_Cvt, sf::Font& I_Font, std::vector<std::function<void(sf::Event*)>>* I_EventQueue);
    virtual ~CollisionAdder();

    /////////////////////////////
    // Accessors
    /////////////////////////////
    const CAStates& GetState() const;
    const sf::FloatRect GetBounds() const;
    const std::vector<sf::Vector2f> FindVerticesByName(const std::string& Name);

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnInput(sf::Event* Event);
    void OnUpdate(const sf::Vector2s& MouseWindow, const sf::Vector2f& I_MouseView);
    void OnDraw(sf::RenderWindow* Window, sf::View* Camera);

private:
    /////////////////////////////
    // SF Components
    /////////////////////////////
    sf::RectangleShape Container;
    sf::Text Text;
    sf::Text StatusText;
    sf::VertexArray Preview;
    std::vector<sf::Vector2f> Vertices;

    /////////////////////////////
    // Custom Components
    /////////////////////////////
    Button* AddTemplateBtn;
    ScrollMode* M_ScrollMode;
    Modal* ModalName;
    std::vector<std::string> CollidersNames;
    std::vector<Card*> Cards;
    std::vector<Collider*> Colliders;

    std::vector<std::function<void(sf::Event*)>>* EventQueue;
    Converter& Cvt;
    sf::Font& Font;

    /////////////////////////////
    // Variables
    /////////////////////////////
    sf::Vector2f MouseView;
    enum CAStates State;

    /////////////////////////////
    // Initializer Methods
    /////////////////////////////
    void InitializeContainer();
    void InitializeCollisions();
    void InitializeComponents();
    void AddCard();

    /////////////////////////////
    // Handler Methods
    /////////////////////////////
    void ClearColliders();
};