#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Engine2D {
	/**
	 * @brief Klasa AnimatedObject.
	 *
	 * Klasa umozliwia animowanie obiektu. Jest klas� powsta�� na potrzeby zadania, na t� chwile jej role przejmuje klasa BitmapObject
	 */
	class AnimatedObject
	{
		/**
	 * @brief Funkcja animacji.
	 *
	 * Funkcja umozliwia animowanie obiektu.
	 *
	 */
		void animate();
	};
}