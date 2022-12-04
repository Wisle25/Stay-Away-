#include "stdpch.hpp"
#include "Core/Vector.hpp"
#include "Collider.hpp"

Collider::Collider()
{
}

Collider::Collider(std::vector<sf::Vector2f>& I_Vertices)
{
    Vertices = I_Vertices;

    Position = GetCenter();
}

sf::Vector2f Collider::GetCenter() const
{
    sf::Vector2f Center;

    int Count = Vertices.size();

    float A = 0.f;
    float Area = 0.f;

    for (int i = 0; i < Count; ++i)
    {
        auto& V0 = Vertices[i];
        auto& V1 = Vertices[i + 1 != Count ? i + 1 : 0];

        float B = VectorCross(V0, V1);

        A += B;

        Center += (V0 + V1) * B;
    }

    Center *= 1.f / (3.f * A);

    return Center;
}

const std::vector<sf::Vector2f>& Collider::GetVertices() const
{
    return Vertices;
}

const sf::Vector2f& Collider::GetPosition() const
{
    return Position;
}

const std::string Collider::GetInformation() const
{
    std::stringstream Information;

    for (auto& Vertex : Vertices)
        Information << Vertex.x << " " << Vertex.y << " ";

    return Information.str();
}

const std::string Collider::GetData() const
{
    std::stringstream Information;

    // Getting Current Position and Vertices
    Information << Position.x << " " << Position.y << " ";
    for (auto& Vertex : Vertices)
        Information << Vertex.x << " " << Vertex.y << " ";

    return Information.str();
}

void Collider::SetPosition(const sf::Vector2f& I_Position)
{
    sf::Vector2f Difference = I_Position - Position;

    for (int i = 0; i < Vertices.size(); ++i)
        Vertices[i] += Difference;

    Position = I_Position;
}

void Collider::Move(sf::Vector2f Offset)
{
    SetPosition(Position + Offset);
}

void Collider::OnDraw(sf::RenderWindow& Window)
{
    sf::VertexArray Vertex = sf::VertexArray(sf::LineStrip, Vertices.size() + 1);

    for (short i = 0; i < Vertices.size(); ++i)
    {
        Vertex[i].position = Vertices[i];
        Vertex[i].color = sf::Color::Red;
    }

    Vertex[Vertices.size()].position = Vertices[0];
    Vertex[Vertices.size()].color = sf::Color::Red;

    Window.draw(Vertex);
}