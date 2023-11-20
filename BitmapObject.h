#include <SFML/Graphics.hpp>
#include <iostream>
#include "DrawableObject.h"
#include <vector>
class BitmapObject : public Engine2D::DrawableObject 
{
	std::vector <sf::Image> bitmaps;

	void virtual Draw();
protected:
	void loadbitmaps(std::vector <sf::Image> bitmapstoload);
	void animate(double deltatime, double frame_speed);
	double offset;
	sf::Sprite renderobj;

};
