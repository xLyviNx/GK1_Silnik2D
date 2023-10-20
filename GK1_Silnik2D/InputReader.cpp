#include "InputReader.h"

set<InputReader*> InputReader::InputReaders;
void InputReader::KeyPressed(sf::Keyboard::Key keyPressed) {}
void InputReader::KeyReleased(sf::Keyboard::Key keyPressed){}
void InputReader::MousePressed(sf::Event::MouseButtonEvent mouseEvent){}
void InputReader::MouseReleased(sf::Event::MouseButtonEvent mouseEvent){}
InputReader::InputReader()
{
	InputReaders.insert(this);
}
InputReader::~InputReader()
{
	InputReaders.erase(this);
}