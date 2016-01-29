#include "Vector2fOperations.h"

float scalar(sf::Vector2f a, sf::Vector2f b)
{
    return a.x * b.x + a.y * b.y;
}

float norm(sf::Vector2f v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

float normSquare(sf::Vector2f v)
{
    return v.x * v.x + v.y * v.y;
}
