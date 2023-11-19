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
		sf::RenderWindow* window;
		DrawableObject();
		virtual void Draw(sf::Texture texture);
		~DrawableObject();
		virtual void deleteMe();
	};
}