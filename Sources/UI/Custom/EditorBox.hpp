#pragma once

class Checklist;
class TextField;

class EditorBox
{
public:
    /////////////////////////////
    // Constructor & Destructor
    /////////////////////////////
    EditorBox(std::vector<std::function<void(sf::Event*)>>* EventQueue);
    virtual ~EditorBox();

    //////////////////////////////
    // Lifecycle
    //////////////////////////////
    void OnUpdate(const float& DeltaTime);
    void OnDraw(sf::RenderWindow* Window);

private:
    //////////////////////////////
    // SF Components
    //////////////////////////////
    sf::RectangleShape Container;

    //////////////////////////////
    // Value to be added
    //////////////////////////////
    std::map<sf::Text, Checklist*> ChecklistVariable;
    std::map<sf::Text, TextField*> TextVariable;
};