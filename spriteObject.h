#pragma once
#include "Bitmapobject.h"
#include "AnimatedObject.h"
#include "Player.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "BitmapHandler.h"
namespace Engine2D
{ 
	class SpriteObject : public virtual BitmapObject, public virtual AnimatedObject
	{ 
		sf::Texture texture;
		void setTexture(sf::Image image);
	protected:
		int animation_index;

	};
}
