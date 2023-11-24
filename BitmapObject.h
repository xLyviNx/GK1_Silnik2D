#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DrawableObject.h"
#include <vector>
class BitmapObject : public Engine2D::DrawableObject 
{
	
protected:
	int i=0;
	double offset;
	
public: 
	void loadbitmaps(std::vector <sf::Texture> bitmapstoload);
	void animate(double deltatime, double frame_speed,int version);
	sf::Sprite renderobj;
	std::vector <sf::Texture> bitmaps;
	virtual void deleteMe() override;

	//void virtual Draw();


};
