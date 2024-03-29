#include "stdpch.hpp"
#include "Card.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Card::Card(CArgs Args, String ImageFile, std::vector<std::function<void(sf::Event*)>>* EventQueue):
    State(C_IDLE),
    File(ImageFile),
    Active(false)
{
    // Initializing Container
    Container.setSize(Args.Size);
    Container.setOrigin(
        Container.getLocalBounds().left + Container.getLocalBounds().width / 2.f,
        Container.getLocalBounds().top + Container.getLocalBounds().height / 2.f
    );
    Container.setPosition(Args.Position);
    Container.setOutlineColor(sf::Color(128, 128, 128));
    Container.setFillColor(sf::Color::Transparent); // Idle Color

    // Initializing Images
    ImageTexture.loadFromFile(ImageFile);
    Image.setTexture(&ImageTexture);
    Image.setPosition( // Left of the container
        Args.Position.x - Container.getGlobalBounds().width / 2.f + 3.5f,
        Args.Position.y - Container.getGlobalBounds().height / 2.f + 4.5f
    );
    Image.setSize(
        sf::Vector2f(
            std::clamp(static_cast<float>(ImageTexture.getSize().x), 0.f, Args.Size.y * 0.84f),
            std::clamp(static_cast<float>(ImageTexture.getSize().y), 0.f, Args.Size.y * 0.84f)
        )
    );

    // Initializing Title
    Title.setFont(Args.Font);
    Title.setCharacterSize(Args.CharSize);
    Title.setString(Args.Title);
    Title.setPosition(
        static_cast<int>(Image.getPosition().x + Image.getGlobalBounds().width + 5.f),
        static_cast<int>(Image.getPosition().y)
    );

    // Initializing Card Detail, the content is just the size of the image texture
    std::stringstream ss;
    ss << "Size: " << ImageTexture.getSize().x << " x " << ImageTexture.getSize().y;
    Detail.setFont(Args.Font);
    Detail.setCharacterSize(Args.CharSize - 2U);
    Detail.setString(ss.str());
    Detail.setPosition(
        static_cast<int>(Image.getPosition().x + Image.getGlobalBounds().width + 5.f),
        static_cast<int>(Title.getPosition().y + 20.f)
    );

    // Initializing Cursor
    ArrowCursor.loadFromSystem(sf::Cursor::Arrow);
    HandCursor.loadFromSystem(sf::Cursor::Hand);

    // *** Enqueue On Input method to Event Queue *** //
    EventQueue->push_back(std::bind(&OnInput, this, std::placeholders::_1));
}

Card::Card(CArgs Args, std::vector<sf::Vector2f> I_Vertices, std::vector<std::function<void(sf::Event*)>>* EventQueue):
    State(C_IDLE),
    Active(false),
    Vertices(I_Vertices)
{
    // Initializing Container
    Container.setSize(Args.Size);
    Container.setOrigin(
        Container.getLocalBounds().left + Container.getLocalBounds().width / 2.f,
        Container.getLocalBounds().top + Container.getLocalBounds().height / 2.f
    );
    Container.setPosition(Args.Position);
    Container.setOutlineColor(sf::Color(128, 128, 128));
    Container.setFillColor(sf::Color::Transparent); // Idle Color

    // Initializing Title
    Title.setFont(Args.Font);
    Title.setCharacterSize(Args.CharSize);
    Title.setString(Args.Title);
    Title.setPosition(
        static_cast<int>(Args.Position.x - Container.getGlobalBounds().width / 2.f + 3.5f),
        static_cast<int>(Args.Position.y - Container.getGlobalBounds().height / 2.f + 4.5f)
    );

    // Initializing Card Detail, the content is the description of the image
    Detail.setFont(Args.Font);
    Detail.setCharacterSize(Args.CharSize - 2U);
    Detail.setString("A Collision for \"" + Args.Title + "\" Object");
    Detail.setPosition(
        static_cast<int>(Args.Position.x - Container.getGlobalBounds().width / 2.f + 3.5f),
        static_cast<int>(Title.getPosition().y + 20.f)
    );

    // Initializing Cursor
    ArrowCursor.loadFromSystem(sf::Cursor::Arrow);
    HandCursor.loadFromSystem(sf::Cursor::Hand);

    // *** Enqueue On Input method to Event Queue *** //
    EventQueue->push_back(std::bind(&OnInput, this, std::placeholders::_1));
}

