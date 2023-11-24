#include "Engine.h"
#include "PrimitiveRenderer.h"
#include <vector>
#include "GameObject.h"
#include "DrawableObject.h"
#include "ShapeObject.h"
#include "Player.h"
#include "BitmapHandler.h"
#include "GameManager.hpp"
#include "Camera.h"
#include "BitmapObject.h"

using namespace std;
using namespace Engine2D;
using namespace sf;

Engine* Engine::singleton = NULL;
float Engine::Gravity = 9.81f;
Engine* Engine::GetSingleton(bool CreateIfNull)
{
	if (Engine::singleton == NULL && CreateIfNull)
	{
		Engine::singleton = new Engine();
	}
	return singleton;
}
double Engine2D::Engine::AngleToRad(float degrees)
{
	return degrees * (M_PI / 180.0);
}

Engine::Engine()
{
	if (singleton != NULL)
	{
		delete(this);
		return;
	}
	singleton = this;
	cout << "Creating Engine Singleton.\n";
	enabled = true;
	keyboardInputEnabled = true;
	mouseInputEnabled = true;
	deltaTime = 0.0;
	LoadAppData();
	InitGame();
}
Engine::~Engine()
{
	cout << "Called Engine Destructor." << endl;
	if (Engine::singleton == this)
	{
		Engine::singleton = NULL;
		cout << "SETTING SINGLETON TO NULL\n";
	}
}
void Engine::InitGame()
{
	if (appData == NULL)
	{
		PrintLog("ERROR! APP DATA NOT FOUND! QUITTING");
		return;
	}
	srand(time(NULL));
	if (Window == NULL) {
		if (enabled) {
			InitLogs();
			PrintLog("Initializing Game Engine.");
			if (Window == NULL)
				Window = new RenderWindow(sf::VideoMode(appData->WindowSize.x, appData->WindowSize.y), appData->ApplicationName, (appData->displayMode == Fullscreen ? sf::Style::Fullscreen : sf::Style::Default));

			Window->setFramerateLimit(appData->maxFramerate);
			SpawnGame();
			this->EngineLoop();
		}
	}
}
void Engine::SpawnGame()
{
	Shapes::RectangleShape* gora = new Shapes::RectangleShape("Top", Vector2f(750, -50), 1500, 100, Color::Green, 1);
	Shapes::RectangleShape* dol = new Shapes::RectangleShape("Floor", Vector2f(750, 770), 1500, 100, Color::Green, 1);
	gora->tag = "kill";
	dol->tag = "kill";
	dol->fillColor = Color::Transparent;
	gora->color = Color::Transparent;
	dol->color = Color::Transparent;
	FlappyBird::GameManager* game = new FlappyBird::GameManager();

}
void Engine::EngineLoop()
{
	PrintLog("Entering Engine Loop");
	InputReader* testReader = new InputReader();
	sf::Clock clock;
	deltaTime = 0.0;

	sf::Clock fpsClock;
	int frameCount = 0;
	int fps = 0;

	sf::Text text;
	sf::Text scoreText;
	cout << "GRAVITY NOW: " << Gravity << endl;


	if (!baseFont.loadFromFile("fonts/PixellettersFull.ttf"))
	{
		cout << "Blad przy zaladowaniu czcionki";
	}

	//td::string tekst = "TEST";
	//sf::String sfmlString(tekst);
	//text.setString(sfmlString);

	text.setFont(baseFont);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(10.f, 10.f);

	scoreText.setFont(baseFont);
	scoreText.setCharacterSize(32);
	scoreText.setFillColor(sf::Color::White);

	/*std::vector < sf::Vector2f > points;
	points.push_back(sf::Vector2f(180, 100));
	points.push_back(sf::Vector2f(150, 320));
	points.push_back(sf::Vector2f(120, 320));
	points.push_back(sf::Vector2f(170, 420));
	points.push_back(sf::Vector2f(200, 520));
	*/
	//Shapes::RectangleShape* rectangle = new Shapes::RectangleShape(Vector2f(500,350), 150, 100, sf::Color::Yellow, 5.0);
	Shapes::CircleShape* circle = new Shapes::CircleShape(Vector2f(800, 300), 50, 5, Color(255,150,50), Color::Yellow);
	
	//rectangle->name = "TEST";
	// Obs³uga bitmapy  czyli przejscie z image>>texture>>sprite
	//BitmapHandler *bitmapa1 = new BitmapHandler(200,100);
	//bitmapa1->loadFromFile("grafika.png");
	sf::Texture texture;
	
	

	//test animacji

	/*
	frame.loadFromFile("sprite sheet.png", sf::IntRect(0, 0, 64, 64));
	toLoadVector.push_back(frame);
	frame.loadFromFile("sprite sheet.png", sf::IntRect(65, 1, 64, 64));
	toLoadVector.push_back(frame);
	frame.loadFromFile("sprite sheet.png", sf::IntRect(129, 0, 64, 64));
	toLoadVector.push_back(frame);
	frame.loadFromFile("sprite sheet.png", sf::IntRect(193, 0, 64, 64));
	toLoadVector.push_back(frame);
	*/
	
	
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("background_day.png")) {
		PrintLog("ERROR! Failed to load background texture.");
		return;
	}

	// Create a sprite for the background
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(static_cast<float>(Window->getSize().x) / backgroundTexture.getSize().x,
		static_cast<float>(Window->getSize().y) / backgroundTexture.getSize().y);

	/*frame.copy(frame, 0, 0, );
	toLoadVector.push_back(frame);
	frame.copy(frame, 0, 0, ,1);
	toLoadVector.push_back(frame);
	frame.copy(frame, 0, 0, sf::IntRect);
	toLoadVector.push_back(frame);
	frame.copy(frame, 0, 0, sf::IntRect);
	toLoadVector.push_back(frame);*/

	/*sf::Sprite Bitmapa_skonwertowana;
	Bitmapa_skonwertowana.setTexture(texture, true);
	Bitmapa_skonwertowana.setPosition(400, 300);
	*/


	
	


	//rectangle->Rotate(10.0);
	text.setOrigin(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f);
	//scoreText.setOrigin(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f);
	scoreText.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
	scoreText.setPosition(Vector2f(appData->WindowSize.x / 2.0f, 100));
	sf::View view = Window->getDefaultView();


	while (Window != NULL && enabled && Window->isOpen())
	{
		
		sf::Event event;
		frameCount++;
		if (fpsClock.getElapsedTime().asSeconds() >= 1.0)
		{
			fps = frameCount;
			frameCount = 0;
			fpsClock.restart();
		}
		text.setString("FPS: " + to_string(fps));

		//text.setPosition(Window->getSize().x / 2, Window->getSize().y / 2);
		deltaTime = clock.restart().asSeconds();
		
		Window->clear(sf::Color::Black);
		//rectangle->Translate(10.0 * deltaTime, 0);
		//circle->Translate(-10 * deltaTime, 0);

		//rectangle->Rotate(10.0 * deltaTime);
		
		// Draw the background sprite
		Window->draw(backgroundSprite);

		
		/*
		while (menuActive)
		{
			menu.Draw();
		}
		*/
		
		if (mouseInputEnabled)
		{
			mousePosition = sf::Mouse::getPosition();
		}
		else
		{
			mousePosition = Vector2i(0, 0);
		}
		while (Window->pollEvent(event))
		{
			if (keyboardInputEnabled)
			{
				vector<InputReader*> inputs = InputReader::InputReaders;
				if (event.type == sf::Event::KeyPressed)
				{
					for (InputReader* reader : inputs)
					{
						if (reader != NULL && !reader->isRemoving)
							reader->KeyPressed(event.key.code);
					}
						
				}
				else if (event.type == sf::Event::KeyReleased)
				{
					for (InputReader* reader : inputs)
					{
						//printf("ADDRESS: %p\n", reader);
						//printf("%d\n",reader->isRemoving);
						if (reader != NULL && !reader->isRemoving)
							reader->KeyReleased(event.key.code);

					}
				}
				else if (event.type == sf::Event::MouseButtonPressed)
				{
					for (InputReader* reader : inputs)
						if (reader != NULL && !reader->isRemoving)
							reader->MousePressed(event.mouseButton);
				}
				else if (event.type == sf::Event::MouseButtonReleased)
				{
					for (InputReader* reader : inputs)
						if (reader != NULL && !reader->isRemoving)
							reader->MouseReleased(event.mouseButton);
				}
				
				
			}
			if (event.type == sf::Event::Closed)
			{
				Window->close();
				break;
			}

			
		}
		for (int i = 0; i < UpdatableObject::All.size(); i++)
		{
			if (UpdatableObject::All[i] != NULL)
			{
				UpdatableObject::All[i]->Update(deltaTime);
			}
		}
		std::vector<DrawableObject*> uiobjects;
		for (int i = 0; i < DrawableObject::All.size(); i++)
		{
			if (DrawableObject::All[i] != NULL)
			{
				DrawableObject* drawable = DrawableObject::All[i];
				if (drawable->isUi) {
					uiobjects.push_back(drawable);
					continue;
				}
				if (drawable->visible);
					drawable->Draw();
			}
		}



		/*
		for (Collisions* colA : Collisions::All)
		{
			if (colA == NULL)
				continue;
			if (!colA->enabled)
				continue;
			for (Collisions* colB : Collisions::All)
			{
				if (colB == NULL || colA == NULL || colB == colA || !colB->enabled)
					continue;
				bool contains = std::find(colA->currentCollisions.begin(), colA->currentCollisions.end(), colB) != colA->currentCollisions.end();
				if (colB->Collides(colA))
				{
					if (!contains)
					{
						colA->OnCollisionEnter(colB);
						cout << colA << endl;
						colA->enabled = false;
						cout << colA->currentCollisions.size()<<endl;
						colA->currentCollisions.push_back(colB);
					}
					else
					{
						colA->OnCollisionStay(colB);
					}
				}
				else if (contains)
				{
					for (vector<Collisions*>::iterator it = colA->currentCollisions.begin(); it != colA->currentCollisions.end(); ++it)
					{
						if (*it == colB) {
							*it = NULL;
							break;
						}
					}
					colA->OnCollisionExit(colB);
				}
			}
		}*/
		vector<Collisions*>::iterator itA;
		vector<Collisions*>::iterator itF;
		vector<Collisions*>::iterator itB;
		for (itA = Collisions::All.begin(); itA != Collisions::All.end();itA++)
		{
			if (*itA == NULL || !(*itA)->enabled)
			{
				continue;
			}
			for (itB = Collisions::All.begin(); itB != Collisions::All.end();itB++)
			{
				if (*itB == NULL || *itA == *itB || !(*itB)->enabled)
				{
					continue;
				}
				itF = std::find((*itA)->currentCollisions.begin(), (*itA)->currentCollisions.end(), (*itB));
				bool contains = itF != (*itA)->currentCollisions.end();
				if ((*itA)->Collides(*itB))
				{
					if (contains)
					{
						(*itA)->OnCollisionStay(*itB);
					}
					else
					{
						(*itA)->currentCollisions.push_back(*itB);
						(*itA)->OnCollisionEnter(*itB);
					}
				}
				else
				{
					if (contains)
					{
						(*itA)->currentCollisions.erase(itF);
						(*itA)->OnCollisionExit(*itB);
					}
				}
			}
		}
		//Window->draw(Bitmapa_skonwertowana);
		Window->setView(Window->getDefaultView());
		for (int i = 0; i < uiobjects.size(); i++)
		{
			if (uiobjects[i] != NULL)
			{
				DrawableObject* drawable = uiobjects[i];
				if (drawable->visible);
					drawable->Draw();
			}
		}
		int score = FlappyBird::GameManager::singleton? FlappyBird::GameManager::singleton->points : -1;
		scoreText.setString((score >= 0 ? to_string(score) : ""));
		Window->draw(text);
		Window->draw(scoreText);
		removeAwaitingObjects();
		//Point2D p2d(sf::Color::Red, (double)5.0, Vector2f(640, 360));
		//p2d.DrawPointSFML();
		//PrimitiveRenderer::DrawEllipse(Vector2f(155, 360), 150, 200, Color::White);
		//PrimitiveRenderer::DrawCircle(Vector2f(500, 360), 150, Color::White);
		//PrimitiveRenderer::DrawSingleLine(Window, Vector2f(700, 200), Vector2f(700, 600), 3.0, Color::Red);
		//PrimitiveRenderer::PointLine(Window, &points, 2.0, Color::Yellow);
		Window->display();
	}
	PrintLog("CLOSED THE GAME WINDOW.");
	enabled = false;
	Cleanup();
}
bool Engine2D::Engine::isKeyTriggered(sf::Keyboard::Key key)
{
	return (keyboardInputEnabled && sf::Keyboard::isKeyPressed(key));
}


