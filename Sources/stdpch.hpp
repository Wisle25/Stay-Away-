#pragma once

// Standard Library
#include <algorithm>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <stack>
#include <sstream>
#include <vector>

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

typedef unsigned short unsh;
namespace fs = std::filesystem;
using String = std::string;

namespace sf
{
typedef sf::Vector2<short> Vector2s;
}