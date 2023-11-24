#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "GameObject.h"
using namespace std;
/**
 * @brief klasa sluzaca do obslugi wejscia.
 */
class InputReader : public virtual Engine2D::GameObject
{
public:
	/**metoda sluzaca do obslugi wcisniecia klawisza.
	 * 
	 * @param keyPressed parametr bedacy aktualnym przyciskiem
	 */
	virtual void KeyPressed(sf::Keyboard::Key keyPressed);
	/**
	 * @brief metoda sluzaca do obslugi zwolnienia klawisza.
	 *
	 * @param keyPressed parametr bedacy aktualnym przyciskiem
	 */
	virtual void KeyReleased(sf::Keyboard::Key keyPressed);
	/**
	 * @brief metoda do obslugi wcisniecia klawisza myszy
	 * 
	 * @param mouseEvent zdarzenie myszy 
	 */
	virtual void MousePressed(sf::Event::MouseButtonEvent mouseEvent);
	/**
	 * @brief metoda do obslugi zwolnienia klawisza myszy
	 *
	 * @param mouseEvent zdarzenie myszy
	 */
	virtual void MouseReleased(sf::Event::MouseButtonEvent mouseEvent);
	static vector<InputReader*> InputReaders;///<Vector sluzacy do przecchowyywania zdarzen wejscia
	InputReader();
	~InputReader();
	virtual void deleteMe() override;
};