#include "stdpch.hpp"

#include "Entities/Entity.hpp"

#include "Systems/Collision/Collider.hpp"
#include "Systems/Collision/Collision.hpp"

#include "TileMap.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
TileMap::TileMap(float I_GridSize, sf::Vector2s& I_MaxWorld):
    GridSizeF(I_GridSize),
    GridSizeS(I_GridSize),
    MaxWorldS(I_MaxWorld),
    MaxWorldF(I_MaxWorld)
{
    Clear();

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
TileMap::TileMap(const String& Mapname)
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
void TileMap::AddTile(sf::Vector2f& Position, const String& TextureFile, bool Grid, bool Collision, unsh Type)
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
        if (Collision)
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

void TileMap::AddCollision(const sf::Vector2f& Position)
{
    // Grid position
    sf::Vector2s GridPosition = sf::Vector2s(Position / GridSizeF);

    if (GridPosition.x < MaxWorldS.x && GridPosition.x >= 0 &&
        GridPosition.y < MaxWorldS.y && GridPosition.y >= 0
    )
    {
        unsh z = Colliders[GridPosition.x][GridPosition.y].size();

        Colliders[GridPosition.x][GridPosition.y].push_back(
            new Collider(Vertices)
        );
        Colliders[GridPosition.x][GridPosition.y][z]->SetPosition(Position);
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

void TileMap::RemoveCollision(const sf::Vector2f& Position)
{
    // Grid position
    sf::Vector2s GridPosition = sf::Vector2s(Position / GridSizeF);

    if (GridPosition.x < MaxWorldS.x && GridPosition.x >= 0 &&
        GridPosition.y < MaxWorldS.y && GridPosition.y >= 0
    )
        // Removing Colliders
        if (!Colliders[GridPosition.x][GridPosition.y].empty())
        {
            unsh z = Colliders[GridPosition.x][GridPosition.y].size() - 1; /* z is Z Position of Collider*/

            delete Colliders[GridPosition.x][GridPosition.y][z];
            Colliders[GridPosition.x][GridPosition.y].pop_back();
        }
}

// \brief Save existed map to a file
void TileMap::SaveToFile(const String& Filename)
{
    std::ofstream OutFile("../Data/Map/" + Filename + ".gmap", std::ios::binary | std::ios::out);

    if (OutFile.is_open())
    {
        // Write Base Data to file
        OutFile.write((char*)&MaxWorldS, sizeof(sf::Vector2s));
        OutFile.write((char*)&GridSizeS, sizeof(short));

        // Getting each tiles data then store it to file
        for (short x = 0; x < MaxWorldS.x; ++x)
            for (short y = 0; y < MaxWorldS.y; ++y)
                for (short z = 0; z < Map[x][y].size(); ++z)
                    if (!Map[x][y].empty())
                    {
                        // Temp variable to save Map Data
                        String MapData = Map[x][y][z]->GetData();
                        unsh Length = MapData.size();

                        String Type = "Tile";
                        unsh TypeLength = Type.size();

                        // Position
                        OutFile.write((char*)&x, sizeof(short));
                        OutFile.write((char*)&y, sizeof(short));
                        OutFile.write((char*)&z, sizeof(short));

                        // Type and Data
                        OutFile.write((char*)&TypeLength, sizeof(unsh));
                        OutFile.write(Type.c_str(), Type.size());
                        OutFile.write((char*)&Length, sizeof(unsh));
                        OutFile.write(MapData.c_str(), MapData.size());
                    }

        // Getting each Colliders data then store it to file
        for (short x = 0; x < MaxWorldS.x; ++x)
            for (short y = 0; y < MaxWorldS.y; ++y)
                for (short z = 0; z < Colliders[x][y].size(); ++z)
                    if (!Colliders[x][y].empty())
                    {
                        // Temp variable to save Colliders Data
                        String CollidersData = Colliders[x][y][z]->GetData();
                        unsh Length = CollidersData.size();

                        String Type = "Collider";
                        unsh TypeLength = Type.size();

                        // Position
                        OutFile.write((char*)&x, sizeof(short));
                        OutFile.write((char*)&y, sizeof(short));
                        OutFile.write((char*)&z, sizeof(short));

                        // Type and Data
                        OutFile.write((char*)&TypeLength, sizeof(unsh));
                        OutFile.write(Type.c_str(), Type.size());
                        OutFile.write((char*)&Length, sizeof(unsh));
                        OutFile.write(CollidersData.c_str(), CollidersData.size());
                    }
    }

    OutFile.close();
}

// \brief Load existed map from file
void TileMap::LoadFromFile(const String& Mapname)
{
    // Variables
    std::ifstream InFile("../Data/Map/" + Mapname + ".gmap", std::ios::binary | std::ios::in);
    sf::Vector2s GridPosition; // x y
    short Layer; // z

    if (InFile.is_open())
    {
        // Getting Base Data from the File
        Clear(); // Clear the map first
        InFile.read((char*)&MaxWorldS, sizeof(sf::Vector2s));
        InFile.read((char*)&GridSizeS, sizeof(short));

        MaxWorldF = sf::Vector2f(MaxWorldS);
        GridSizeF = static_cast<float>(GridSizeS);

        // Reconstructing map (Literally the same as the default class constructor *Look at line 9*)
        Map.resize(MaxWorldS.x, std::vector<std::vector<Tile*>>());
        Colliders.resize(MaxWorldS.x, std::vector<std::vector<Collider*>>());
        for (short x = 0; x < MaxWorldS.x; ++x)
            for (short y = 0; y < MaxWorldS.y; ++y)
            {
                Map[x].resize(MaxWorldS.y, std::vector<Tile*>());
                Colliders[x].resize(MaxWorldS.y, std::vector<Collider*>());
            }

        // Getting each tile's data from file
        while (InFile.read((char*)&GridPosition.x, sizeof(short)))
        {
            InFile.read((char*)&GridPosition.y, sizeof(short));
            InFile.read((char*)&Layer, sizeof(short));

            unsh TypeSize;
            String Type;
            char* TypeBuffer;

            InFile.read((char*)&TypeSize, sizeof(unsh));
            TypeBuffer = new char[TypeSize + 1];
            InFile.read(TypeBuffer, TypeSize);
            TypeBuffer[TypeSize] = '\0';
            Type = TypeBuffer;

            if (Type == "Tile")
            {
                String TextureFile;
                sf::Vector2f Position;
                unsh TypeTile;

                unsh MapDataSize;
                String MapData;
                char* MapDataBuffer;

                // Unreadable Part :)
                InFile.read((char*)&MapDataSize, sizeof(unsh));
                MapDataBuffer = new char[MapDataSize + 1];
                InFile.read(MapDataBuffer, MapDataSize);
                MapDataBuffer[MapDataSize] = '\0';
                MapData = MapDataBuffer;

                // Spread MapData to some items
                std::stringstream Ss(MapData);
                Ss >> TextureFile >> Position.x >> Position.y >> TypeTile;

                // Finally insert tile to the variables
                if (Layer > 0)
                    Map[GridPosition.x][GridPosition.y].push_back(
                        new Tile(
                            Position,
                            1.f,
                            TextureFile,
                            TypeTile
                        )
                    );
                else
                    Map[GridPosition.x][GridPosition.y].push_back(
                        new Tile(
                            sf::Vector2f(GridPosition),
                            GridSizeF,
                            TextureFile,
                            TypeTile
                        )
                    );

                delete[] MapDataBuffer;
            }
            else if (Type == "Collider")
            {
                String CollidersData;
                char* CollidersDataBuffer;
                unsh CollidersDataSize;

                // Unreadable Part :)
                InFile.read((char*)&CollidersDataSize, sizeof(unsh));
                CollidersDataBuffer = new char[CollidersDataSize + 1];
                InFile.read(CollidersDataBuffer, CollidersDataSize);
                CollidersDataBuffer[CollidersDataSize] = '\0';
                CollidersData = CollidersDataBuffer;

                // Getting position each Vertices
                std::vector<sf::Vector2f> T_Vertices;
                sf::Vector2f TV; // TV = Temp Vertex
                std::stringstream VS(CollidersData); // VS = Vertices Stream
                while (VS >> TV.x >> TV.y)
                    T_Vertices.push_back(TV);

                // Finally insert it to variables
                Colliders[GridPosition.x][GridPosition.y].push_back(
                    new Collider(T_Vertices)
                );

                delete[] CollidersDataBuffer;
            }

            delete[] TypeBuffer;
        }
    }
    InFile.close();
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
void TileMap::OnCollision(Entity* Entity)
{
    for (short x = std::clamp(short(Entity->GetPositionGrid(GridSizeF).x - 1), (short)0, MaxWorldS.x);
         x < std::clamp(short(Entity->GetPositionGrid(GridSizeF).x + 3), (short)0, MaxWorldS.x);
         x++
        )
        for (short y = std::clamp(short(Entity->GetPositionGrid(GridSizeF).y - 1), (short)0, MaxWorldS.y);
             y < std::clamp(short(Entity->GetPositionGrid(GridSizeF).y + 3), (short)0, MaxWorldS.y);
             y++
            )
            for (short z = 0; z < Colliders[x][y].size(); z++)
            {
                sf::Vector2f MTV;

                if (Collision(Entity->GetCollider(), Colliders[x][y][z], MTV))
                    Entity->ResetVelocity();

                Entity->Move(MTV);
            }
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
    if (ShowCollision)
    for (short x = std::clamp(short(GridPosition.x - 15), (short)0, MaxWorldS.x); x < std::clamp(short(GridPosition.x + 16), (short)0, MaxWorldS.x); ++x)
        for (short y = std::clamp(short(GridPosition.y - 9), (short)0, MaxWorldS.y); y < std::clamp(short(GridPosition.y + 10), (short)0, MaxWorldS.y); ++y)
            for (short z = 0; z < Colliders[x][y].size(); ++z)
                Colliders[x][y][z]->OnDraw(*Window);
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