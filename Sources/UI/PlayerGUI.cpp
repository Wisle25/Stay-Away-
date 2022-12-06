// #include "stdpch.hpp"
// #include "PlayerGUI.hpp"

// /////////////// Constructor & Destructor ///////////////
// PlayerGUI::PlayerGUI(Player* i_player, sf::Font& i_font, Cvt& cvt):
//     player(i_player)
// {
//     // ******** Create HP Bar ******** //
//     bars["HP_BAR"] = new Bar(
//         sf::Vector2f(cvt.p2pX(85.4f), cvt.p2pY(13.6f)), // Position
//         sf::Vector2f(cvt.p2pX(13.2f), cvt.p2pY(1.6f)), // Size
//         i_font,
//         cvt.p2pChar(173)
//     );
//     // ******** END ******** //

//     // ******** Create EXP Bar ******** //
//     bars["EXP_BAR"] = new Bar(
//         sf::Vector2f(cvt.p2pX(85.4f), cvt.p2pY(16.6f)), // Position
//         sf::Vector2f(cvt.p2pX(13.2f), cvt.p2pY(1.6f)),
//         i_font,
//         cvt.p2pChar(173)
//     );
//     bars["EXP_BAR"]->setContentColor(sf::Color(3, 83, 151));
//     // ******** END ******** //
// }

// PlayerGUI::~PlayerGUI()
// {
//     for (auto& bar : bars)
//         delete bar.second;
// }

// /////////////// Modifiers ///////////////
// void PlayerGUI::setGUIOutlineColor(sf::Color color)
// {
//     for (auto& bar : bars)
//         bar.second->setContainerOutline(color, 2.f);
// }

// /////////////// Lifecycle Methods ///////////////
// void PlayerGUI::onUpdate()
// {
//     // ******** HP Bar ******** //
//     bars["HP_BAR"]->onUpdate(player->getAttribute()->hp, player->getAttribute()->maxHP, "HP");

//     /* Changing the hp color bar to red if it's less than the half maxHP */
//     if (player->getAttribute()->hp < player->getAttribute()->maxHP / 2)
//         bars["HP_BAR"]->setContentColor(sf::Color(255, 30, 0));
//     else
//         bars["HP_BAR"]->setContentColor(sf::Color(91, 179, 24));
//     // ******** END ******** //

//     // ******** Exp Bar ******** //
//     bars["EXP_BAR"]->onUpdate(player->getAttribute()->exp, player->getAttribute()->next_exp, "EXP");
//     // ******** END ******** //
// }

// void PlayerGUI::onDraw(sf::RenderTarget* target)
// {
//     // ******** onDrawing HP and EXP Bar ******** //
//     for (auto& bar : bars)
//         bar.second->onDraw(target);
//     // ******** END ******** //
// }