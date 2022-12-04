#include "stdpch.hpp"

#include "UI/Converter.hpp"
#include "UI/Components/Card.hpp"
#include "UI/Components/ScrollMode.hpp"
#include "UI/Components/Modal.hpp"
#include "UI/Micro/Button.hpp"
#include "Systems/Collision/Collider.hpp"

#include "CollisionAdder.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
CollisionAdder::CollisionAdder(Converter& I_Cvt, sf::Font& I_Font, std::vector<std::function<void(sf::Event*)>>* I_EventQueue):
    State(CA_IDLE),
    Cvt(I_Cvt),
    Font(I_Font),
    EventQueue(I_EventQueue)
{
    InitializeContainer();
    InitializeCollisions();
    InitializeComponents();

    // *** Adding Event Queue *** //
    EventQueue->push_back(std::bind(&OnInput, this, std::placeholders::_1));
}

CollisionAdder::~CollisionAdder()
{
    delete AddTemplateBtn;
    delete M_ScrollMode;
    delete ModalName;

    if (!Cards.empty())
    {
        for (auto& M_Card : Cards)
        {
            delete M_Card;
            M_Card = nullptr;
        }
        Cards.clear();
    }

    // ClearColliders();
}

///////////// Accessors /////////////

// \brief Get the State of the Collision Adder
const CAStates& CollisionAdder::GetState() const
{
    return State;
}

const sf::FloatRect CollisionAdder::GetBounds() const
{
    return Container.getGlobalBounds();
}

const std::vector<sf::Vector2f> CollisionAdder::FindVerticesByName(const std::string& Name)
{
    for (unsh i = 0; i < CollidersNames.size(); ++i)
    {
        if (CollidersNames[i] == Name)
            return Colliders[i]->GetVertices();
    }

    return std::vector<sf::Vector2f>();
}

///////////// Private Methods /////////////

void CollisionAdder::InitializeContainer()
{
    // *** Initializing Container *** //
    Container.setSize({ Cvt.P2PX(18.6f), Cvt.P2PY(45.f) });
    Container.setPosition(Cvt.P2PX(80.5f), Cvt.P2PY(0.5f));
    Container.setFillColor(sf::Color(25, 25, 25));
    Container.setOutlineThickness(1.f);
    Container.setOutlineColor(sf::Color(255, 255, 255, 200));

    // *** Initializing Text *** //
    Text.setFont(Font);
    Text.setCharacterSize(Cvt.P2PChar(140));
    Text.setString("Collision Center");
    Text.setOrigin(
        Text.getLocalBounds().left + Text.getLocalBounds().width / 2.f,
        Text.getLocalBounds().top + Text.getLocalBounds().height / 2.f
    );
    Text.setPosition({ Container.getPosition().x + Container.getSize().x / 2.f , Cvt.P2PY(2.f) });

    // *** Initializing Status Text *** //
    StatusText.setFont(Font);
    StatusText.setCharacterSize(Cvt.P2PChar(155));
    StatusText.setString("Status: " + State);
    StatusText.setOrigin(
        StatusText.getLocalBounds().left + StatusText.getLocalBounds().width / 2.f,
        StatusText.getLocalBounds().top + StatusText.getLocalBounds().height / 2.f
    );
    StatusText.setPosition({ Container.getPosition().x + Container.getSize().x / 2.f , Cvt.P2PY(4.f) });
}

