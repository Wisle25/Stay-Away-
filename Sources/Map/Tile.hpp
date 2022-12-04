#pragma once

enum TTypes
{
    NORMAL,
    DEFERED
};

class Tile
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Tile();
    Tile(sf::Vector2f Position, float GridSize, const std::string& I_Texture, unsh I_Types);
    virtual ~Tile();

    /////////////////////////////
    // Accessors
    /////////////////////////////
    const sf::Vector2f& GetPosition() const;
    const std::string GetData() const;
    const sf::FloatRect GetBounds() const;
    const unsh GetType() const;
    const bool Contains(const sf::Vector2f& Position) const;

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnUpdate(const float& DeltaTime);
    void OnDraw(sf::RenderWindow* Window, sf::Shader* Shader, const sf::Vector2f& EntityPosition);

private:
    /////////////////////////////
    // SF Components
    /////////////////////////////
    sf::Sprite STile;
    sf::Texture Texture;
    unsh Type;

    // A Variable that used to save texture file name / path
    std::string TextureFile;
};