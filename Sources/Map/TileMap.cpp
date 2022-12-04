#include "stdpch.hpp"

#include "Entities/Entity.hpp"
#include "Systems/Collision/Collider.hpp"

#include "TileMap.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
TileMap::TileMap(float I_GridSize, sf::Vector2s& I_MaxWorld):
    GridSizeF(I_GridSize),
    GridSizeS(I_GridSize),
    MaxWorldS(I_MaxWorld),
    MaxWorldF(I_MaxWorld)
{
    // *** Resizing array of tile to the max world *** //
    Map.resize(MaxWorldS.x, std::vector<std::vector<Tile*>>());
    Colliders.resize(MaxWorldS.x, std::vector<std::vector<Collider*>>());
    for (short x = 0; x < MaxWorldS.x; x++)
        for (short y = 0; y < MaxWorldS.y; y++)
        {
            Map[x].resize(MaxWorldS.y, std::vector<Tile*>());
            Colliders[x].resize(MaxWorldS.y, std::vector<Collider*>());
        }
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

const unsh TileMap::GetLayerSize(const sf::Vector2s& GridPosition) const
{
    return Map[GridPosition.x][GridPosition.y].size();
}

///////////// Modifiers /////////////

// Set the vertices
void TileMap::SetVertices(const std::vector<sf::Vector2f>& I_Vertices)
{
    Vertices = I_Vertices;
}

// \brief Add a tile to the map
void TileMap::AddTile(sf::Vector2f& Position, const std::string& TextureFile, bool Grid, bool AddCollision, unsh Type)
{
    // Grid position
    sf::Vector2s GridPosition = sf::Vector2s(Position / GridSizeF);

    if (GridPosition.x < MaxWorldS.x && GridPosition.x >= 0 &&
        GridPosition.y < MaxWorldS.y && GridPosition.y >= 0
    )
    {
        // Modify the position so it origin is mouse cursor
        sf::Texture Texture;
        Texture.loadFromFile(TextureFile);
        Position -= sf::Vector2f(Texture.getSize()) / 2.f;

        // If it's at first layer or based on grid position
        // we make it as ground which is it's Position is fixed to the Grid Position
        if (Map[GridPosition.x][GridPosition.y].empty() || Grid)
            Map[GridPosition.x][GridPosition.y].push_back(new Tile(sf::Vector2f(GridPosition), GridSizeF, TextureFile, Type));
        else
            Map[GridPosition.x][GridPosition.y].push_back(new Tile(Position, 1, TextureFile, Type));

        // Reset the origin
        Position += sf::Vector2f(Texture.getSize()) / 2.f;
        if (AddCollision)
        {
            unsh z = Colliders[GridPosition.x][GridPosition.y].size();

            Colliders[GridPosition.x][GridPosition.y].push_back(
                new Collider(Vertices)
            );
            sf::Vector2f Pos = sf::Vector2f(GridPosition * GridSizeS) + sf::Vector2f(Texture.getSize()) / 2.f;
            Colliders[GridPosition.x][GridPosition.y][z]->SetPosition(
                Grid ? Pos : Position
            );
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

                // Also removing collider if it has collision
                if (!Colliders[GridPosition.x][GridPosition.y].empty())
                {
                    unsh zC = Colliders[GridPosition.x][GridPosition.y].size() - 1; /* zC is Z Position of Collider*/

                    delete Colliders[GridPosition.x][GridPosition.y][zC];
                    Colliders[GridPosition.x][GridPosition.y].pop_back();
                }
            }
            else if (z == 0)
            {
                delete Map[GridPosition.x][GridPosition.y][z];
                Map[GridPosition.x][GridPosition.y].pop_back();

                // Also removing collider if it has collision
                if (!Colliders[GridPosition.x][GridPosition.y].empty())
                {
                    unsh zC = Colliders[GridPosition.x][GridPosition.y].size() - 1; /* zC is Z Position of Collider*/

                    delete Colliders[GridPosition.x][GridPosition.y][zC];
                    Colliders[GridPosition.x][GridPosition.y].pop_back();
                }
            }
        }
}

// \brief Save existed map to a file
void TileMap::SaveToFile(const std::string& Filename)
{
    std::ofstream outfile("../Data/Map/" + Filename + ".gmap", std::ios::binary | std::ios::out);

    if (outfile.is_open())
    {
        // Write Base Data to file
        outfile.write((char*)&MaxWorldS, sizeof(sf::Vector2s));
        outfile.write((char*)&GridSizeS, sizeof(short));

        // Getting each tiles data then store it to file
        for (int x = 0; x < MaxWorldS.x; ++x)
            for (int y = 0; y < MaxWorldS.y; ++y)
                for (int z = 0; z < Map[x][y].size(); ++z)
                    if (!Map[x][y].empty())
                    {
                        // Temp variable to save Map Data
                        std::string MapData = Map[x][y][z]->GetData();
                        unsh Length = MapData.size();

                        outfile.write((char*)&x, sizeof(int));
                        outfile.write((char*)&y, sizeof(int));
                        outfile.write((char*)&z, sizeof(int));
                        outfile.write((char*)&Length, sizeof(unsh));
                        outfile.write(MapData.c_str(), MapData.size());
                    }

        // Getting each Colliders data then store it to file
        for (short x = 0; x < MaxWorldS.x; ++x)
            for (short y = 0; y < MaxWorldS.y; ++y)
                for (short z = 0; z < Colliders[x][y].size(); ++z)
                    if (!Colliders[x][y].empty())
                    {
                        // Temp variable to save Colliders Data
                        std::string CollidersData = Colliders[x][y][z]->GetData();
                        unsh Length = CollidersData.size();

                        outfile.write((char*)&x, sizeof(short));
                        outfile.write((char*)&y, sizeof(short));
                        outfile.write((char*)&z, sizeof(short));
                        outfile.write((char*)&Length, sizeof(unsh));
                        outfile.write(CollidersData.c_str(), CollidersData.size());
                    }
    }

    outfile.close();
}

// \brief Load existed map from file
void TileMap::LoadFromFile(const std::string& Mapname)
{
    // Variables
    std::ifstream infile("../Data/Map/" + Mapname + ".gmap", std::ios::binary | std::ios::in);
    sf::Vector2i GridTile; // x y
    int LayerTile; // z

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
        while (infile.read((char*)&GridTile.x, sizeof(int)))
        {
            // Temp variable to save Map Data
            std::string MapData;
            char* MapDataBuffer;
            unsh MapDataSize;

            std::string TextureFile;
            sf::Vector2f Position;
            unsh Type;

            infile.read((char*)&GridTile.y, sizeof(int));
            infile.read((char*)&LayerTile, sizeof(int));

            // Unreadable Part :)
            infile.read((char*)&MapDataSize, sizeof(unsh));
            MapDataBuffer = new char[MapDataSize + 1];
            infile.read(MapDataBuffer, MapDataSize);
            MapDataBuffer[MapDataSize] = '\0';
            MapData = MapDataBuffer;

            // Spread MapData to some items
            std::stringstream Ss(MapData);
            Ss >> TextureFile >> Position.x >> Position.y >> Type;

            // Finally insert tile to the variables
            if (LayerTile > 0)
                Map[GridTile.x][GridTile.y].push_back(
                    new Tile(
                        Position,
                        1.f,
                        TextureFile,
                        Type
                    )
                );
            else
                Map[GridTile.x][GridTile.y].push_back(
                    new Tile(
                        sf::Vector2f(GridTile),
                        GridSizeF,
                        TextureFile,
                        Type
                    )
                );

            delete[] MapDataBuffer;
        }

        sf::Vector2s GridColl; // x y
        short LayerColl; // z

        // Getting each collider's data from file
        while (infile.read((char*)&GridColl.x, sizeof(short)))
        {
            std::cout << "Im executed" << std::endl;
            // Temp variable to save Colliders Data
            std::string CollidersData;
            char* CollidersDataBuffer;
            unsh CollidersDataSize;

            sf::Vector2f Position;

            infile.read((char*)&GridColl.y, sizeof(short));
            infile.read((char*)&LayerColl, sizeof(short));

            // Unreadable Part :)
            infile.read((char*)&CollidersDataSize, sizeof(unsh));
            CollidersDataBuffer = new char[CollidersDataSize + 1];
            infile.read(CollidersDataBuffer, CollidersDataSize);
            CollidersDataBuffer[CollidersDataSize] = '\0';
            CollidersData = CollidersDataBuffer;

            // Getting position each Vertices
            std::vector<sf::Vector2f> T_Vertices;
            sf::Vector2f TV; // TV = Temp Vertex
            std::stringstream VS(CollidersData); // VS = Vertices Stream
            VS >> Position.x >> Position.y;
            while (VS >> TV.x >> TV.y)
                T_Vertices.push_back(TV);

            // Finally insert it to variables
            Colliders[GridColl.x][GridColl.y].push_back(
                new Collider(Vertices)
            );
            Colliders[GridColl.x][GridColl.y][LayerColl]->SetPosition(Position);

            delete[] CollidersDataBuffer;
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
                    delete Map[x][y][z];
                    Map[x][y][z] = NULL;
                }
                Map[x][y].clear();
            }
            Map[x].clear();
        }

        Map.clear();
    }

    if (!Colliders.empty())
    {
        // Clearing the Colliders if it's not empty only
        for (short x = 0; x < Colliders.size(); x++)
        {
            for (short y = 0; y < Colliders[x].size(); y++)
            {
                for (short z = 0; z < Colliders[x][y].size(); z++)
                {
                    delete Colliders[x][y][z];
                    Colliders[x][y][z] = NULL;
                }
                Colliders[x][y].clear();
            }
            Colliders[x].clear();
        }

        Colliders.clear();
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
    bool ShowCollision,
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

    // We will draw the collision if user want to show it
    // if (ShowCollision)
    // for (short x = std::clamp(short(GridPosition.x - 15), (short)0, MaxWorldS.x); x < std::clamp(short(GridPosition.x + 16), (short)0, MaxWorldS.x); ++x)
    //     for (short y = std::clamp(short(GridPosition.y - 9), (short)0, MaxWorldS.y); y < std::clamp(short(GridPosition.y + 10), (short)0, MaxWorldS.y); ++y)
    //         for (short z = 0; z < Colliders[x][y].size(); ++z)
    //             Colliders[x][y][z]->OnDraw(*Window);
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