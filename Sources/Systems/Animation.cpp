#include "stdpch.hpp"
#include "Animation.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Animation::Animation(sf::Sprite& I_Sprite, const String& Directory, float I_Speed, unsh I_Width):
    Sprite(I_Sprite),
    Timer(0),
    Speed(I_Speed),
    CurrentFrame(0),
    Width(I_Width)
{
    // Applying Texture
    TextureSheet.loadFromFile(Directory);
    TotalFrames = TextureSheet.getSize().x / Width;
}

Animation::~Animation()
{
}

///////////////// Accessors /////////////////

const bool Animation::IsFinished() const
{
    return CurrentFrame == TotalFrames;
}

///////////////// Modifiers /////////////////

// \brief Set the texture sheet is flipped or not
void Animation::SetFlipped(const bool I_Flipped)
{
    Flipped = I_Flipped;
}

// \brief Reset the animation to default one
void Animation::Reset()
{
    CurrentFrame = 0;
}

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void Animation::OnUpdate(const float& DeltaTime)
{
    Timer += 100.f * DeltaTime;

    // Reset the timer once it's finished
    while (Timer >= Speed)
    {
        Timer = 0.f;
        CurrentFrame = (CurrentFrame + 1) % TotalFrames;
    }

    // Animating
    Sprite.setTexture(TextureSheet);

    // Check for the flipped or not
    if (!Flipped)
        Sprite.setTextureRect(sf::IntRect(CurrentFrame * Width, 0, Width, TextureSheet.getSize().y /* Height of the texture */));
    else
        Sprite.setTextureRect(sf::IntRect((CurrentFrame + 1) * Width, 0, -Width, TextureSheet.getSize().y /* Height of the texture */));
}

void Animation::OnUpdate(const float& DeltaTime, float Modifier)
{
    Timer += Modifier * 100.f * DeltaTime;

    // Reset the timer once it's finished
    while (Timer >= Speed)
    {
        Timer = 0.f;
        CurrentFrame = (CurrentFrame + 1) % TotalFrames;
    }

    // Animating
    Sprite.setTexture(TextureSheet);

    // Check for the flipped or not
    if (!Flipped)
        Sprite.setTextureRect(sf::IntRect(CurrentFrame * Width, 0, Width, TextureSheet.getSize().y /* Height of the texture */));
    else
        Sprite.setTextureRect(sf::IntRect((CurrentFrame + 1) * Width, 0, -Width, TextureSheet.getSize().y /* Height of the texture */));
}