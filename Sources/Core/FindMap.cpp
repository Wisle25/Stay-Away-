#include "stdpch.hpp"
#include "FindMap.hpp"

template<typename T>
std::map<String, T> FindMap(std::map<String, T>& I_Map, const String key)
{
    std::map<String, T> Result;

    for (auto& Value : I_Map)
    {
        if (Value.first.find(key) != String::npos)
            Result.insert({ Value.first, Value.second });
    }

    return Result;
}
