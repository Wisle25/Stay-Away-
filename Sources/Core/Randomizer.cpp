#include "stdpch.hpp"
#include "Randomizer.hpp"

sf::Vector2f RandomizePosition(const sf::Vector2f& Max)
{
    return sf::Vector2f
    (
        rand() % int(Max.x + 1),
        rand() % int(Max.y + 1)
    );
}
