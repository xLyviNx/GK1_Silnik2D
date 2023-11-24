#include "InputReader.h"

vector<InputReader*> InputReader::InputReaders = vector<InputReader*>();
void InputReader::KeyPressed(sf::Keyboard::Key keyPressed) {}
void InputReader::KeyReleased(sf::Keyboard::Key keyPressed) {}
void InputReader::MousePressed(sf::Event::MouseButtonEvent mouseEvent) {}
void InputReader::MouseReleased(sf::Event::MouseButtonEvent mouseEvent) {}
InputReader::InputReader()
{
	InputReaders.push_back(this);
}
InputReader::~InputReader()
{
	auto it = std::find(InputReader::InputReaders.begin(), InputReader::InputReaders.end(), this);
	if (it != InputReader::InputReaders.end())
	{
		InputReader::InputReaders.erase(it);
	}
}

void InputReader::deleteMe()
{
	delete (InputReader*)this;
}
