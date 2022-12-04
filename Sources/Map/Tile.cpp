#include "stdpch.hpp"
#include "Tile.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Default constructor
Tile::Tile()
{

}

// \brief Called once when at the first start

Tile::Tile(sf::Vector2f Position, float GridSize, const std::string& I_Texture, unsh I_Type):
    TextureFile(I_Texture),
    Type(I_Type)
{
    // *** Initializing the shape and Texture *** //
    Texture.loadFromFile(I_Texture);
    STile.setTexture(Texture);

    STile.setPosition(Position * GridSize);
}

Tile::~Tile()
{

}

///////////// Accessors /////////////////

// \brief Getting the position of each tile
const sf::Vector2f& Tile::GetPosition() const
{
    return STile.getPosition();
}

// \brief Getting some datas that needed to save map information
const std::string Tile::GetData() const
{
    std::stringstream Data;

    Data << TextureFile << " " << STile.getPosition().x << " " << STile.getPosition().y << " " << Type << " ";

    return Data.str();
}

const sf::FloatRect Tile::GetBounds() const
{
    return STile.getGlobalBounds();
}

const unsh Tile::GetType() const
{
    return Type;
}

// \brief Checking is the tile contains mouse position or not
const bool Tile::Contains(const sf::Vector2f& Position) const
{
    return STile.getGlobalBounds().contains(Position);
}

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void Tile::OnUpdate(const float& DeltaTime)
{

}

// \brief Draw SF drawable components to screen
void Tile::OnDraw(sf::RenderWindow* Window, sf::Shader* Shader, const sf::Vector2f& EntityPosition)
{
    if (Shader)
    {
        Shader->setUniform("hasTexture", true);
        Shader->setUniform("light", EntityPosition);
        Window->draw(STile, Shader);
    }
    else
        Window->draw(STile);
}