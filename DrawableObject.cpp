#include "DrawableObject.h"
#include "SFML/Graphics.hpp"
#include "Engine.h"
namespace Engine2D {
	std::vector<DrawableObject*> DrawableObject::All;
	
	
	DrawableObject::DrawableObject()
	{
		Engine* eng = Engine::GetSingleton(false);
		this->window = eng? eng->Window : NULL;
		visible = true;
		isUi = false;
		All.push_back(this);
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
		std::cout << "SETTING NULL DRAWABLE" << std::endl;
		for (vector<DrawableObject*>::iterator it = DrawableObject::All.begin(); it != DrawableObject::All.end(); ++it)
		{
			if (*it == this) {
				*it = NULL;
				break;
			}
		}
	}

	void DrawableObject::deleteMe()
	{
		delete this;
	}

}