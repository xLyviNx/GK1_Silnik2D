#pragma once
#include <set>
#include <SFML/Graphics.hpp>

namespace Engine2D {
	class DrawableObject
	{
	public:
		bool visible;
		static std::vector<DrawableObject*> All;
		virtual void Draw();
		sf::RenderWindow* window;
		DrawableObject();
		virtual void Draw(sf::Texture texture);
		~DrawableObject();
		bool isUi;
		virtual void deleteMe();
	};
}