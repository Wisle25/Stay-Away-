#include "stdpch.hpp"
#include "Vector.hpp"

sf::Vector2f Normalized(sf::Vector2f Vector)
{
    float Normalize = sqrtf(powf(Vector.x, 2) + powf(Vector.y, 2));

    return Vector / Normalize;
}

float VectorCross(const sf::Vector2f& V1, const sf::Vector2f& V2)
{
    return V1.x * V2.y - V1.y * V2.x;
}

float VectorDot(const sf::Vector2f& V1, const sf::Vector2f& V2)
{
    return V1.x * V2.x + V1.y * V2.y;
}

float VectorDot(const sf::Vector3f& V1, const sf::Vector3f& V2)
{
    return V1.x * V2.x + V1.y * V2.y + V1.z * V2.z;
}