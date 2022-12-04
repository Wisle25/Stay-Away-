#include "stdpch.hpp"
#include "FindMap.hpp"

template<typename T>
std::map<std::string, T> FindMap(std::map<std::string, T>& I_Map, const std::string key)
{
    std::map<std::string, T> Result;

    for (auto& Value : I_Map)
    {
        if (Value.first.find(key) != std::string::npos)
            Result.insert({ Value.first, Value.second });
    }

    return Result;
}
