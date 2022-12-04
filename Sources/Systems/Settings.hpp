#pragma once

class Settings
{
public:
    // Variables
    sf::VideoMode Resolution;
    sf::ContextSettings CtxSettings;
    std::vector<sf::VideoMode> VideoModes;

    bool Fullscreen, VSync;
    unsh FpsLimit;

    // Constructor
    Settings();

    // Methods
    void SaveToFile(const std::string Path);
    void LoadFromFile(const std::string Path);
};