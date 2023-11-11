#pragma once
#include "SFML/Graphics.hpp"
namespace Engine2D
{
	class Calculations {
	public:
		static sf::Vector2f Vector2f_Normalize(sf::Vector2f Vector);
		static float Vector2f_Magnitude(sf::Vector2f Vector);
	};
}