#include "stdpch.hpp"

#include "UI/Micro/Button.hpp"

#include "Dropdown.hpp"

/////////////// Constructor & Destructor ///////////////

Dropdown::Dropdown(
    BArgs Args,
    BColorArgs CArgs,
    std::vector<String>& I_Lists,
    std::vector<std::function<void(sf::Event*)>>* EventQueue
):
    Show(false)
{
    // Initializing Active List Button
    ActiveList = new Button({
        .Size = Args.Size,
        .Position = Args.Position,
        .Font = Args.Font,
        .CharSize = Args.CharSize,
        .Text = I_Lists[0].data()
    }, EventQueue);
    ActiveList->SetColors(CArgs);

    // Initializing each list
    for (unsh i = 0; i < I_Lists.size(); i++)
    {
        Lists.push_back(
            new Button({
                .Size = Args.Size,
                .Position = sf::Vector2f(Args.Position.x, Args.Position.y + ((i + 1) * Args.Size.y)),
                .Font = Args.Font,
                .CharSize = Args.CharSize,
                .Text = I_Lists[i].data()
            }, EventQueue)
        );
        Lists[i]->SetColors(CArgs);
        Lists[i]->SetId(i);
    }
}

Dropdown::~Dropdown()
{
    delete this->ActiveList;
    for (auto& list : Lists)
        delete list;
}

/////////////// Accessors ///////////////
const unsh& Dropdown::GetActiveId() const
{
    return ActiveList->GetId();
}

const bool& Dropdown::GetShow() const
{
    return Show;
}

/////////////// Modifiers ///////////////
void Dropdown::SetActiveText(String Text)
{
    ActiveList->SetText(Text);
}

void Dropdown::SetColors(BColorArgs Colors)
{
    // Active List
    ActiveList->SetColors(Colors);

    // Lists
    for (auto& list : Lists)
        list->SetColors(Colors);
}

void Dropdown::SetOutline(sf::Color Color, float Thickness)
{
    // Active List
    ActiveList->SetOutline(Color, Thickness);

    // Lists
    for (auto& list : Lists)
        list->SetOutline(Color, Thickness);
}

/////////////// Public Methods ///////////////
void Dropdown::OnUpdate(const sf::Vector2s& MousePosition)
{
    // ******** Updating Components ******** //
    /** Active list **/
    ActiveList->OnUpdate(MousePosition);
    ActiveList->OnClick([this]() {
        Show = !Show;
    });
    /** End **/

    /* Handling Lists once active list is clicked */
    if (Show)
        for (auto& list : Lists)
        {
            // Updating each list
            list->OnUpdate(MousePosition);

            list->OnClick([&]() {
                Show = false;
                ActiveList->SetText(list->GetText().getString());
                ActiveList->SetId(list->GetId());
            });
        }
    /** End **/
    // ******** END ******** //
}

void Dropdown::OnDraw(sf::RenderWindow* Window)
{
    ActiveList->OnDraw(Window);
    if (Show)
    {
        for (auto& list : Lists)
            list->OnDraw(Window);
    }
}