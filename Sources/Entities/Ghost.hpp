#pragma once

#include "Player.hpp"

class Bar;
class Body;
class SoundManager;
struct Converter;

class Ghost : public Entity
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    Ghost(EArgs Args);
    virtual ~Ghost();

    //////////////////////////////
    // Accessors
    //////////////////////////////
    const String& GetName() const;
    const sf::Uint8& GetOpacity() const;

    virtual Body* GetBody() const;

    //////////////////////////////
    // Modifiers
    //////////////////////////////
    virtual void SetCleaned(bool Value);
    void SetOpacity(float I_Alpha);
    void SetDirection(sf::Vector2f I_Direction);

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    virtual void OnUpdate(const float& DeltaTime, const sf::Vector2f& PlayerPosition);
    virtual void OnDraw(sf::RenderWindow* Window, sf::Shader* Shader, bool ShowBox);

protected:
    /////////////////////////////
    // Custom Components
    /////////////////////////////
    Bar* HP_Bar;
    std::map<String, SoundManager*> Sounds;

    String Name;
    sf::Uint8 Alpha;

    //////////////////////////////
    // Timer to change direction for AI Movement and screaming sound
    //////////////////////////////
    float Timer;
    float MaxTimer;

    float ScreamTimer;
    float MaxScreamTimer;

    //////////////////////////////
    // Private Methods
    //////////////////////////////
    void AIMovement(const float& DeltaTime, const sf::Vector2f& PlayerPosition);
};

class Jumpscare
{
public:
    /////////////////////////////
    // Constructor
    /////////////////////////////
    Jumpscare(Converter& Cvt, const String& Texture, sf::Vector2f Position);
    ~Jumpscare();

    /////////////////////////////
    // Lifecycle
    /////////////////////////////
    bool OnUpdate(const float& DeltaTime);
    void OnDraw(sf::RenderWindow* Window);

private:
    /////////////////////////////
    // Jumpscare
    /////////////////////////////
    sf::Sprite M_Jumpscare;
    sf::Sprite Text;
    sf::Texture TextTexture;

    SoundManager* S_Jumpscare;

    Animation* M_Animation;

    float Timer;
    float MaxTimer;
};