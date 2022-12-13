#include "stdpch.hpp"
#include "Vector.hpp"

sf::Vector2f VectorNormalized(sf::Vector2f Vector)
{
    float Length = VectorLength(Vector);

    return Length ? Vector / Length : sf::Vector2f();
}

float VectorLength(sf::Vector2f Vector)
{
    return sqrtf(Vector.x * Vector.x + Vector.y * Vector.y);
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

sf::Vector2f Rotate(sf::Vector2f Point, sf::Vector2f Center, float Angle)
{
    float Radian = Angle * 3.14159f / 180.f;

    return
    {
		cosf(Radian) * (Point.x - Center.x) - sinf(Radian) * (Point.y - Center.y) + Center.x,
		sinf(Radian) * (Point.x - Center.x) + cosf(Radian) * (Point.y - Center.y) + Center.y
    };
}