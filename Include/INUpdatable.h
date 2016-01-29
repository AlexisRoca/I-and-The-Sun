#pragma once

#include <SFML/Graphics.hpp>

class INUpdatable
{
    public:
		virtual void update(sf::Clock const & clk) = 0;
};
