#pragma once

template <typename T>
T Randomize(T Min, T Max)
{
    return Min + (rand() % int(Max - Min + 1));
}

sf::Vector2f RandomizePosition(const sf::Vector2f& Max);