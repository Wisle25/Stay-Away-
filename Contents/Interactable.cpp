#include "stdpch.hpp"
#include "Interactable.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Interactable::Interactable(const String& Texture, sf::Vector2f Scale, sf::Vector2f Position):
    DefaultScale(Scale)
{
    // *** Initializing Sprite, Texture, and Boundaries *** //
    M_Texture.loadFromFile(Texture);

    M_Sprite.setTexture(M_Texture);
    M_Sprite.setScale(Scale);
    M_Sprite.setOrigin(
        M_Sprite.getGlobalBounds().left + M_Sprite.getGlobalBounds().width / 2.f,
        M_Sprite.getGlobalBounds().top + M_Sprite.getGlobalBounds().height / 2.f
    );
    M_Sprite.setPosition(Position);

    // Set the boundaries, we set the size of the boundaries based on
    // sprite size + some pixel
    M_Boundaries.setSize({
        M_Texture.getSize().x + 20.f,
        M_Texture.getSize().y + 20.f
    });
    M_Boundaries.setFillColor(sf::Color::Transparent);
    M_Boundaries.setOutlineColor(sf::Color::Blue);
    M_Boundaries.setOutlineThickness(-0.5f);
    M_Boundaries.setOrigin(
        M_Boundaries.getGlobalBounds().left + M_Boundaries.getGlobalBounds().width / 2.f,
        M_Boundaries.getGlobalBounds().top + M_Boundaries.getGlobalBounds().height / 2.f
    );
    M_Boundaries.setPosition(Position);
}

Interactable::~Interactable()
{

}

const sf::Vector2f& Interactable::GetDefaultScale() const
{
    return DefaultScale;
}

const bool Interactable::InBoundary(const sf::Vector2f& Position) const
{
    if (M_Boundaries.getGlobalBounds().contains(Position))
        return true;

    return false;
}

///////////// Lifecycle /////////////////

// \brief Draw SF drawable components to screen
void Interactable::OnDraw(sf::RenderWindow* Window)
{
    Window->draw(M_Sprite);
}