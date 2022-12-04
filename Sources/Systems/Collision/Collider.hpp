#pragma once

class Collider
{
private:
    std::vector<sf::Vector2f> Vertices;
    sf::Vector2f Position;

public:
    Collider();
    Collider(std::vector<sf::Vector2f>& I_Vertices);

    sf::Vector2f GetCenter() const;
    const std::vector<sf::Vector2f>& GetVertices() const;
    const sf::Vector2f& GetPosition() const;
    const std::string GetInformation() const;
    const std::string GetData() const;

    void SetPosition(const sf::Vector2f& I_Position);

    void Move(sf::Vector2f Offset);
    void OnDraw(sf::RenderWindow& Window);
};