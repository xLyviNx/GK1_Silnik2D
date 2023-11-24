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
	/**
	  * @brief klasa reprezentujaca obiekt typu ,,sprite" dziedziczy po Bitmapobject, na ta chwile jest klasa abstrakcyjna, poniewaz jej role zastepuje klasa Player
	  */
	class SpriteObject : public virtual BitmapObject, public virtual AnimatedObject
	{ 
		sf::Texture texture;///<aktualna tekstura
		/**
		 * @brief funkcja ustawiajaca dana teksture
		 * 
		 * @param obraz do zaladowania typu sf::Image
		 */
		void setTexture(sf::Image image);

		
	public:
		/**
		 * @brief funkcja usuwajaca obiekt.
		 * 
		 */
		virtual void deleteMe() override;
	};
}
