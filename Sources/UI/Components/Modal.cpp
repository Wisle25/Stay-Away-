#include "stdpch.hpp"

#include "UI/Micro/Button.hpp"
#include "UI/Micro/TextField.hpp"
#include "Dropdown.hpp"

#include "Modal.hpp"

/////////////// Constructor & Destructor ///////////////

// \brief Called once when at the first start
Modal::Modal(MArgs Args, std::vector<std::function<void(sf::Event*)>>* EventQueue, MTypes I_Type):
    Active(false),
    M_DropDown(nullptr),
    Type(I_Type)
{
    // *** Initializing Container *** //
    Container.setSize(Args.Size);
    Container.setOrigin(
        Container.getLocalBounds().left + Container.getLocalBounds().width / 2.f,
        Container.getLocalBounds().top + Container.getLocalBounds().height / 2.f
    );
    Container.setFillColor(sf::Color::Black);
    Container.setPosition(Args.Position);
    // *** END *** //

    // *** Initializing header Text and Text *** //
    HeaderText.setFont(Args.Font);
    HeaderText.setCharacterSize(40);
    HeaderText.setString(Args.HeaderText);
    HeaderText.setOrigin(
        HeaderText.getLocalBounds().left + HeaderText.getLocalBounds().width / 2.f,
        HeaderText.getLocalBounds().top + HeaderText.getLocalBounds().height / 2.f
    );
    HeaderText.setPosition(Args.Position.x, Container.getGlobalBounds().top + 58.f);

    Text.setFont(Args.Font);
    Text.setCharacterSize(24);
    Text.setString(Args.ContentText);
    Text.setOrigin(
        Text.getLocalBounds().left + Text.getLocalBounds().width / 2.f,
        Text.getLocalBounds().top + Text.getLocalBounds().height / 2.f
    );
    Text.setPosition(Args.Position.x, HeaderText.getPosition().y + 50.f);
    // *** END *** //

    // *** Initializing Text Fields Or DropDown*** //
    if (Type == TEXT)
    {
        M_Textfield = new TextField({
            .Size = sf::Vector2f(Args.Size.x * 0.85f, 32.f),
            .Position = Args.Position,
            .Font = Args.Font,
            .CharSize = 20,
            .DefaultText = "Answer here"
        }, EventQueue);
    }
    // *** END *** //

    // *** Initializing Buttons *** //
    /** Continue Button **/
    Buttons["CONTINUE_BTN"] = new Button({
        .Size = sf::Vector2f(150.f, 50.f),
        .Position = sf::Vector2f(
            Container.getGlobalBounds().left + 120.f,
            (Container.getPosition().y + Container.getGlobalBounds().height / 2.f) - 55.f
        ),
        .Font = Args.Font,
        .CharSize = 30,
        .Text = "Continue"
    }, EventQueue);
    Buttons["CONTINUE_BTN"]->SetOutline(sf::Color(73, 255, 0), 1.f);
    Buttons["CONTINUE_BTN"]->SetColors({
        .IdleColor = sf::Color(26, 77, 46),
        .HoverColor = sf::Color(125, 206, 19, 50),
        .ActiveColor = sf::Color::Transparent
    });
    /** END **/

    /** Cancel Button **/
    Buttons["CANCEL_BTN"] = new Button({
        .Size = sf::Vector2f(150.f, 50.f),
        .Position = sf::Vector2f(
            (Container.getPosition().x + Container.getGlobalBounds().width / 2.f) - 120.f,
            (Container.getPosition().y + Container.getGlobalBounds().height / 2.f) - 55.f
        ),
        .Font = Args.Font,
        .CharSize = 30,
        .Text = "Cancel"
    }, EventQueue);
    Buttons["CANCEL_BTN"]->SetOutline(sf::Color(255, 30, 0), 1.f);
    Buttons["CANCEL_BTN"]->SetColors({
        .IdleColor = sf::Color::Transparent,
        .HoverColor = sf::Color(236, 114, 114, 50),
        .ActiveColor = sf::Color(194, 16, 16)
    });
    /** END **/
    // *** END *** //
}

