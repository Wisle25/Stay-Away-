#pragma once

sf::Vector2f VectorNormalized(sf::Vector2f Vector);

float VectorCross(const sf::Vector2f& V1, const sf::Vector2f& V2);

float VectorDot(const sf::Vector2f& V1, const sf::Vector2f& V2);
float VectorDot(const sf::Vector3f& V1, const sf::Vector3f& V2);

// Advanced Vector
sf::Vector2f Rotate(sf::Vector2f Point, sf::Vector2f Center, float Angle);