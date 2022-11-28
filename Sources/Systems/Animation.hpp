#pragma once

class Animation
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Animation(sf::Sprite& I_Sprite, std::string Directory, const float I_Speed, const unsh I_Width);
    virtual ~Animation();

    /////////////////////////////
    // Accessors
    /////////////////////////////
    const bool IsFinished() const;

    /////////////////////////////
    // Modifiers
    /////////////////////////////
    void SetFlipped(const bool I_Flipped);
    void Reset();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnUpdate(const float& DeltaTime);

private:
    /////////////////////////////
    // SF Components
    /////////////////////////////
    sf::Sprite& Sprite;
    sf::Texture TextureSheet;

    /////////////////////////////
    // Timer
    /////////////////////////////
    float Timer;
    float Speed;

    /////////////////////////////
    // Sheet Info
    /////////////////////////////
    unsh CurrentFrame;
    unsh Width;
    unsh TotalFrames;

    bool Flipped;
};