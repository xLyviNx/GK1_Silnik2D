#include "Calculations.h"
#include <cmath>
sf::Vector2f Engine2D::Calculations::Vector2f_Normalize(sf::Vector2f Vector)
{
    float magnitude = Vector2f_Magnitude(Vector);
    if (magnitude != 0)
    {
        return sf::Vector2f(Vector.x / magnitude, Vector.y / magnitude);
    }
    else {
        return Vector;
    }
}

float Engine2D::Calculations::Vector2f_Magnitude(sf::Vector2f Vector)
{
    return std::sqrt((Vector.x * Vector.x) + (Vector.y * Vector.y));
}