Card::~Card()
{

}

const sf::Vector2f& Card::GetPosition() const
{
    return Container.getPosition();
}

const sf::Vector2f& Card::GetSize() const
{
    return Container.getSize();
}

const String Card::GetName() const
{
    return Title.getString();
}

///////////// Accessors /////////////

// \brief Getting Image detail such as size and texture file
const std::map<String, String> Card::GetData() const
{
    std::stringstream Size;
    Size << ImageTexture.getSize().x << " " << ImageTexture.getSize().y;

    // If the card does have image
    if (ImageTexture.getSize() != sf::Vector2u(0, 0))
        return std::map<String, String>{
            { "Name", Title.getString() },
            { "Texture", File },
            { "Size", Size.str() }
        };
    // Else if the card does have vertices data
    else
    {
        std::stringstream VerticesDataStream;

        for (auto& Vertex : Vertices)
            VerticesDataStream << Vertex.x << " " << Vertex.y << " ";

        return std::map<String, String>{
            { "Vertices", VerticesDataStream.str() }
        };
    }
}

const std::vector<sf::Vector2f>& Card::GetVertices() const
{
    return Vertices;
}

///////////// Modifiers /////////////

// \brief Set the position of each card
void Card::SetPosition(const sf::Vector2f& Position)
{
    Container.setPosition(Position);
    Image.setPosition( // Left of the Container
        Position.x - Container.getGlobalBounds().width / 2.f + 3.5f,
        Position.y - Container.getGlobalBounds().height / 2.f + 4.5f
    );
    Title.setPosition(
        static_cast<int>(Image.getPosition().x + Image.getGlobalBounds().width + 5.f),
        static_cast<int>(Image.getPosition().y)
    );
    Detail.setPosition(
        static_cast<int>(Image.getPosition().x + Image.getGlobalBounds().width + 5.f),
        static_cast<int>(Title.getPosition().y + 20.f)
    );
}

void Card::SetColors(CColorArgs Color)
{
    // Container Fill Color
    IdleColor = Color.IdleColor;
    HoverColor = Color.HoverColor;
    ActiveColor = Color.ActiveColor;

    // Text Color, only changing if the color is different from the default one
    if (Title.getFillColor() != Color.TextColor)
        Title.setFillColor(Color.TextColor);
}

void Card::SetOutline(sf::Color Color, float Thickness)
{
    Container.setOutlineColor(Color);
    Container.setOutlineThickness(Thickness);
}

///////////// Lifecycle /////////////

void Card::OnInput(sf::Event* Event)
{
    if (Event->type == sf::Event::MouseButtonPressed &&
        Event->mouseButton.button == sf::Mouse::Left &&
        State == C_HOVER
    )
    {
        State = C_PRESSED;
        Container.setFillColor(ActiveColor);
    }
}

void Card::OnClick(std::function<void()> Callback)
{
    if (State == C_PRESSED)
        Callback();
}

void Card::OnUpdate(const sf::Vector2s& MousePosition)
{
    State = C_IDLE;

    if (Container.getGlobalBounds().contains(sf::Vector2f(MousePosition)))
    {
        State = C_HOVER;
        Active = true;
    }
}

// \brief Draw SF drawable components to screen
void Card::OnDraw(sf::RenderTexture* Texture, sf::RenderWindow* Window)
{
    switch (State)
    {
    case C_IDLE:
        Container.setFillColor(IdleColor);
        if (Active) { Window->setMouseCursor(ArrowCursor); Active = false; }
        break;

    case C_HOVER:
        Container.setFillColor(HoverColor);
        if (Active) Window->setMouseCursor(HandCursor);
        break;

    default:
        Container.setFillColor(sf::Color::Transparent);
        break;
    }

    Texture->draw(Container);

    Texture->draw(Image);
    Texture->draw(Title);
    Texture->draw(Detail);
}