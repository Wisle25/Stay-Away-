#include "stdpch.hpp"

#include "Collectable/Collectable.hpp"
#include "UI/Micro/Bar.hpp"

#include "Inventory.hpp"

///////////// Constructor & Destructor /////////////////

// \brief Called once when at the first start
Inventory::Inventory(float Size, sf::Vector2f Position, sf::Font& Font, std::vector<std::function<void(sf::Event*)>>* EventQueue):
    ContainerSize(Size),
    Now(1)
{
    InitializeContainer(Position, Font);
    InitializeSelector();

    // Enqueue On Input methods to Event Queue
    EventQueue->push_back(std::bind(&OnInput, this, std::placeholders::_1));
}

Inventory::~Inventory()
{
    for (auto& Amount : Items)
    {
        for (auto& Item : Amount)
            delete Item;
        Amount.clear();
    }
    Items.clear();

    for (auto& Bar : AmountBars)
        delete Bar;
}

void Inventory::AddItem(std::vector<Collectable*> I_Items)
{
    // If the slot is not full, we can add the item to inventory
    if (Items.size() + 1 < ItemContainers.size())
    {
        unsh Size = Items.size();
        Items.push_back(I_Items);

        for (unsh i = 0; i < I_Items.size(); ++i)
        {
            Items[Size][i]->SetPosition(ItemContainers[Size].getPosition());
            Items[Size][i]->SetScale({ 1.4f, 1.4f });
            Items[Size][i]->SetRotation(-45);
        }
    }
}

void Inventory::UseItem(const sf::Vector2f& Position, const sf::Vector2f& I_Direction)
{
    // If there are no any items, then do nothing
    if (Now > Items.size())
        return;

    unsh Amount = Items[Now - 1].size() - 1;
    auto& Item = Items[Now - 1][Amount];

    Item->UseItem(Position, I_Direction);

    // Finally we can store it on stack
    UsedItem.push_back(Item);

    // Will remove the item if its removable
    if (Item->IsRemovable())
        Items[Now - 1].pop_back();
}

///////////// Private Methods (Initializer) /////////////

void Inventory::InitializeContainer(sf::Vector2f Position, sf::Font& Font)
{
    // Default slot for inventory is 6
    for (unsh i = 0; i < 6; ++i)
    {
        // *** Initializing Containers *** //
        ItemContainers.push_back(sf::RectangleShape());
        ItemContainers[i].setFillColor(sf::Color::Transparent);
        ItemContainers[i].setOutlineColor(sf::Color(245, 235, 224));
        ItemContainers[i].setOutlineThickness(-7.f);
        ItemContainers[i].setSize({ ContainerSize, ContainerSize });
        ItemContainers[i].setOrigin({ ContainerSize / 2.f, ContainerSize / 2.f });
        ItemContainers[i].setPosition({ Position.x + i * (ContainerSize - 5.f), Position.y });

        // *** Initializing Amount Bars *** //
        AmountBars.push_back(new Bar({
            .Size = { ContainerSize * 0.72f, ContainerSize * 0.13f },
            .Position = {
                ItemContainers[i].getPosition().x - (ContainerSize * 0.72f) / 2.f,
                ItemContainers[i].getPosition().y + 20.f
            },
            .Font = Font,
            .CharSize = 10
        }));
        AmountBars[i]->SetContentColor(sf::Color::Green);
        AmountBars[i]->SetContainerOutline(sf::Color::Blue, 2.f);
        AmountBars[i]->OnUpdate(0, 15, "");
    }
}

void Inventory::InitializeSelector()
{
    Selector.setFillColor(sf::Color::Transparent);
    Selector.setOutlineColor(sf::Color::Blue);
    Selector.setOutlineThickness(-5.f);
    Selector.setSize({ ContainerSize, ContainerSize });
    Selector.setOrigin({ ContainerSize / 2.f, ContainerSize / 2.f });
    Selector.setPosition(ItemContainers[0].getPosition());
}

///////////// Lifecycle /////////////////

// \brief Handling input
void Inventory::OnInput(sf::Event* Event)
{
    if (Event->type == sf::Event::MouseWheelScrolled)
    {
        if (Event->mouseWheelScroll.delta > 0)
        {
            if (Now++ >= ItemContainers.size())
                Now = 1;
            Selector.setPosition(ItemContainers[Now - 1].getPosition());
        }
        else if (Event->mouseWheelScroll.delta < 0)
        {
            if (Now-- <= 1)
                Now = ItemContainers.size();
            Selector.setPosition(ItemContainers[Now - 1].getPosition());
        }
    }

    if (Event->type == sf::Event::KeyPressed)
    {
        // The reason why i divide it by 26 is coz the key code
        // for number "1" (below F1) is 27, So i decide to divide it by 26 to make it really "1"
        unsh KeyCode = Event->key.code - 26;
        if (KeyCode >= 1 && KeyCode <= 6)
            Now = KeyCode;

        Selector.setPosition(ItemContainers[Now - 1].getPosition());
    }
}

// \brief Called every frame, apply game logic here
void Inventory::OnUpdate(const float& DeltaTime, const sf::Vector2i& GridPosition, float GridSize)
{
    // Automatically drop the item once the amount is 0
    for (unsh i = 0; i < Items.size(); ++i)
    {
        if (Items[i].size() <= 0 || Items[i][0]->GetAmount() <= 0)
            Items.erase(Items.begin() + i);

        AmountBars[i]->OnUpdate(
            (Items[i][0]->IsRemovable()) ? Items[i].size() : Items[i][0]->GetAmount(),
            Items[i][0]->GetMaxAmount(),
            ""
        );
    }

    for (unsh i = 0; i < UsedItem.size(); ++i)
    {
        // Update used item
        UsedItem[i]->OnUpdate(DeltaTime);

        // We will delete the UsedItem[i] once it's out of screen
        float Min_X = float(GridPosition.x - 15) * GridSize;
        float Max_X = float(GridPosition.x + 15) * GridSize;
        float Min_Y = float(GridPosition.y - 9) * GridSize;
        float Max_Y = float(GridPosition.y + 10) * GridSize;

        if (UsedItem[i]->GetPosition().x <= Min_X || UsedItem[i]->GetPosition().x >= Max_X ||
            UsedItem[i]->GetPosition().y <= Min_Y || UsedItem[i]->GetPosition().y >= Max_Y
        )
        {
            delete UsedItem[i];
            UsedItem.erase(UsedItem.begin() + i);
        }
    }
}

// \brief Draw SF drawable components to screen
void Inventory::OnDraw(sf::RenderWindow* Window)
{
    for (auto& Container : ItemContainers)
        Window->draw(Container);

    for (unsh i = 0; i < Items.size(); ++i)
    {
        if (Items[i][0] != nullptr)
            Items[i][0]->OnDraw(Window);
    }

    for (auto& Item : UsedItem)
        Item->OnDraw(Window);

    for (auto& Bar : AmountBars)
        Bar->OnDraw(Window);

    Window->draw(Selector);
}