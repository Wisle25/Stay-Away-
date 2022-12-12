#include "stdpch.hpp"

#include "UI/Converter.hpp"
#include "UI/Custom/SkillCheck.hpp"
#include "UI/Micro/Bar.hpp"
#include "Systems/SoundManager.hpp"

#include "SkillChecks.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
SkillChecks::SkillChecks(Converter& Cvt, sf::Font& Font, const String& Texture, sf::Vector2f Scale, sf::Vector2f Position):
    Interactable(Texture, Scale, Position),
    Progress(0.f),
    MaxProgress(100.f),
    SkillCheckTimer(0.f),
    DrawSkillCheck(false),
    OnProgress(false)
{
    // Randomize the max timer for skill check, the range is 5 to 10 seconds(?)
    SkillCheckTimerMax = 5 + (rand() % (10 - 5 + 1));

    // Initializing Progress Bar
    ProgressBar = new Bar(
        { Cvt.P2PX(8.f), Cvt.P2PX(0.7f) },
        { Position.x - M_Texture.getSize().x * 2.f, Position.y - M_Texture.getSize().y * 1.12f }
    );
    ProgressBar->SetContentColor(sf::Color::Green);
    ProgressBar->SetContainerOutline(sf::Color::White, 1.5f);

    M_SkillCheck = new SkillCheck(Cvt, Font);

    // Sound
    Sounds["WARN"] = new SoundManager("../Resources/sounds/enviroment/skill_check.ogg");
    Sounds["FAIL"] = new SoundManager("../Resources/sounds/enviroment/ghost_laugh.ogg");
    Sounds["BLOOD_SPLASH"] = new SoundManager("../Resources/sounds/enviroment/knife_stab_effect.ogg");
    Sounds["BLOOD_SPLASH"]->SetPlayingOffset(1.f);
}

SkillChecks::~SkillChecks()
{
    delete ProgressBar;
    delete M_SkillCheck;

    for (auto& Sound : Sounds)
        delete Sound.second;
}

const bool SkillChecks::IsCompleted() const
{
    return Progress >= MaxProgress;
}

void SkillChecks::SetOnProgress(bool I_Value)
{
    OnProgress = I_Value;
}

///////////// Private Methods /////////////

void SkillChecks::Reset()
{
    DrawSkillCheck = false;

    // Reset skill check timer also get a new max timer by rand()
    SkillCheckTimer = 0.f;
    SkillCheckTimerMax = 5 + (rand() % (10 - 5 + 1));

    M_SkillCheck->ResetCount();
    M_SkillCheck->SetNewSkill();

    Sounds["WARN"]->Reset();
}

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void SkillChecks::OnUpdate(const float& DeltaTime)
{
    // Updating skill check timer then reset it back if it's reached the max
    SkillCheckTimer += 2.f * DeltaTime;
    Progress += std::clamp(7.f * DeltaTime, 0.f, 100.f);

    // Play warn sfx
    if (SkillCheckTimerMax - SkillCheckTimer <= 1.5f)
        Sounds["WARN"]->Play(DeltaTime);

    // Getting Input, If Space is pressed we will check the skill then reset skill check
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && DrawSkillCheck)
    {
        DrawSkillCheck = false;

        // If the player successed the skill check, increase the progress by 10
        if (M_SkillCheck->IsSuccess())
            Progress += 10.f;
        else
        {
            Progress -= 15.f;
            Sounds["FAIL"]->Play(DeltaTime);
            Sounds["BLOOD_SPLASH"]->Play(DeltaTime);
        }

        Reset();
    }

    ProgressBar->OnUpdate(Progress, MaxProgress);

    if (SkillCheckTimer >= SkillCheckTimerMax)
    {
        DrawSkillCheck = true;
        M_SkillCheck->OnUpdate(DeltaTime);

        // If it's 3 times, it means the player failed the skill check
        if (M_SkillCheck->GetCount() >= 3)
        {
            // Progress is decreased then reset the skill check
            Progress -= 15.f;
            Sounds["FAIL"]->Play(DeltaTime);
            Sounds["BLOOD_SPLASH"]->Play(DeltaTime);
            Reset();
        }
    }
}

// \brief Draw SF drawable components to screen
void SkillChecks::OnDraw(sf::RenderWindow* Window, bool I_OnProgress)
{
    // Inheritance
    Interactable::OnDraw(Window);

    if (OnProgress || I_OnProgress)
    {
        if (DrawSkillCheck) M_SkillCheck->OnDraw(Window);
        ProgressBar->OnDraw(Window);
    }
}