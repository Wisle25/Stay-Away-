#pragma once

class Collider;

bool Collision(const Collider* ColliderA, const Collider* ColliderB, sf::Vector2f& MTV);

sf::Vector2f Perpendicular(std::vector<sf::Vector2f>& Vertices, short Index, short Count);
sf::Vector2f ProjectOnto(std::vector<sf::Vector2f>& Vertices, short Count, sf::Vector2f Axis);

float CheckOverlap(sf::Vector2f V1, sf::Vector2f V2);