#include "stdpch.hpp"

#include "Entities/Entity.hpp"

#include "TileMap.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
TileMap::TileMap(float I_GridSize, sf::Vector2s& I_MaxWorld):
    GridSizeF(I_GridSize),
    MaxWorldS(I_MaxWorld),
    MaxWorldF(I_MaxWorld)
{
    // *** Resizing array of tile to the max world *** //
    Map.resize(MaxWorldF.x, std::vector<std::vector<Tile*>>());
    for (short x = 0; x < MaxWorldF.x; x++)
        for (short y = 0; y < MaxWorldF.y; y++)
            Map[x].resize(MaxWorldF.y, std::vector<Tile*>());
}

// \brief Constructor to load a map from existed map
TileMap::TileMap(const std::string& Mapname)
{
    // *** Simply just call load from file function to construct *** //
    LoadFromFile(Mapname);
}

TileMap::~TileMap()
{
    Clear();
}

///////////// Accessors /////////////

// \brief Check is there a tile in the specified position
const bool TileMap::IsEmpty(const sf::Vector2f& Position) const
{
    return Map[Position.x][Position.y].empty();
}
///////////// Modifiers /////////////

// \brief Add a tile to the map
void TileMap::AddTile(sf::Vector2f& Position, const std::string& TextureFile, enum TTypes Type)
{
    // Grid position
    sf::Vector2s GridPosition = sf::Vector2s(Position / GridSizeF);

    if (GridPosition.x < MaxWorldS.x && GridPosition.x >= 0 &&
        GridPosition.y < MaxWorldS.y && GridPosition.y >= 0
    )
    {
        // If it's at first layer, we make it as ground which is it's GridPosition is fixed to the grid size
        if (Map[GridPosition.x][GridPosition.y].empty())
            Map[GridPosition.x][GridPosition.y].push_back(new Tile(sf::Vector2f(GridPosition), GridSizeF, TextureFile, Type));
        else
        {
            sf::Texture Texture;
            Texture.loadFromFile(TextureFile);
            // Modify the position so it origin is mouse cursor
            Position -= sf::Vector2f(Texture.getSize()) / 2.f;

            Map[GridPosition.x][GridPosition.y].push_back(new Tile(Position, 1, TextureFile, Type));
        }
    }
}

// \brief Remove a tile from the Map
void TileMap::RemoveTile(const sf::Vector2f& Position)
{
    // Grid position
    sf::Vector2s GridPosition = sf::Vector2s(Position / GridSizeF);

    if (GridPosition.x < MaxWorldS.x && GridPosition.x >= 0 &&
        GridPosition.y < MaxWorldS.y && GridPosition.y >= 0
    )
        if (!Map[GridPosition.x][GridPosition.y].empty())
        {
            unsh z = Map[GridPosition.x][GridPosition.y].size() - 1;

            if (z > 0 && Map[GridPosition.x][GridPosition.y][z]->Contains(Position))
            {
                delete Map[GridPosition.x][GridPosition.y][z];
                Map[GridPosition.x][GridPosition.y].pop_back();
            }
            else if (z == 0)
            {
                delete Map[GridPosition.x][GridPosition.y][z];
                Map[GridPosition.x][GridPosition.y].pop_back();
            }
        }
}

// \brief Save existed map to a file
void TileMap::SaveToFile(const std::string& Filename)
{
    std::ofstream outfile(Filename + ".gmap", std::ios_base::binary | std::ios::out);

    if (outfile.is_open())
    {
        // Write Base Data to file
        outfile.write((char*)&MaxWorldS, sizeof(sf::Vector2s));
        outfile.write((char*)&GridSizeS, sizeof(short));

        // Getting each tiles data then store it to file
        for (short x = 0; x < MaxWorldS.x; x++)
            for (short y = 0; y < MaxWorldS.y; y++)
                for (short z = 0; z < Map[x][y].size(); z++)
                    if (!Map[x][y].empty())
                    {
                        // Temp variable to save Map Data
                        std::string MapData = Map[x][y][z]->GetData();

                        outfile.write((char*)&x, sizeof(short));
                        outfile.write((char*)&y, sizeof(short));
                        outfile.write((char*)&z, sizeof(short));
                        outfile.write((char*)MapData.size(), sizeof(size_t));
                        outfile.write(MapData.c_str(), sizeof(char) * MapData.size());
                    }
    }

    outfile.close();
}

