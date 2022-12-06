#include "stdpch.hpp"
#include "Converter.hpp"

/**
 * @brief Convert percentage of the value to pixel relative of current resolution in X-Axis
 *
 * @param percent
 * @return const float
 */
const float Converter::P2PX(const float Percent)
{
    return std::floor(static_cast<float>(VirtualMachine.width) * (Percent / 100.f));
}

/**
 * @brief Convert Percentage of the value to pixel relative of current resolution in Y-Axis
 *
 * @param Percent
 * @return const float
 */
const float Converter::P2PY(const float Percent)
{
    return std::floor(static_cast<float>(VirtualMachine.height) * (Percent / 100.f));
}

/**
 * @brief Calculates the character size for text using the current resolution and a constant.
 *
 * @param modifier
 * @return const short
 */
const unsh Converter::P2PChar(const unsh Modifier)
{
    return static_cast<unsh>((VirtualMachine.width + VirtualMachine.height) / Modifier);
}