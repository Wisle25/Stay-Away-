#include "stdpch.hpp"

#include "UI/Components/Dropdown.hpp"

#include "SettingsState.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
SettingsState::SettingsState(Context* I_Ctx):
    State(I_Ctx)
{
    // *** Initializing Titles *** //
    TitleText.setFont(Ctx->SecondFont);
    TitleText.setFillColor(sf::Color(207, 10, 10));
    TitleText.setCharacterSize(Cvt.P2PChar(50));
    TitleText.setString("Settings");
    TitleText.setOrigin(
        TitleText.getGlobalBounds().left + TitleText.getGlobalBounds().width / 2.f,
        TitleText.getGlobalBounds().height + TitleText.getGlobalBounds().height / 2.f
    );
    TitleText.setPosition({ Cvt.P2PX(50.f), Cvt.P2PY(20.f) });
    // *** END *** //

    // *** Initializing Settings *** //
    /** Graphics **/
    SessionText.push_back(sf::Text());
    SessionText[0].setFont(Ctx->SecondFont);
    SessionText[0].setFillColor(sf::Color(207, 10, 10));
    SessionText[0].setCharacterSize(Cvt.P2PChar(80));
    SessionText[0].setString("Graphics");
    SessionText[0].setOrigin(
        SessionText[0].getGlobalBounds().left + SessionText[0].getGlobalBounds().width / 2.f,
        SessionText[0].getGlobalBounds().height + SessionText[0].getGlobalBounds().height / 2.f
    );
    SessionText[0].setPosition({ Cvt.P2PX(20.f), Cvt.P2PY(40.f) });

    /* Resolution */
    SettingsName["Resolution"] = sf::Text();
    SettingsName["Resolution"].setFont(Ctx->SecondFont);
    SettingsName["Resolution"].setFillColor(sf::Color(207, 10, 10));
    SettingsName["Resolution"].setCharacterSize(Cvt.P2PChar(100));
    SettingsName["Resolution"].setString("Settings");
    SettingsName["Resolution"].setOrigin(
        SettingsName["Resolution"].getGlobalBounds().left + SettingsName["Resolution"].getGlobalBounds().width / 2.f,
        SettingsName["Resolution"].getGlobalBounds().height + SettingsName["Resolution"].getGlobalBounds().height / 2.f
    );
    SettingsName["Resolution"].setPosition({ Cvt.P2PX(20.f), Cvt.P2PY(35.f) });

    std::vector<sf::VideoMode> Resolution = sf::VideoMode::getFullscreenModes();
    std::vector<String> ResolutionList;

    for (unsh i = 0; i < Resolution.size(); ++i)
    {
        std::stringstream SS;
        SS << Resolution[i].width << " x " << Resolution[i].height;

        ResolutionList.push_back(SS.str());
    }

    Settings["Resolution"] = new Dropdown(
        {
            .Size = { Cvt.P2PX(10.f), Cvt.P2PY(4.f) },
            .Position = { Cvt.P2PX(66.f), Cvt.P2PY(35.f) },
            .Font = Ctx->MainFont,
            .CharSize = Cvt.P2PChar(140)
        },
        {
            .IdleColor = Ctx->MainColor,
            .HoverColor = sf::Color(166, 35, 73),
            .ActiveColor = sf::Color(99, 6, 6),
        },
        ResolutionList,
        &EventQueue
    );
    // *** END *** //
}

SettingsState::~SettingsState()
{
    for (auto& Setting : Settings)
        delete Setting.second;

    for (auto& Btn : Btns)
        delete Btn.second;
}

///////////// Private Methods /////////////

///////////// Lifecycle /////////////////

// \brief Handling input
void SettingsState::OnInput(sf::Event* Event)
{

}

// \brief Called every frame, apply game logic here
void SettingsState::OnUpdate(const float& DeltaTime)
{
    for (auto& Setting : Settings)
        Setting.second->OnUpdate(MouseWindow);
}

// \brief Draw SF drawable components to screen
void SettingsState::OnDraw(sf::RenderWindow* Window)
{
    Window->draw(TitleText);

    for (auto& Text : SessionText)
        Window->draw(Text);

    for (auto& Name : SettingsName)
        Window->draw(Name.second);

    for (auto& Setting : Settings)
        Setting.second->OnDraw(Window);
}