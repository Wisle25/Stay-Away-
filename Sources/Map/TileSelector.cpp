#include "stdpch.hpp"

#include "UI/Micro/Button.hpp"
#include "UI/Components/Card.hpp"
#include "UI/Converter.hpp"
#include "UI/Components/ScrollMode.hpp"
#include "UI/Micro/TextField.hpp"

#include "TileSelector.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
TileSelector::TileSelector(Converter& Cvt, float I_GridSize, sf::Font& Font, std::vector<std::function<void(sf::Event*)>>* EventQueue):
    Active(false),
    GridSize(I_GridSize),
    Page(0)
{
    InitializeCategory();
    InitializeBase(Cvt, Font);
    InitializeComponents(Cvt, Font, EventQueue);
}

TileSelector::~TileSelector()
{
    delete this->Scrollmode;

    for (auto& Btn : this->Buttons)
        delete Btn.second;

    for (unsh i = 0; i < Cards.size(); i++)
    {
        for (unsh j = 0; j < Cards[i].size(); j++)
        {
            delete this->Cards[i][j];
            this->Cards[i][j] = NULL;
        }
        this->Cards[i].clear();
    }
    this->Cards.clear();
}

///////////// Accessors /////////////

// \brief Check is the selector active, It's based on the mouse position.
// If container contains mouse position, then it's active
const bool& TileSelector::IsActive() const
{
    return Active;
}

const std::map<std::string, std::string>& TileSelector::GetData() const
{
    return Scrollmode->GetData();
}

///////////// Private Methods /////////////

// \brief A methods to getting all tiles grouped by folders
void TileSelector::InitializeCategory()
{
    short TitleIdx = -1;

    for (auto& folder : fs::directory_iterator("../Resources/Tiles"))
    {
        std::string title = folder.path().filename().string();
        Category.push_back({ title, std::map<std::string, std::string>() });
        ++TitleIdx;

        for (auto& file : fs::directory_iterator("../Resources/Tiles/" + title))
        {
            std::string Filename = file.path().filename().string();
            std::string Filepath = file.path().filename().string();

            // Removing the .png extensions
            Filename.erase(Filename.begin() + Filename.length() - 4, Filename.end());

            // Append to the Category
            Category[TitleIdx].second.emplace(Filename, Filepath);
        }
    }
}

// \brief Initializing Container and Texts
void TileSelector::InitializeBase(Converter& Cvt, sf::Font& Font)
{
    // Initializing bounds
    Container.setSize(sf::Vector2f(Cvt.P2PX(18.6f), Cvt.P2PY(45.f)));
    Container.setPosition(Cvt.P2PX(0.5f), Cvt.P2PY(0.5f));
    Container.setFillColor(sf::Color(25, 25, 25));
    Container.setOutlineThickness(1.f);
    Container.setOutlineColor(sf::Color(255, 255, 255, 200));

    // Initializing Texts
    Texts["TITLE"] = sf::Text(Category[Page].first, Font, Cvt.P2PChar(140));

    /** Initializing Page Texts **/
    std::stringstream ps; // Page stream
    ps << Page + 1 << " / " << Category.size();
    Texts["PAGE"] = sf::Text(ps.str(), Font, Cvt.P2PChar(177));

    for (auto& Text : Texts)
        Text.second.setOrigin(
            Text.second.getLocalBounds().left + Text.second.getLocalBounds().width / 2.f,
            Text.second.getLocalBounds().top + Text.second.getLocalBounds().height / 2.f
        );

    /** Texts positioning **/
    Texts["TITLE"].setPosition( // Center of Container
        std::floor(Container.getPosition().x + Container.getGlobalBounds().width / 2.f),
        std::floor(Cvt.P2PY(6.8f))
    );
    Texts["PAGE"].setPosition( // Center of Container
        std::floor(Container.getPosition().x + Container.getGlobalBounds().width / 2.f),
        std::floor(Cvt.P2PY(3.2f))
    );
}

