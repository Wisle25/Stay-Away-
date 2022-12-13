#pragma once

struct Converter;

class SkillCheck
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    SkillCheck(Converter& Cvt, sf::Font& Font);
    virtual ~SkillCheck();

    //////////////////////////////
    // Accessors
    //////////////////////////////
    const bool IsSuccess() const;
    const unsh& GetCount() const;

    //////////////////////////////
    // Modifiers
    //////////////////////////////
    void ResetCount();
    void SetNewSkill();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnUpdate(const float& DeltaTime);
    void OnDraw(sf::RenderWindow* Window);

private:
    //////////////////////////////
    // SFML Components
    //////////////////////////////
    sf::RectangleShape Container;
    sf::RectangleShape Skill;
    sf::RectangleShape LineCheck;

    sf::Text Text;
    sf::Vector2f Direction;

    unsh Count;

    //////////////////////////////
    // Methods
    //////////////////////////////
    float RandomizePosition(float Min, float Max);
};