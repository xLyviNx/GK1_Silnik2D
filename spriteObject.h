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
	class SpriteObject : public BitmapObject, public AnimatedObject, public Player
	{ 


		sf::Texture texture;
		void setTexture();
		void Movement(Engine* engine, float deltaTime);

	};
}