// \brief Initializing Components such as Buttons, Cards, and Scroll Mode
void TileSelector::InitializeComponents(Converter& Cvt, sf::Font& Font, std::vector<std::function<void(sf::Event*)>>* EventQueue)
{
// ******** Initializing Buttons ******** //
    Buttons["PREVIOUS_BTN"] = new Button({
        .Size = sf::Vector2f(Cvt.P2PX(4.1f), Cvt.P2PY(2.2f)),
        .Position = sf::Vector2f(Cvt.P2PX(6.3f), Cvt.P2PY(3.f)),
        .Font = Font,
        .CharSize = Cvt.P2PChar(187),
        .Text = "Previous"
    }, EventQueue);

    Buttons["NEXT_BTN"] = new Button({
        .Size = sf::Vector2f(Cvt.P2PX(4.1f), Cvt.P2PY(2.2f)),
        .Position = sf::Vector2f(Cvt.P2PX(13.3f), Cvt.P2PY(3.f)),
        .Font = Font,
        .CharSize = Cvt.P2PChar(187),
        .Text = "Next"
    }, EventQueue);

    for (auto& Btn : Buttons)
    {
        Btn.second->SetOutline(sf::Color(255, 165, 0));
        Btn.second->SetColors({
            .IdleColor = sf::Color::Transparent,
            .HoverColor = sf::Color(255, 255, 255, 50),
            .ActiveColor = sf::Color(250, 250, 250, 100),
            .TextColor = sf::Color::White
        });
    }

    // ******** Initializing Cards and Scrolling Mode ******** //
    /* Cards */
    unsh i = 0;
    unsh j = 0; // This iterator is for positioning purpose
    for (auto& Ctg : Category)
    {
        Cards.resize(Category.size(), std::vector<Card*>());

        for (auto& Object : Ctg.second)
        {
            Cards[i].push_back(
                new Card({
                    .Size = sf::Vector2f(Cvt.P2PX(15.6f), Cvt.P2PY(4.8f)),
                    .Position = sf::Vector2f( // Position
                        Container.getPosition().x + Container.getGlobalBounds().width / 2.f,
                        Cvt.P2PY(12.1f) + (j * Cvt.P2PY(5.f)) // Keep adjusting position by the size of it's card
                    ),
                    .Font = Font,
                    .CharSize = 17,
                    .Title = Object.first
                },
                "../Resources/Tiles/" + Ctg.first + "/" + Object.second, // Tile path
                EventQueue
                )
            );

            j++;
        }

        i++;
        j = 0; // Reset for the next Ctg
    }
    for (unsh i = 0; i < Cards.size(); i++)
    {
        for (unsh j = 0; j < Cards[i].size(); j++)
        {
            Cards[i][j]->SetOutline(sf::Color(255, 165, 0));
            Cards[i][j]->SetColors({
                .IdleColor = sf::Color::Transparent,
                .HoverColor = sf::Color(255, 255, 255, 50),
                .ActiveColor = sf::Color(250, 250, 250, 100),
                .TextColor = sf::Color::White
            });
        }
    }

    /* Scroll Mode */
    Scrollmode = new ScrollMode(
        sf::Vector2f(Cvt.P2PX(16.2f), Cvt.P2PY(35.f)),
        sf::Color(239, 91, 12),
        &Cards[Page],
        Cvt.VirtualMachine,
        EventQueue
    );
}

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void TileSelector::OnUpdate(const sf::Vector2s& MousePosition)
{
    // *** Updating components are only happens once the mouse entered the container *** //
    if (Container.getGlobalBounds().contains(sf::Vector2f(MousePosition)))
    {
        Active = true;

        // *** Handling button functionality *** //
        Buttons["NEXT_BTN"]->OnClick([this]() {
            // Check if the page won't beyond the title size
            if (Page < Category.size() - 1) Page++;

            Texts["TITLE"].setString(Category[Page].first);
            Texts["TITLE"].setOrigin(
                static_cast<int>(Texts["TITLE"].getLocalBounds().left + Texts["TITLE"].getLocalBounds().width / 2.f),
                static_cast<int>(Texts["TITLE"].getLocalBounds().top + Texts["TITLE"].getLocalBounds().height / 2.f)
            );

            std::stringstream ps; // Page stream
            ps << Page + 1 << " / " << Category.size();

            Texts["PAGE"].setString(ps.str());
            Scrollmode->SetData(&Cards[Page]);
        });

        Buttons["PREVIOUS_BTN"]->OnClick([this]() {
            // Check if the Page won't behind 0
            if (Page > 0) Page--;

            Texts["TITLE"].setString(Category[Page].first);
            Texts["TITLE"].setOrigin(
                static_cast<int>(Texts["TITLE"].getLocalBounds().left + Texts["TITLE"].getLocalBounds().width / 2.f),
                static_cast<int>(Texts["TITLE"].getLocalBounds().top + Texts["TITLE"].getLocalBounds().height / 2.f)
            );

            std::stringstream ps; // Page stream
            ps << Page + 1 << " / " << Category.size();

            Texts["PAGE"].setString(ps.str());
            Scrollmode->SetData(&Cards[Page]);
        });

        // ******** Updating each Buttons ******** //
        for (auto& Btn : Buttons)
            Btn.second->OnUpdate(MousePosition);

        Scrollmode->OnUpdate(MousePosition);

    }
    else
        Active = false;
}

// \brief Draw SF drawable components to screen
void TileSelector::OnDraw(sf::RenderWindow* Window)
{
    Window->draw(Container);

    for (auto& Btn : Buttons)
        Btn.second->OnDraw(Window);

    for (auto& Text : Texts)
        Window->draw(Text.second);

    Scrollmode->OnDraw(Window);
}