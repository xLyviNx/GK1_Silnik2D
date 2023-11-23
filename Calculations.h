#pragma once
#include "SFML/Graphics.hpp"
#define M_PI 3.14159265358979323846

namespace Engine2D
{
	class Calculations {
	public:
		static sf::Vector2f Vector2f_Normalize(sf::Vector2f Vector);
		static float Vector2f_Magnitude(sf::Vector2f Vector);
		static float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b);
		static int Random(int min, int max);
	};
}