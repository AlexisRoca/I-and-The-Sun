#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

float scalar(sf::Vector2f a, sf::Vector2f b);
float norm(sf::Vector2f v);
float normSquare(sf::Vector2f v);

template <typename T>
T min(T const& a, T const& b)
{
    return (a < b)? a : b;
}

template <typename T>
T max(T const& a, T const& b)
{
    return (a > b)? a : b;
}
