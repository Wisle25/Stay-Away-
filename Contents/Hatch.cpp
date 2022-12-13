#include "stdpch.hpp"

#include "Entities/Player.hpp"
#include "UI/Converter.hpp"

#include "Hatch.hpp"

///////////// Constructor & Destructor /////////////////

Hatch::Hatch(Converter& Cvt, sf::Vector2f Scale, sf::Vector2f Position):
    Interactable("../Resources/item/hatch_1.png", Scale, Position)
{
    // *** Initializing Text *** //
    Text.loadFromFile("../Resources/escapedfix.png");
    Shape.setTexture(Text);
    Shape.setScale(0.5f, 0.5f);
    Shape.setOrigin(
        Shape.getGlobalBounds().width / 2.f,
        Shape.getGlobalBounds().height / 2.f
    );
    Shape.setPosition(Cvt.P2PX(50.f), Cvt.P2PY(14.f));
}

Hatch::~Hatch()
{
}

///////////// Lifecycle /////////////

void Hatch::OnUpdate(const float& DeltaTime)
{
}

void Hatch::OnDraw(sf::RenderWindow* Window)
{
    // Inheritance
    Interactable::OnDraw(Window);

    Window->draw(Shape);
}