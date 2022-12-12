#include "stdpch.hpp"
#include "SoundManager.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
SoundManager::SoundManager(const String& Path):
    Played(false)
{
    Buffer.loadFromFile(Path);
    Sound.setBuffer(Buffer);
}

SoundManager::~SoundManager()
{

}

void SoundManager::Reset()
{
    Played = false;
    Timer = 0.f;
    Sound.stop();
}

void SoundManager::SetPlayingOffset(float Offset)
{
    Sound.setPlayingOffset(sf::seconds(Offset));
}

void SoundManager::Play(const float DeltaTime)
{
    if (!Played)
    {
        Sound.play();
        Played = true;
    }

    if (Timer <= Buffer.getDuration().asSeconds())
        Timer += 1.f * DeltaTime;
    else
        Reset();
}

///////////// Lifecycle /////////////////
