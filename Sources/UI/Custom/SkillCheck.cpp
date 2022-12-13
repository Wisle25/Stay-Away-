#include "stdpch.hpp"
#include "UI/Converter.hpp"
#include "SkillCheck.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
SkillCheck::SkillCheck(Converter& Cvt, sf::Font& Font):
    Direction({ 1.f, 0.f }),
    Count(0)
{
    // *** Initializing Container *** //
    Container.setSize({ Cvt.P2PX(15.f), Cvt.P2PY(1.6f)});
    Container.setOrigin(
        Container.getGlobalBounds().left + Container.getGlobalBounds().width / 2.f,
        Container.getGlobalBounds().top + Container.getGlobalBounds().height / 2.f
    );
    Container.setFillColor(sf::Color::Transparent);
    Container.setOutlineColor(sf::Color(194, 16, 16));
    Container.setOutlineThickness(2.f);
    Container.setPosition({ Cvt.P2PX(50.f), Cvt.P2PY(47.8f) });

    // *** Initializing Skill *** //
    Skill.setSize({ Cvt.P2PX(1.8f), Cvt.P2PY(1.6f)});
    Skill.setFillColor(sf::Color::White);
    Skill.setPosition({
        // Randomize X Position
        RandomizePosition(Container.getPosition().x - Container.getOrigin().x, Container.getPosition().x + Container.getOrigin().x - Skill.getSize().y / 2.f),
        // Y Position
        Cvt.P2PY(47.41f) - Container.getOrigin().y / 2.f
    });

    // *** Initializing Line Check *** //
    LineCheck.setSize({ Cvt.P2PX(0.3f), Cvt.P2PY(4.f) });
    LineCheck.setFillColor(sf::Color(199, 10, 128));
    LineCheck.setPosition({ Cvt.P2PX(50.f) - Container.getOrigin().x, Cvt.P2PY(45.8f)});

    // *** Initializing Text *** //
    Text.setFont(Font);
    Text.setCharacterSize(Cvt.P2PChar(190));
    Text.setFillColor(sf::Color::White);
    Text.setString("Skill Check!");
    Text.setOrigin(
        Text.getGlobalBounds().left + Text.getGlobalBounds().width / 2.f,
        Text.getGlobalBounds().top + Text.getGlobalBounds().height / 2.f
    );
    Text.setPosition(Cvt.P2PX(50.f), Cvt.P2PY(51.7f));
}

SkillCheck::~SkillCheck()
{

}

///////////// Accessors /////////////

const bool SkillCheck::IsSuccess() const
{
    if (LineCheck.getPosition().x >= Skill.getPosition().x                     &&
        LineCheck.getPosition().x <= Skill.getPosition().x + Skill.getSize().x
    )
        return true;

    return false;
}

const unsh& SkillCheck::GetCount() const
{
    return Count;
}

///////////// Modifiers /////////////

void SkillCheck::ResetCount()
{
    Count = 0;
}

void SkillCheck::SetNewSkill()
{
    Skill.setPosition({
        // Randomize X Position
        RandomizePosition(Container.getPosition().x - Container.getOrigin().x, Container.getPosition().x + Container.getOrigin().x - Skill.getSize().y / 2.f),
        // Y Position
        Skill.getPosition().y
    });
}

///////////// Lifecycle /////////////////

// \brief Called every frame, apply game logic here
void SkillCheck::OnUpdate(const float& DeltaTime)
{
    float Velocity = 400.f;

    LineCheck.move(Direction * Velocity * DeltaTime);

    if (LineCheck.getPosition().x >= Container.getPosition().x + Container.getOrigin().x ||
        LineCheck.getPosition().x <= Container.getPosition().x - Container.getOrigin().x
    )
    {
        Direction.x = -Direction.x;
        Count++;
    }
}

// \brief Draw SF drawable components to screen
void SkillCheck::OnDraw(sf::RenderWindow* Window)
{
    Window->draw(Text);
    Window->draw(Container);
    Window->draw(Skill);
    Window->draw(LineCheck);
}

///////////// Private Methods /////////////////

float SkillCheck::RandomizePosition(float Min, float Max)
{
    return Min + (rand() % int(Max - Min + 1));
}