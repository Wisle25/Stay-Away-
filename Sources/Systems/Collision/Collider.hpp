#pragma once

class Collider
{
private:
    std::vector<sf::Vector2f> Vertices;
    sf::Vector2f Position;
    sf::Vector2f Origin;
    sf::Color M_Color = sf::Color::Red;

    float Rotation;

public:
    Collider();
    Collider(const std::vector<sf::Vector2f>& I_Vertices);

    sf::Vector2f GetCenter() const;
    const std::vector<sf::Vector2f>& GetVertices() const;
    const sf::Vector2f& GetPosition() const;
    const String GetInformation() const;
    const String GetData() const;

    void SetPosition(const sf::Vector2f& I_Position);
    void SetOrigin(const sf::Vector2f& I_Origin);
    void SetRotation(float Angle);
    void SetColor(sf::Color I_Color);

    void Move(sf::Vector2f Offset);
    void OnDraw(sf::RenderWindow& Window);
};