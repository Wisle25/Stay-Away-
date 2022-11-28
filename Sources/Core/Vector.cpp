#include "stdpch.hpp"
#include "Vector.hpp"

sf::Vector2f Normalized(sf::Vector2f& Vector)
{
    float Normalize = std::sqrt(powf(Vector.x, 2) + powf(Vector.y, 2));

    return Vector / Normalize;
}