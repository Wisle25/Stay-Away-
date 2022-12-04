#pragma once

#include "Tile.hpp"

class Entity;
class Collider;

class TileMap
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    TileMap(float I_GridSize, sf::Vector2s& I_MaxWorld);
    TileMap(const std::string& Mapname);
    virtual ~TileMap();

    //////////////////////////////
    // Accessors
    //////////////////////////////
    const bool IsEmpty(const sf::Vector2f& Position) const;
    const unsh GetLayerSize(const sf::Vector2s& GridPosition) const;

    //////////////////////////////
    // Modifiers
    //////////////////////////////
    void SetVertices(const std::vector<sf::Vector2f>& I_Vertices);

    void AddTile(
        sf::Vector2f& Position,
        const std::string& TextureFile,
        bool Grid = false,
        bool AddCollision = false,
        unsh Type = NORMAL
    );
    void RemoveTile(const sf::Vector2f& Position);

    void SaveToFile(const std::string& Filename);
    void LoadFromFile(const std::string& Mapname);

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void Collision(Entity* Entity, const float& DeltaTime);
    void OnUpdate(const float& DeltaTime);
    void OnDraw(
        sf::RenderWindow* Window,
        const sf::Vector2s& GridPosition,
        bool ShowCollision = false,
        sf::Shader* Shader = nullptr,
        const sf::Vector2f& EntityPosition = sf::Vector2f()
    );
    void DrawDefered(
        sf::RenderWindow* Window,
        sf::Shader* Shader = nullptr,
        const sf::Vector2f& EntityPosition = sf::Vector2f()
    );

private:
    //////////////////////////////
    // Grid Size and Max World
    //////////////////////////////
    float GridSizeF;
    short GridSizeS;
    sf::Vector2f MaxWorldF;
    sf::Vector2s MaxWorldS;

    //////////////////////////////
    // Components
    //////////////////////////////
    /* 3rd dimension world */
    std::vector<std::vector<std::vector<Tile*>>> Map;
    std::vector<std::vector<std::vector<Collider*>>> Colliders;
    std::vector<sf::Vector2f> Vertices;

    std::stack<Tile*> TopTile;
    std::stack<Tile*> DeferedTile;

    //////////////////////////////
    // Initiate Methods
    //////////////////////////////
    void Clear();
};