#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DrawableObject.h"
#include <vector>
/**
 * @brief klasa sluzaca do obslugi animowanych obiektow, uzywajacych bitmap
 */
class BitmapObject : public Engine2D::DrawableObject 
{
	
protected:
	int i=0;
	double offset; 
	
public: 
	/**
	 * @brief funkcja ladujaca bitmape z obiektu typu Vector do wewnetrznego Vectora
	 * 
	 * @param Vector z ktorego maja byc zaladowane Bitmapy
	 */
	void loadbitmaps(std::vector <sf::Texture> bitmapstoload);
	/**
	 * @brief funkcja zmieniaj¹ca ,,klatki" animacji
	 * 
	 * @param deltaTime zmienna sluzaca do odmierzania czasu miedzy klatkami.
	 * @param frame_speed zmienna ktora okresla czas miedzy klatkami wzgledem wartosci deltaTime
	 * @param version wybor wersji animacji, tzn zalozylismy ze w przyszlosci animacji moze byc wiecej a ta zmienna bedzie sluzyla do ich wyboru
	 */
	void animate(double deltatime, double frame_speed,int version);
	sf::Sprite renderobj;///< obiekt z ktorego pomoca mozna wyrenderowac animacje 
	std::vector <sf::Texture> bitmaps; ///<Vector sluzacy do przechowywania Bitmap wewnatrz klasy 
	virtual void deleteMe() override;///<zmienna usuwajaca obiekt

	//void virtual Draw();


};