Modal::~Modal()
{
    if (M_DropDown)
        delete this->M_DropDown;

    delete this->M_Textfield;

    for (auto& Btn : Buttons)
        delete Btn.second;
}

/////////////// Accessors ///////////////

// \brief Getting the input that's been submited
const std::string Modal::GetInput() const
{
    return M_Textfield->GetInput();
}

/////////////// Modifier ///////////////

// \brief A function to add M_dropdown to the Modal, It is added near the text field
void Modal::AddDropdown(std::vector<std::string>* Lists, sf::Font& Font, unsh CharSize, BColorArgs Colors, std::vector<std::function<void(sf::Event*)>>* EventQueue)
{
    // *** Resize M_Textfield and inputField to make M_dropdown fit to Container *** //
    Data = Lists;
    M_Textfield->SetSize(sf::Vector2f(Container.getSize().x * 0.6f, 32.f));
    // *** END *** //

    // *** Initializing M_Dropdown components *** //
    M_DropDown = new Dropdown({
        .Size = sf::Vector2f(Container.getGlobalBounds().width * 0.24f, 32.f),
        .Position = sf::Vector2f(M_Textfield->GetPosition().x + (M_Textfield->GetBounds().width / 2.f) + 5.f, M_Textfield->GetPosition().y),
        .Font = Font,
        .CharSize = CharSize
    }, Colors, *Data, EventQueue);
    M_DropDown->SetActiveText("Choose Map");
    M_DropDown->SetOutline(sf::Color(239, 91, 12), 1.6f);
    // *** END *** //
}

void Modal::SetContainerOutline(sf::Color color, float thickness)
{
    Container.setOutlineColor(color);
    Container.setOutlineThickness(thickness);
}

// \brief Modify modal's text content
void Modal::SetTextContent(std::string& i_Text)
{
    Text.setString(i_Text);
}

/////////////// Lifecycle ///////////////

// \brief Handling what should Modal do when user choosed continue
void Modal::OnContinue(std::function<void()> cb)
{
    Buttons["CONTINUE_BTN"]->OnClick(cb);
}

// \brief Handling what should Modal do when user choosed cancel
void Modal::OnCancel(std::function<void()> cb)
{
    Buttons["CANCEL_BTN"]->OnClick(cb);
}

// \brief Called every frame, apply game logic here
void Modal::OnUpdate(const sf::Vector2s& MousePosition)
{
    // If the modal has M_dropdown
    if (M_DropDown && !Active)
        if (M_DropDown->GetActiveId() != 100 )
            M_Textfield->SetInput(*Data[M_DropDown->GetActiveId()].data());

    // *** Handling Buttons OnClick Events *** //
    Buttons["CANCEL_BTN"]->OnClick([this]() {
        if (M_DropDown && !M_DropDown->GetShow())
            M_Textfield->Reset();
    });
    // *** END *** //

    // *** Updating components *** //
    /** Buttons **/
    for (auto& Btn : Buttons)
        Btn.second->OnUpdate(MousePosition);

    /** M_Dropdown **/
    if (M_DropDown)
        M_DropDown->OnUpdate(MousePosition);

    /** M_Textfield **/
    if (M_Textfield)
        M_Textfield->OnUpdate(MousePosition);
}

// \brief Draw SF drawable components to screen
void Modal::OnDraw(sf::RenderWindow* Window)
{
    // *** Drawing to the screen *** //
    Window->draw(Container);
    Window->draw(HeaderText);
    Window->draw(Text);

    if (M_DropDown)
        M_DropDown->OnDraw(Window);

    for (auto& btn : Buttons)
        btn.second->OnDraw(Window);

    if (M_Textfield)
        M_Textfield->OnDraw(Window);
}