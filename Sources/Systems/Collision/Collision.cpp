#include "stdpch.hpp"

#include "Core/Vector.hpp"
#include "Collider.hpp"

#include "Collision.hpp"

bool Collision(const Collider* ColliderA, const Collider* ColliderB, sf::Vector2f& MTV)
{
    float MinOverlap = INFINITY;

    std::vector<sf::Vector2f> ColliderAVertices = ColliderA->GetVertices();
    std::vector<sf::Vector2f> ColliderBVertices = ColliderB->GetVertices();

    short ColliderACount = ColliderA->GetVertices().size();
    short ColliderBCount = ColliderB->GetVertices().size();

    short All = ColliderACount + ColliderBCount;

    sf::Vector2f* Axis = new sf::Vector2f[All];

    for (short i = 0; i < ColliderACount; ++i)
        Axis[i] = Perpendicular(ColliderAVertices, i, ColliderACount);

    for (short i = 0; i < ColliderBCount; ++i)
        Axis[i + ColliderACount] = Perpendicular(ColliderBVertices, i, ColliderBCount);

    for (short i = 0; i < All; ++i)
    {
        auto& A = Axis[i];

        sf::Vector2f ColliderAProjection = ProjectOnto(ColliderAVertices, ColliderACount, A);
        sf::Vector2f ColliderBProjection = ProjectOnto(ColliderBVertices, ColliderBCount, A);

        float Overlap = CheckOverlap(ColliderAProjection, ColliderBProjection);

        if (!Overlap)
        {
            MTV = sf::Vector2f(0.f, 0.f);

            delete[] Axis;

            return false;
        }
        else
            if (Overlap < MinOverlap)
            {
                MinOverlap = Overlap;

                MTV = A * Overlap;
            }
    }

    if (VectorDot(ColliderA->GetCenter() - ColliderB->GetCenter(), MTV) < 0.f)
        MTV *= -1.f;

    delete[] Axis;
    return true;
}

bool Collision(const Collider* ColliderA, const Collider* ColliderB)
{
    float MinOverlap = INFINITY;

    std::vector<sf::Vector2f> ColliderAVertices = ColliderA->GetVertices();
    std::vector<sf::Vector2f> ColliderBVertices = ColliderB->GetVertices();

    short ColliderACount = ColliderA->GetVertices().size();
    short ColliderBCount = ColliderB->GetVertices().size();

    short All = ColliderACount + ColliderBCount;

    sf::Vector2f* Axis = new sf::Vector2f[All];

    for (short i = 0; i < ColliderACount; ++i)
        Axis[i] = Perpendicular(ColliderAVertices, i, ColliderACount);

    for (short i = 0; i < ColliderBCount; ++i)
        Axis[i + ColliderACount] = Perpendicular(ColliderBVertices, i, ColliderBCount);

    for (short i = 0; i < All; ++i)
    {
        auto& A = Axis[i];

        sf::Vector2f ColliderAProjection = ProjectOnto(ColliderAVertices, ColliderACount, A);
        sf::Vector2f ColliderBProjection = ProjectOnto(ColliderBVertices, ColliderBCount, A);

        float Overlap = CheckOverlap(ColliderAProjection, ColliderBProjection);

        if (!Overlap)
        {
            delete[] Axis;
            return false;
        }
    }

    delete[] Axis;
    return true;
}

sf::Vector2f Perpendicular(std::vector<sf::Vector2f>& Vertices, short Index, short Count)
{
    short I0 = Index + 1;
    short I1 = Index;

    if (I0 == Count)
    {
        I0 = 0;
        I1 = Count - 1;
    }

    sf::Vector2f V = VectorNormalized(Vertices[I0] - Vertices[I1]);

    return { -V.y, V.x };
}

sf::Vector2f ProjectOnto(std::vector<sf::Vector2f>& Vertices, short Count, sf::Vector2f Axis)
{
    float Min =  INFINITY;
    float Max = -INFINITY;

    for (short i = 0; i < Count; ++i)
    {
        float Projection = VectorDot(Vertices[i], Axis);

        if (Projection < Min)
            Min = Projection;

        if (Projection > Max)
            Max = Projection;
    }

    return { Min, Max };
}

float CheckOverlap(sf::Vector2f V1, sf::Vector2f V2)
{
    return !(V1.x <= V2.y && V1.y >= V2.x) ? 0.0f : std::min(V1.y, V2.y) - std::max(V1.x, V2.x);
}