// \brief Load existed map from file
void TileMap::LoadFromFile(const std::string& Mapname)
{
    // Variables
    std::ifstream infile(Mapname + ".gmap", std::ios::out | std::ios::binary);
    sf::Vector2s GridPosition; // x y
    short Layer; // z

    if (infile.is_open())
    {
        // Getting Base Data from the File
        Clear(); // Clear the map first
        infile.read((char*)&MaxWorldS, sizeof(sf::Vector2s));
        infile.read((char*)&GridSizeS, sizeof(short));

        MaxWorldF = sf::Vector2f(MaxWorldS);
        GridSizeF = static_cast<float>(GridSizeS);

        // Reconstructing map (Literally the same as the default class constructor *Look at line 9*)
        Map.resize(MaxWorldS.x, std::vector<std::vector<Tile*>>());
        for (short x = 0; x < MaxWorldS.x; x++)
            for (short y = 0; y < MaxWorldS.y; y++)
                Map[x].resize(MaxWorldS.y, std::vector<Tile*>());

        // Getting each tile's data from file
        while (infile.read((char*)&GridPosition.x, sizeof(short)))
        {
            // Temp variable to save Map Data
            std::string MapData;
            size_t MapDataSize;

            std::string TextureFile;
            sf::Vector2f Position;
            unsh TypeS;

            infile.read((char*)&GridPosition.y, sizeof(short));
            infile.read((char*)&Layer, sizeof(short));
            infile.read((char*)&MapDataSize, sizeof(size_t));
            infile.read((char*)&MapData, sizeof(char) * MapDataSize);

            // Spread MapData to some items
            std::stringstream Ss(MapData);
            Ss >> TextureFile >> Position.x >> Position.y >> TypeS;

            enum TTypes Type = static_cast<enum TTypes>(TypeS);

            if (Layer > 0)
                Map[GridPosition.x][GridPosition.y].push_back(
                    new Tile(
                        Position,
                        1.f,
                        TextureFile,
                        Type
                    )
                );
            else
                Map[GridPosition.x][GridPosition.y].push_back(
                    new Tile(
                        sf::Vector2f(GridPosition),
                        GridSizeF,
                        TextureFile,
                        Type
                    )
                );
        }
    }
    infile.close();
}

///////////// Private Methods /////////////
void TileMap::Clear()
{
    if (!Map.empty())
    {
        // Clearing the Map if it's not empty only
        for (short x = 0; x < Map.size(); x++)
        {
            for (short y = 0; y < Map[x].size(); y++)
            {
                for (short z = 0; z < Map[x][y].size(); z++)
                {
                    delete this->Map[x][y][z];
                    this->Map[x][y][z] = NULL;
                }
                this->Map[x][y].clear();
            }
            this->Map[x].clear();
        }

        this->Map.clear();
    }
}

///////////// Lifecycle /////////////////

// \brief Handling collision beetween the entity and the world / map
void TileMap::Collision(Entity* Entity, const float& DeltaTime)
{

}

// \brief Called every frame, apply game logic here
void TileMap::OnUpdate(const float& DeltaTime)
{

}

// \brief Draw SF drawable components to screen
void TileMap::OnDraw(
    sf::RenderWindow* Window,
    const sf::Vector2s& GridPosition,
    sf::Shader* Shader,
    const sf::Vector2f& EntityPosition
)
{
    // Draw All Tiles
    for (short x = std::clamp(short(GridPosition.x - 15), (short)0, MaxWorldS.x); x < std::clamp(short(GridPosition.x + 16), (short)0, MaxWorldS.x); ++x)
        for (short y = std::clamp(short(GridPosition.y - 9), (short)0, MaxWorldS.y); y < std::clamp(short(GridPosition.y + 10), (short)0, MaxWorldS.y); ++y)
            for (short z = Map[x][y].size() - 1; z >= 0; --z)
                // We gonna draw the tile above anything if the type is defered
                if (Map[x][y][z]->GetType() == TTypes::DEFERED)
                    DeferedTile.push(Map[x][y][z]);
                else
                    if (z > 0)
                        TopTile.push(Map[x][y][z]);
                    else
                        Map[x][y][z]->OnDraw(Window, Shader, EntityPosition);

    // Drop some tiles that's on 1+ Layer
    while (!TopTile.empty())
    {
        TopTile.top()->OnDraw(Window, Shader, EntityPosition);
        TopTile.pop();
    }
}

// \brief Draw map above the player.
// NOTE: Make sure to call this function after all the component
void TileMap::DrawDefered(sf::RenderWindow* Window,
    sf::Shader* Shader,
    const sf::Vector2f& EntityPosition
)
{
    while (!DeferedTile.empty())
    {
        DeferedTile.top()->OnDraw(Window, Shader, EntityPosition);
        DeferedTile.pop();
    }
}