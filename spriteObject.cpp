#include "spriteObject.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Calculations.h"
#include "BitmapHandler.h"
#include "Player.h"

namespace Engine2D
{

	void SpriteObject::setTexture(sf::Image bitmap)
	{
			 texture.loadFromImage(bitmap);
	}
	
	
}
