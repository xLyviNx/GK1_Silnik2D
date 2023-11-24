#pragma once

#include "UpdatableObject.h"
#include "ShapeObject.h"
#include "Engine.h"
#include "Transform.h"
#include "DrawableObject.h"

#define MAX_NUMBER_OF_OPTIONS 2

using namespace Engine2D;
class Menu : public virtual UpdatableObject, public virtual TransformableObject, public virtual InputReader, public virtual DrawableObject
{
private:
	int selectedOptionIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_OPTIONS];
	bool returnToMenu;
	bool endGame;

public:
	bool menuActive;
	Menu(float width, float height);
	void MoveUp();
	void MoveDown();
	int getPressedOption();
	virtual void deleteMe() override;
	virtual void Draw() override;
	virtual void KeyPressed(sf::Keyboard::Key keyPressed) override;
	virtual void KeyReleased(sf::Keyboard::Key keyPressed) override;
	virtual void MousePressed(sf::Event::MouseButtonEvent mouseEvent) override;
	virtual void MouseReleased(sf::Event::MouseButtonEvent mouseEvent) override;


};

