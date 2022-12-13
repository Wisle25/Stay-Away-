#pragma once

// Standard Library
#include <cmath>
#include <fstream>
#include <filesystem>
#include <functional>
#include <map>
#include <random>
#include <stack>
#include <sstream>
#include <vector>

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Alias
typedef unsigned short unsh;
namespace fs = std::filesystem;
using String = std::string;

// Create Vector with type Short
namespace sf
{
typedef sf::Vector2<short> Vector2s;
}