void CollisionAdder::InitializeComponents()
{
    // Initialize Cards
    for (unsh i = 0; i < Colliders.size(); ++i)
    {
        Cards.push_back(
            new Card({
                .Size = { Cvt.P2PX(15.6f), Cvt.P2PY(4.8f) },
                .Position = {
                    Container.getPosition().x + Container.getGlobalBounds().width / 2.f,
                    Cvt.P2PY(8.5f) + (i * Cvt.P2PY(5.f)) // Keep adjusting position by the size of it's card
                },
                .Font = Font,
                .CharSize = 17,
                .Title = CollidersNames[i]
            }, Colliders[i]->GetVertices(), EventQueue)
        );

        Cards[i]->SetOutline(sf::Color(255, 165, 0));
        Cards[i]->SetColors({
            .IdleColor = sf::Color::Transparent,
            .HoverColor = sf::Color(255, 255, 255, 50),
            .ActiveColor = sf::Color(250, 250, 250, 100),
            .TextColor = sf::Color::White
        });
    }

    // ScrollMode
    M_ScrollMode = new ScrollMode(
        { Cvt.P2PX(16.2f), Cvt.P2PY(32.f) },
        { // Position
            Container.getPosition().x + Container.getGlobalBounds().width / 2.f,
            Cvt.P2PY(21.5f)
        },
        sf::Color(239, 91, 12),
        &Cards,
        Cvt.VirtualMachine,
        EventQueue
    );

    // Button
    AddTemplateBtn = new Button({
        .Size = { Cvt.P2PX(16.5f), Cvt.P2PY(4.f) },
        .Position = { Container.getPosition().x + Container.getSize().x / 2.f, Cvt.P2PY(42.f) },
        .Font = Font,
        .CharSize = Cvt.P2PChar(170),
        .Text = "Add More Template"
    }, EventQueue);
    AddTemplateBtn->SetOutline(sf::Color(28, 23, 46), 2.5f);
    AddTemplateBtn->SetColors({
        .IdleColor = sf::Color(124, 22, 46),
        .HoverColor = sf::Color(166, 35, 73),
        .ActiveColor = sf::Color(99, 6, 6),
        .TextColor = sf::Color::White
    });

    // Modal
    ModalName = new Modal({
        .Size = { Cvt.P2PX(42.f), Cvt.P2PY(30.f) },
        .Position = { Cvt.P2PX(50.f), Cvt.P2PY(50.f) },
        .Font = Font,
        .HeaderText = "Save Collision Template",
        .ContentText = "Give a name to your new Collision template"
    }, EventQueue);
    ModalName->SetContainerOutline(sf::Color(124, 22, 46), 2.f);
}

void CollisionAdder::InitializeCollisions()
{
    // Clear Those data first
    ClearColliders();

    // The actual Initialize Collisions from file
    std::ifstream InFile("../Data/Collision.gdat", std::ios::binary | std::ios::out);

    unsh NameSize;
    unsh InformationSize;
    char* NameBuffer;
    char* InformationBuffer;

    while (InFile.read((char*)&NameSize, sizeof(unsh)))
    {
        // Getting the name
        NameBuffer = new char[NameSize + 1];
        InFile.read(NameBuffer, NameSize);
        NameBuffer[NameSize] = '\0';
        std::string Name = NameBuffer;
        CollidersNames.push_back(Name);

        // Getting the Vertices
        InFile.read((char*)&InformationSize, sizeof(unsh));
        InformationBuffer = new char[InformationSize + 1];
        InFile.read(InformationBuffer, InformationSize);
        InformationBuffer[InformationSize] = '\0';
        std::string Information = InformationBuffer;

        sf::Vector2f TV; // TV = Temp Vertices
        std::stringstream VS(Information); // VS = Vertices Stream
        while (VS >> TV.x >> TV.y)
            Vertices.push_back(TV);

        Colliders.push_back(new Collider(Vertices));
        Vertices.clear();

        // Deallocate
        delete[] NameBuffer;
        delete[] InformationBuffer;
    }
}

void CollisionAdder::AddCard()
{
    // Initializing Cards
    unsh i = Colliders.size() - 1;

    Cards.push_back(
        new Card({
            .Size = { Cvt.P2PX(15.6f), Cvt.P2PY(4.8f) },
            .Position = {
                Container.getPosition().x + Container.getGlobalBounds().width / 2.f,
                Cvt.P2PY(8.5f) + (i * Cvt.P2PY(5.f)) // Keep adjusting position by the size of it's card
            },
            .Font = Font,
            .CharSize = 17,
            .Title = CollidersNames[i]
        }, Colliders[i]->GetVertices(), EventQueue)
    );

    Cards[i]->SetOutline(sf::Color(255, 165, 0));
    Cards[i]->SetColors({
        .IdleColor = sf::Color::Transparent,
        .HoverColor = sf::Color(255, 255, 255, 50),
        .ActiveColor = sf::Color(250, 250, 250, 100),
        .TextColor = sf::Color::White
    });
}

// Clear Colliders
void CollisionAdder::ClearColliders()
{
    if (!CollidersNames.empty())
    {
        CollidersNames.clear();

        for (auto& M_Collider : Colliders)
        {
            delete M_Collider;
            M_Collider = nullptr;
        }

        Colliders.clear();
    }
}

