#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObject.h"

namespace Engine2D {
	class DrawableObject : public virtual GameObject
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
		virtual void deleteMe() override;
	};
}