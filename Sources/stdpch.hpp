#pragma once

// Standard Library
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <functional>
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <sstream>
#include <vector>

// SFML
#include <SFML/Graphics.hpp>

typedef unsigned short unsh;
namespace fs = std::filesystem;

namespace sf
{
typedef sf::Vector2<short> Vector2s;
}

// CUSTOM LIBRARY
struct Cvt
{
    sf::VideoMode& VirtualMachine;
    Cvt(sf::VideoMode& i_VirtualMachine):
        VirtualMachine(i_VirtualMachine)
    {
    }

    const float P2pX(const float Percent);
    const float P2pY(const float Percent);
    const short P2pChar(const short Modifier);
};