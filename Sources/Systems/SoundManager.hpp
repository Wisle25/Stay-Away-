#pragma once

class SoundManager
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    SoundManager(const String& Path);
    virtual ~SoundManager();

    void Reset();
    void SetPlayingOffset(float Offset);
    void Play(const float DeltaTime);

private:
    /////////////////////////////
    // SFML Components
    /////////////////////////////
    sf::Sound Sound;
    sf::SoundBuffer Buffer;

    bool Played;

    float Timer;
};