#pragma once

class Movement
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Movement(sf::Sprite& I_Sprite, float I_MaxVelocity, float I_Acceleration, float I_Deceleration);
    virtual ~Movement();

    /////////////////////////////
    // Accessors
    /////////////////////////////
    const sf::Vector2f& GetVelocity() const;
    const float& GetMaxVelocity() const;

    /////////////////////////////
    // Modifiers
    /////////////////////////////
    void SetVelocity(sf::Vector2f I_Velocity = sf::Vector2f(0, 0) /* Default behavior is reseting velocity */);

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void Move(sf::Vector2f Direction, const float& DeltaTime);
    void OnUpdate(const float& DeltaTime);

private:
    /////////////////////////////
    // SF Components
    /////////////////////////////
    sf::Sprite& Sprite;
    sf::Vector2f Velocity;

    /////////////////////////////
    // To adjust the movement
    /////////////////////////////
    float MaxVelocity;
    float Acceleration;
    float Deceleration;
};