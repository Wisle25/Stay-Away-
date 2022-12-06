#include "stdpch.hpp"
#include "Core/Vector.hpp"
#include "Collider.hpp"

Collider::Collider()
{
}

Collider::Collider(const std::vector<sf::Vector2f>& I_Vertices):
    Vertices(I_Vertices),
    Origin({0.f, 0.f})
{
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

const String Collider::GetInformation() const
{
    std::stringstream Information;

    for (auto& Vertex : Vertices)
        Information << Vertex.x << " " << Vertex.y << " ";

    return Information.str();
}

const String Collider::GetData() const
{
    std::stringstream Information;

    // Getting Current Position and Vertices
    for (auto& Vertex : Vertices)
        Information << Vertex.x << " " << Vertex.y << " ";

    return Information.str();
}

void Collider::SetPosition(const sf::Vector2f& I_Position)
{
    sf::Vector2f Difference = I_Position - Position - Origin;

    for (int i = 0; i < Vertices.size(); ++i)
        Vertices[i] += Difference;

    Position = I_Position - Origin;
}

void Collider::SetOrigin(const sf::Vector2f& I_Origin)
{
    Origin = I_Origin;
}

void Collider::SetRotation(float Angle)
{
    float Difference = Angle - Rotation;

    for (unsh i = 0; i < Vertices.size(); ++i)
        Vertices[i] = Rotate(Vertices[i], Position, Difference);

    Rotation = Angle;
}

void Collider::SetColor(sf::Color I_Color)
{
    M_Color = I_Color;
}

void Collider::Move(sf::Vector2f Offset)
{
    SetPosition(Position + Offset + Origin);
}

void Collider::OnDraw(sf::RenderWindow& Window)
{
    sf::VertexArray Vertex = sf::VertexArray(sf::LineStrip, Vertices.size() + 1);

    for (short i = 0; i < Vertices.size(); ++i)
    {
        Vertex[i].position = Vertices[i];
        Vertex[i].color = M_Color;
    }

    Vertex[Vertices.size()].position = Vertices[0];
    Vertex[Vertices.size()].color = M_Color;

    Window.draw(Vertex);
}