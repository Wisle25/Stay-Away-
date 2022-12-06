#include "stdpch.hpp"

#include "Systems/Attributes.hpp"
#include "UI/Micro/Bar.hpp"
#include "UI/Converter.hpp"

#include "PlayerGUI.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
PlayerGUI::PlayerGUI(Converter& Cvt, sf::Font& Font)
{
    // *** Initializing HP Bar *** //
    HP_Bar = new Bar({
        .Size = { Cvt.P2PX(16.f), Cvt.P2PY(2.6f) },
        .Position = { Cvt.P2PX(82.6f), Cvt.P2PY(4.6) },
        .Font = Font,
        .CharSize = Cvt.P2PChar(170)
    });

    Stamina_Bar = new Bar({
        .Size = { Cvt.P2PX(16.f), Cvt.P2PY(2.6f) },
        .Position = { Cvt.P2PX(82.6f), Cvt.P2PY(8.2) },
        .Font = Font,
        .CharSize = Cvt.P2PChar(170)
    });
}

PlayerGUI::~PlayerGUI()
{
    delete HP_Bar;
    delete Stamina_Bar;
}

///////////// Private Methods /////////////

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void PlayerGUI::OnUpdate(Attributes* I_Attribute)
{
    // *** Updating Health Point Bar *** //
    HP_Bar->OnUpdate(I_Attribute->HP, I_Attribute->MaxHP, "Health");
    if (I_Attribute->HP < I_Attribute->MaxHP / 4.f)
        HP_Bar->SetContentColor(sf::Color(220, 53, 53));
    else if (I_Attribute->HP < I_Attribute->MaxHP / 3.f)
        HP_Bar->SetContentColor(sf::Color(255, 225, 93));
    else
        HP_Bar->SetContentColor(sf::Color(56, 229, 77));

    Stamina_Bar->OnUpdate(I_Attribute->Stamina, I_Attribute->MaxStamina, "Stamina");
    Stamina_Bar->SetContentColor(sf::Color(51, 47, 208));
}

// \brief Draw SF drawable components to screen
void PlayerGUI::OnDraw(sf::RenderWindow* Window)
{
    HP_Bar->OnDraw(Window);
    Stamina_Bar->OnDraw(Window);
}