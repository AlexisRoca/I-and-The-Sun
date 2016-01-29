#pragma once

#include <SFML/Graphics.hpp>

class INEventHandler
{
    public:
        virtual void react(sf::Event const& event) = 0;
};
