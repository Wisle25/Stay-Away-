#include "stdpch.hpp"
#include "Core/Vector.hpp"
#include "Movement.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Movement::Movement(sf::Sprite& I_Sprite, float I_MaxVelocity, float I_Acceleration, float I_Deceleration):
    Sprite(I_Sprite),
    MaxVelocity(I_MaxVelocity),
    Acceleration(I_Acceleration),
    Deceleration(I_Deceleration)
{
    Velocity = sf::Vector2f(0, 0);
}

Movement::~Movement()
{

}

///////////// Accessors /////////////////

// \brief Get the current velocity of the sprite
const sf::Vector2f& Movement::GetVelocity() const
{
    return Velocity;
}

const float& Movement::GetMaxVelocity() const
{
    return MaxVelocity;
}

///////////// Modifiers /////////////////

// \brief Set the velocity of the sprite
void Movement::SetVelocity(sf::Vector2f I_Velocity)
{
    Velocity = I_Velocity;
}

void Movement::Move(sf::Vector2f Direction, const float& DeltaTime)
{
    Velocity += Acceleration * VectorNormalized(Direction) * DeltaTime;
}

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void Movement::OnUpdate(const float& DeltaTime)
{
    // *** Decelerating velocity and limit the velocity to it's maximum *** //
    /* Horizontal Directions */
	if (Velocity.x > 0.f)
	{
		// Max Velocity
		if (Velocity.x > MaxVelocity)
			Velocity.x = MaxVelocity;

		// Deceleration
		Velocity.x -= Deceleration * DeltaTime;
		if (Velocity.x < 0.f)
			Velocity.x = 0.f;
	}
	else if(Velocity.x < 0.f)
	{
		// Max Velocity
		if (Velocity.x < -MaxVelocity)
			Velocity.x = -MaxVelocity;

		// Deceleration
		Velocity.x += Deceleration * DeltaTime;
		if (Velocity.x > 0.f)
			Velocity.x = 0.f;
	}

    /* Vertical Directions */
	if (Velocity.y > 0.f)
	{
		// Max Velocity
		if (Velocity.y > MaxVelocity)
			Velocity.y = MaxVelocity;

		// Deceleration
		Velocity.y -= Deceleration * DeltaTime;
		if (Velocity.y < 0.f)
			Velocity.y = 0.f;
	}
	else if (Velocity.y < 0.f)
	{
		// Max Velocity
		if (Velocity.y < -MaxVelocity)
			Velocity.y = -MaxVelocity;

		// Deceleration
		Velocity.y += Deceleration * DeltaTime;
		if (Velocity.y > 0.f)
			Velocity.y = 0.f;
	}

    Sprite.move(Velocity * DeltaTime);
}