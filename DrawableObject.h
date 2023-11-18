#pragma once
#include <set>
#include <SFML/Graphics.hpp>

namespace Engine2D {
	class DrawableObject
	{
	public:
		bool visible;
		static std::set<DrawableObject*> All;
		virtual void Draw();
		sf::RenderWindow window;
		DrawableObject(sf::RenderWindow window);
		~DrawableObject();
		virtual void deleteMe();
	};
}