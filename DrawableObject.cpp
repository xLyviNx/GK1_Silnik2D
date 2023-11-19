#include "DrawableObject.h"
#include "SFML/Graphics.hpp"
#include "Engine.h"
namespace Engine2D {
	std::set<DrawableObject*> DrawableObject::All;
	
	
	DrawableObject::DrawableObject()
	{
		Engine* eng = Engine::GetSingleton(false);
		this->window = eng? eng->Window : NULL;
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