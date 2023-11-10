#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include <iostream>
using namespace std;
class InputReader
{
public:
	virtual void KeyPressed(sf::Keyboard::Key keyPressed);
	virtual void KeyReleased(sf::Keyboard::Key keyPressed);
	virtual void MousePressed(sf::Event::MouseButtonEvent mouseEvent);
	virtual void MouseReleased(sf::Event::MouseButtonEvent mouseEvent);
	static set<InputReader*> InputReaders;
	InputReader();
	~InputReader();
	virtual void deleteMe();
};