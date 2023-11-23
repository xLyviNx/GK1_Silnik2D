#include "Menu.h"
#include "ShapeObject.h"
#include "DrawableObject.h"

Menu::Menu(float width, float height)
{
	menuActive = true;
	window = Engine::GetSingleton(false)->Window;
	
	// Wczytanie czczcionki dla tekstu
	if (!font.loadFromFile("fonts/PixellettersFull.ttf"))
	{
		cout << "Blad w MENU przy zaladowaniu tekstury font";
	}

	menu[0].setFont(font);
	menu[0].setCharacterSize(52); 
	menu[0].setFillColor(sf::Color::Blue); 
	menu[0].setString("Graj"); 
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_OPTIONS + 1) * 1)); 
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2); 
	menu[0].setOutlineColor(sf::Color::Black); 
	menu[0].setOutlineThickness(2.5f); 


	menu[1].setFont(font);
	menu[1].setCharacterSize(52); 
	menu[1].setFillColor(sf::Color::White); 
	menu[1].setString("Wyjdz"); 
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_OPTIONS + 1) * 2)); 
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2); 
	menu[1].setOutlineColor(sf::Color::Black);
	menu[1].setOutlineThickness(2.5f);

	selectedOptionIndex = 0;
}

void Menu::MoveUp()
{
	if (selectedOptionIndex - 1 >= 0)
	{
		menu[selectedOptionIndex].setFillColor(sf::Color::White);
		selectedOptionIndex--;
		menu[selectedOptionIndex].setFillColor(sf::Color::Blue);
	}
}

void Menu::MoveDown()
{
	if (selectedOptionIndex + 1 < MAX_NUMBER_OF_OPTIONS)
	{
		menu[selectedOptionIndex].setFillColor(sf::Color::White);
		selectedOptionIndex++;
		menu[selectedOptionIndex].setFillColor(sf::Color::Blue);
	}
}

int Menu::getPressedOption()
{
	return selectedOptionIndex;
}


void Menu::deleteMe()
{
	delete this;
}

void Menu::Draw()
{
	
	for (int i = 0; i < MAX_NUMBER_OF_OPTIONS; i++)
	{
		this->window->draw(menu[i]);
	}
	//this->window->display();
}

void Menu::KeyPressed(sf::Keyboard::Key keyPressed)
{
	
}

void Menu::KeyReleased(sf::Keyboard::Key keyPressed)
{
		switch (keyPressed)
		{
		case sf::Keyboard::Up:
			MoveUp();
			break;

		case sf::Keyboard::Down:
			MoveDown();
			break;
		case sf::Keyboard::Escape:
			returnToMenu = true;
			break;

		case sf::Keyboard::Return:
			switch (getPressedOption())
			{
			case 0:
				cout << "Wcisnieto graj" << endl;
				menuActive = false;
				break;
			case 1:
				cout << "Wcisnieto wyjdz" << endl;
				this->window->close();
				menuActive = false;
				break;
			}

			break;


		}


	
}

void Menu::MousePressed(sf::Event::MouseButtonEvent mouseEvent)
{

}

void Menu::MouseReleased(sf::Event::MouseButtonEvent mouseEvent)
{

}
