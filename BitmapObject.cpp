#include <SFML/Graphics.hpp>
#include <iostream>
#include "BitmapObject.h"

void BitmapObject::loadbitmaps(std::vector<sf::Image> bitmapstoload)
{
	for (sf::Image bitmapa : bitmapstoload)
	{
		bitmaps.push_back(bitmapa);
	}
}

void BitmapObject::animate(double deltatime, double frame_speed)
{
	offset+=deltatime;
	sf::Texture actual_texture;
	int i=0;
	actual_texture.loadFromImage(bitmaps[i]);
	if (offset > frame_speed)
		i++;
	renderobj.setTexture(actual_texture);
	if (i == 4)
		i = 0;
	offset = 0;
}
