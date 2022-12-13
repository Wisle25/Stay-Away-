#include "stdpch.hpp"

#include "Core/Vector.hpp"
#include "UI/Converter.hpp"
#include "UI/Micro/Bar.hpp"
#include "Systems/SoundManager.hpp"

#include "Ghost.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Ghost::Ghost(EArgs Args):
    Entity(Args),
    Timer(0.f),
    Alpha(255)
{
    // *** Initializing HP Bar *** //
    HP_Bar = new Bar(
        { 40.f, 4.f },
        {
            Sprite.getPosition().x - 20.f,
            Sprite.getPosition().y - Sprite.getOrigin().y - 5.f
        }
    );
    HP_Bar->SetContentColor(sf::Color::Red);
    HP_Bar->SetContainerOutline(sf::Color::Red, 1.f);

    // *** Set Max Timer Randomly ***
    MaxTimer = 5 + rand() % (15 - 5 + 1);
    MaxScreamTimer = 14 + rand() % (30 - 14 + 1);

    // *** Sound *** //
    Sounds["SCREAM"] = new SoundManager("../Resources/sounds/enviroment/ghost_sound_3.ogg");
    Sounds["DISSAPEAR"] = new SoundManager("../Resources/sounds/enviroment/ghost_dissapear.wav");
}

Ghost::~Ghost()
{
    for (auto& Sound : Sounds)
        delete Sound.second;
}

///////////// Accessors /////////////////

const String& Ghost::GetName() const
{
    return Name;
}

const sf::Uint8& Ghost::GetOpacity() const
{
    return Alpha;
}

Body* Ghost::GetBody() const
{
    // Since only kuyang have the body, return nullptr
    return nullptr;
}

///////////// Modifiers /////////////////

void Ghost::SetCleaned(bool Value)
{

}

void Ghost::SetOpacity(float I_Alpha)
{
    Alpha -= I_Alpha;

    Sprite.setColor(sf::Color(255, 255, 255, Alpha));
}

void Ghost::SetDirection(sf::Vector2f I_Direction)
{
    Direction = I_Direction;
}

///////////// Methods /////////////////

void Ghost::AIMovement(const float& DeltaTime, const sf::Vector2f& PlayerPosition)
{
    sf::Vector2f Dir = (PlayerPosition - sf::Vector2f(0.f, 32.f)) - (Sprite.getPosition() - sf::Vector2f(0.f, 32.f));

    // If the player is close to the ghost, the ghost will be aggresive by catching the player
    if (abs(VectorLength(Dir)) < 280.f)
    {
        M_Movement->SetMaxVelocity(M_Movement->GetMaxVelocity() + 180.f);
        M_Movement->Move(Dir, DeltaTime);
    }
    else
    {
        Timer += 1.5f * DeltaTime;

        if (Timer >= MaxTimer)
        {
            sf::Vector2f R_Direction[4] = {
                { 1.f, 0.f },
                { -1.f, 0.f },
                { 0.f, 1.f },
                { 0.f, -1.f}
            };

            // Set the direction randomly
            Direction = R_Direction[0 + rand() % (3 - 0 + 1)];

            Timer = 0.f;
            MaxTimer = 3 + rand() % (5 - 3 + 1);
        }
            // Finally move the ghost
        M_Movement->SetMaxVelocity(0.f);
        M_Movement->Move(Direction, DeltaTime);
    }
}

///////////// Lifecycle /////////////////

void Ghost::OnUpdate(const float& DeltaTime, const sf::Vector2f& PlayerPosition)
{
    // Inheritance
    Entity::OnUpdate(DeltaTime);

    // Update HP Bar position so it always follow ghost's position
    HP_Bar->SetPosition({
        Sprite.getPosition().x - 20.f,
        Sprite.getPosition().y - Sprite.getOrigin().y - 5.f
    });

    // Updating HP Bar
    HP_Bar->OnUpdate(M_Attributes->HP, M_Attributes->MaxHP);

    // Keep HP more than 0
    if (M_Attributes->HP < 0.f)
        M_Attributes->HP = 0.f;

    // Updating the movement
    AIMovement(DeltaTime, PlayerPosition);

    // Sounds
    if (ScreamTimer <= MaxScreamTimer)
        ScreamTimer += 1.f * DeltaTime;
    else
    {
        Sounds["SCREAM"]->Play(DeltaTime);
        ScreamTimer = 0.f;
        MaxScreamTimer = 14 + rand() % (30 - 14 + 1);
    }

    if (M_Attributes->Dead())
        Sounds["DISSAPEAR"]->Play(DeltaTime);
}

void Ghost::OnDraw(sf::RenderWindow* Window, sf::Shader* Shader, bool ShowBox)
{
    // Inheritance
    Entity::OnDraw(Window, Shader, ShowBox);

    // Draw HP Bar
    HP_Bar->OnDraw(Window);
}

///////////////////////// Jumpscare /////////////////

Jumpscare::Jumpscare(Converter& Cvt, const String& Texture, sf::Vector2f Position):
    Timer(0.f),
    MaxTimer(3.5f)
{
    M_Animation = new Animation(M_Jumpscare, Texture, 27.f, 64);

    M_Jumpscare.setScale({ 13.f, 13.f });
    M_Jumpscare.setOrigin(
        M_Jumpscare.getGlobalBounds().left + M_Jumpscare.getGlobalBounds().width / 2.f,
        M_Jumpscare.getGlobalBounds().top + M_Jumpscare.getGlobalBounds().height / 2.f
    );
    M_Jumpscare.setPosition(Position);

    // Text
    TextTexture.loadFromFile("../Resources/Sprites/Jumpscare/red_1.png");
    Text.setTexture(TextTexture);
    Text.setOrigin(
        Text.getGlobalBounds().left + Text.getGlobalBounds().width / 2.f,
        Text.getGlobalBounds().top + Text.getGlobalBounds().height / 2.f
    );
    Text.setPosition({ Cvt.P2PX(50.f), Cvt.P2PY(16.f)});

    // Sound
    S_Jumpscare = new SoundManager("../Resources/sounds/enviroment/jumpscare.wav");
}

Jumpscare::~Jumpscare()
{
    delete M_Animation;
    delete S_Jumpscare;
}

bool Jumpscare::OnUpdate(const float& DeltaTime)
{
    M_Animation->OnUpdate(DeltaTime);
    S_Jumpscare->Play(DeltaTime, false);

    if (Timer <= MaxTimer)
    {
        Timer += 1.f * DeltaTime;
        return false;
    }

    return true;
}

void Jumpscare::OnDraw(sf::RenderWindow* Window)
{
    Window->draw(M_Jumpscare);
    Window->draw(Text);
}