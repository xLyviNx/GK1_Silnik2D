#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "GameObject.h"
using namespace std;
class InputReader : public virtual Engine2D::GameObject
{
public:
	virtual void KeyPressed(sf::Keyboard::Key keyPressed);
	virtual void KeyReleased(sf::Keyboard::Key keyPressed);
	virtual void MousePressed(sf::Event::MouseButtonEvent mouseEvent);
	virtual void MouseReleased(sf::Event::MouseButtonEvent mouseEvent);
	static vector<InputReader*> InputReaders;
	InputReader();
	~InputReader();
	virtual void deleteMe() override;
};