#include <SFML/Graphics.hpp>
#include <iostream>
#include "BitmapObject.h"

void BitmapObject::loadbitmaps(std::vector<sf::Texture> bitmapstoload)
{
	for (sf::Texture bitmapa : bitmapstoload)
	{
		bitmaps.push_back(bitmapa);
	}
}

void BitmapObject::animate(double deltatime, double frame_speed, int version)
{
	offset+=deltatime;
	//sf::Texture actual_texture;
	//actual_texture = bitmaps[i];
	if (offset > frame_speed)
	{
		i++;
		offset = 0;
	}
	if (i >= bitmaps.size())
		i = 0;
	renderobj.setTexture(bitmaps[i]);
	
}
