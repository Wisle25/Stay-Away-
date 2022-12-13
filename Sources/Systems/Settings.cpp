#include "stdpch.hpp"
#include "Settings.hpp"

/////////////// Constructor ///////////////
Settings::Settings()
{
    // ******** Initializing variables ******** //
    Resolution = sf::VideoMode::getDesktopMode();
    Fullscreen = true;
    VSync = false;
    FpsLimit = 144;
    CtxSettings.antialiasingLevel = 0;
    VideoModes = sf::VideoMode::getFullscreenModes();
    // ******** END ******** //
}

/////////////// Methods ///////////////
void Settings::SaveToFile(const String& path)
{
    // ********  Open the config file then write each option to file ******** //
    std::ofstream ofs_window(path);
    if (ofs_window.is_open())
    {
        ofs_window << Resolution.width << " " << Resolution.height;
        ofs_window << Fullscreen;
        ofs_window << FpsLimit;
        ofs_window << VSync;
        ofs_window << CtxSettings.antialiasingLevel;
    }
    ofs_window.close();
    // ******** END ******** //
}

void Settings::LoadFromFile(const String& path)
{
    std::ifstream ifs_window(path);
    if (ifs_window.is_open())
    {
        ifs_window >> Resolution.width >> Resolution.height;
        ifs_window >> Fullscreen;
        ifs_window >> FpsLimit;
        ifs_window >> VSync;
        ifs_window >> CtxSettings.antialiasingLevel;
    }
    ifs_window.close();
}