void Engine::Cleanup()
{
	PrintLog("Cleaning up the Engine...");

	CleanupScene();

	delete(appData);
	appData = NULL;
	delete(Window);
	Window = NULL;
}
void Engine::CleanupScene()
{
	for(GameObject* gObject : GameObject::All)
	{
		if (gObject != NULL)
		{
			gObject->isRemoving = true;
		}
	}
	removeAwaitingObjects();
	GameObject::All.clear();
}
void Engine::InitLogs()
{
	const std::string logFilename = LOGFILE;
	const std::string oldLogFilename = LOGFILE_OLD;
	std::ifstream logFile(logFilename);
	if (logFile.good()) {
		logFile.close();
		std::remove(oldLogFilename.c_str());
		if (std::rename(logFilename.c_str(), oldLogFilename.c_str()) != 0) {
			std::cerr << "ERROR SWAPPING LOG FILES (OLD FILE)." << std::endl;
		}
	}
	std::ofstream newLogFile(logFilename);
	if (newLogFile.is_open())
	{
		newLogFile.close();
	}
	else {
		std::cerr << "ERROR CREATING NEW LOG FILE." << std::endl;
	}
}
void Engine::PrintLog(const std::string& log) {
	const std::string logFilename = LOGFILE;

	std::time_t now = std::time(nullptr);
	std::tm tm;
	if (localtime_s(&tm, &now) != 0) {
		std::cerr << "ERROR READING DATETIME" << std::endl;
		return;
	}

	char timestamp[20];
	std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &tm);

	std::ofstream logFile(logFilename, std::ios::app);

	if (logFile.is_open()) {
		string logWTime = "[" + (string)timestamp + "] " + log + "\n";
		cout << "(LOG) " << logWTime;
		logFile << logWTime;
		logFile.close();
	}
	else {
		std::cerr << "ERROR READING LOGS FILE" << std::endl;
	}
}
void Engine::removeAwaitingObjects()
{
	vector<GameObject*> toRemove;
	for (vector<GameObject*>::iterator it = GameObject::All.begin(); it != GameObject::All.end();)
	{
		if ((*it) == NULL)
		{
			GameObject::All.erase(it);
			continue;
		}
		else if ((*it)->isRemoving)
		{
			toRemove.push_back(*it);
			++it;
		}
		else {
			++it;
		}
	}
	for (GameObject* g : toRemove)
	{
		vector<GameObject*>::iterator itF = std::find(GameObject::All.begin(), GameObject::All.end(), g);
		if (*itF != NULL)
		{
			cout << "REMOVING OBJECT '" << (*itF) << "'" << endl;
			(*itF)->deleteMe();
		}
		else {
			PrintLog("Couldn't remove an object.");
		}
	}
}