///////////// Lifecycle /////////////////

// \brief Handling Input
void CollisionAdder::OnInput(sf::Event* Event)
{
    switch (State)
    {
    case ADDING:
        // We will add vertex once the mouse left button is pressed
        if (Event->type == sf::Event::MouseButtonPressed && Event->mouseButton.button == sf::Mouse::Left)
            Vertices.push_back(MouseView);
        // We can undo the vertices by using CTRL + Z
        else if (Event->type == sf::Event::KeyPressed      &&
                 Event->key.control                        &&
                 Event->key.code == sf::Keyboard::Z
        )
            Vertices.pop_back();

        // We can finish the adding mode by pressing ENTER
        if (Event->type == sf::Event::KeyPressed &&
            Event->key.code == sf::Keyboard::Enter
        )
            State = FINISHED;
        break;

    case FINISHED:
        ModalName->OnContinue([this]() {
            // Add New Colliders
            CollidersNames.push_back(
                ModalName->GetInput()
            );
            Colliders.push_back(new Collider(Vertices));
            AddCard();

            // Save it to file
            std::ofstream OutFile("../Data/Collision.gdat", std::ios::binary | std::ios::out);

            for (unsh i = 0; i < Colliders.size(); ++i)
            {
                // Saving the name
                unsh NameSize = CollidersNames[i].size();
                OutFile.write((char*)&NameSize, sizeof(unsh));
                OutFile.write(CollidersNames[i].c_str(), NameSize);

                // Saving the Vertices
                unsh InformationSize = Colliders[i]->GetInformation().size();
                OutFile.write((char*)&InformationSize, sizeof(unsh));
                OutFile.write(Colliders[i]->GetInformation().c_str(), InformationSize);
            }
            OutFile.close();

            // Reset the State and Vertices back to 0
            Vertices.clear();

            State = CA_IDLE;
        });

        ModalName->OnCancel([this]() {
            State = CA_IDLE;
            Vertices.clear();
        });
        break;
    }
}

// \brief Called every frame, apply game logic here
void CollisionAdder::OnUpdate(const sf::Vector2s& MouseWindow, const sf::Vector2f& I_MouseView)
{
    // *** Updating Mouse View Position *** //
    MouseView = I_MouseView;

    // *** Handling Buttons *** //
    AddTemplateBtn->OnClick([this]() {
        State = ADDING;
    });

    // *** Updating Modal once the state is finished
    if (State == FINISHED)
    {
        ModalName->OnUpdate(MouseWindow);
        return;
    }

    // *** Updating Status Text *** //
    std::string str_state[3] = { "Normal", "Adding", "Finished" };
    StatusText.setString("Status: " + str_state[State]);
    StatusText.setOrigin(
        StatusText.getLocalBounds().left + StatusText.getLocalBounds().width / 2.f,
        StatusText.getLocalBounds().top + StatusText.getLocalBounds().height / 2.f
    );
    StatusText.setPosition({ Container.getPosition().x + Container.getSize().x / 2.f , StatusText.getPosition().y });

    // *** Updating Components *** //
    AddTemplateBtn->OnUpdate(MouseWindow);
    M_ScrollMode->OnUpdate(MouseWindow);
}

// \brief Draw SF drawable components to screen
void CollisionAdder::OnDraw(sf::RenderWindow* Window, sf::View* Camera)
{
    // Drawing Vertex as Preview
    Window->setView(*Camera);
    if (!Vertices.empty())
    {
        Preview = sf::VertexArray(sf::LineStrip, Vertices.size() + 1);
        for (short i = 0; i < Vertices.size(); ++i)
        {
            Preview[i].position = Vertices[i];
            Preview[i].color = sf::Color::Red;
        }

        Preview[Vertices.size()].position = Vertices[0];
        Preview[Vertices.size()].color = sf::Color::Red;

        Window->draw(Preview);
    }

    Window->setView(Window->getDefaultView());
    Window->draw(Container);
    Window->draw(Text);
    Window->draw(StatusText);

    if (State == FINISHED) ModalName->OnDraw(Window);

    M_ScrollMode->OnDraw(Window);
    AddTemplateBtn->OnDraw(Window);
}