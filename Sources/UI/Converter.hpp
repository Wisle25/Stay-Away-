#pragma once

struct Converter
{
    sf::VideoMode& VirtualMachine;
    Converter(sf::VideoMode& i_VirtualMachine):
        VirtualMachine(i_VirtualMachine)
    {
    }

    const float P2PX(const float Percent);
    const float P2PY(const float Percent);
    const unsh P2PChar(const unsh Modifier);

    // Converting Methods
};