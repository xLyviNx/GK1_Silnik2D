#include "DrawableObject.h"
#include "SFML/Graphics.hpp"
namespace Engine2D {
	std::set<DrawableObject*> DrawableObject::All;
	
	
	DrawableObject::DrawableObject(sf::RenderWindow *window)
	{
		this->window = window;
		visible = true;
		All.insert(this);
	}

	void DrawableObject::Draw(sf::Texture texture)
	{
		//window->draw();
	}

	void DrawableObject::Draw()
	{
	}

	DrawableObject::~DrawableObject()
	{
		All.erase(this);
	}

	void DrawableObject::deleteMe()
	{
		delete this;
	}

}