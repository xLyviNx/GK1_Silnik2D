#include "Engine.h"
#include "PrimitiveRenderer.h"
#include <vector>
#include "GameObject.h"
#include "DrawableObject.h"
#include "ShapeObject.h"
#include "Player.h"
#include "BitmapHandler.h"
#include "Camera.h"
using namespace std;
using namespace Engine2D;
using namespace sf;

Engine* Engine::singleton = NULL;
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
	Gravity = 9.81;
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
	if (Window == NULL) {
		if (enabled) {
			InitLogs();
			PrintLog("Initializing Game Engine.");
			if (Window == NULL)
				Window = new RenderWindow(sf::VideoMode(appData->WindowSize.x, appData->WindowSize.y), appData->ApplicationName, (appData->displayMode == Fullscreen ? sf::Style::Fullscreen : sf::Style::Default));

			Window->setFramerateLimit(appData->maxFramerate);

			this->EngineLoop();
		}
	}
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

	sf::Font font;
	sf::Text text;
	


	if (!font.loadFromFile("fonts/PixellettersFull.ttf"))
	{
		cout << "Blad przy zaladowaniu czcionki";
	}

	//td::string tekst = "TEST";
	//sf::String sfmlString(tekst);
	//text.setString(sfmlString);

	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(10.f, 10.f);


	std::vector < sf::Vector2f > points;
	points.push_back(sf::Vector2f(180, 100));
	points.push_back(sf::Vector2f(150, 320));
	points.push_back(sf::Vector2f(120, 320));
	points.push_back(sf::Vector2f(170, 420));
	points.push_back(sf::Vector2f(200, 520));

	Shapes::RectangleShape* rectangle = new Shapes::RectangleShape(Vector2f(500,350), 150, 100, sf::Color::Yellow, 5.0);
	Shapes::CircleShape* circle = new Shapes::CircleShape(Vector2f(800, 300), 150, Color::Red);
	rectangle->name = "TEST";
	Camera* camera = new Camera("Main Camera", Vector2f(0, 0));
	Player* plr = new Player("Player Object", Vector2f(500, 500));

	BitmapHandler *bitmapa1 = new BitmapHandler(200,100);
	bitmapa1->loadFromFile("grafika.png");
	sf::Texture texture;
	texture.loadFromImage(bitmapa1->getImage());
	sf::Sprite Bitmapa_skonwertowana;
	Bitmapa_skonwertowana.setTexture(texture, true);
	Bitmapa_skonwertowana.setPosition(400, 300);
	

	while (Window != NULL && enabled && Window->isOpen())
	{
		
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
		rectangle->Translate(10.0 * deltaTime, 0);
		//circle->Translate(-10 * deltaTime, 0);
		//rectangle->Rotate(10.0 * deltaTime);

		sf::Event event;
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
				if (event.type == sf::Event::KeyPressed)
				{
					for (InputReader* reader : InputReader::InputReaders)
						reader->KeyPressed(event.key.code);

				}
				else if (event.type == sf::Event::KeyReleased)
				{
					for (InputReader* reader : InputReader::InputReaders)
						reader->KeyReleased(event.key.code);
				}
				else if (event.type == sf::Event::MouseButtonPressed)
				{
					for (InputReader* reader : InputReader::InputReaders)
						reader->MousePressed(event.mouseButton);
				}
				else if (event.type == sf::Event::MouseButtonReleased)
				{
					for (InputReader* reader : InputReader::InputReaders)
						reader->MouseReleased(event.mouseButton);
				}
			}
			if (event.type == sf::Event::Closed)
			{
				Window->close();
				break;
			}
		}
		for (UpdatableObject* upd : UpdatableObject::All)
		{
			upd->Update(deltaTime);
		}		
		for (DrawableObject* drawable : DrawableObject::All)
		{
			if (drawable->visible)
				drawable->Draw();
		}
		Window->draw(Bitmapa_skonwertowana);
		Window->draw(text);
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
	while (!GameObject::All.empty())
	{
		GameObject* gObject = *(GameObject::All.begin());
		if (gObject != NULL)
		{
			gObject->deleteMe();
		}
		else
			GameObject::All.erase(gObject);
	}
	GameObject::All.clear();
	while (!UpdatableObject::All.empty())
	{
		UpdatableObject* object = *(UpdatableObject::All.begin());
		if (object != NULL)
		{
			object->deleteMe();
		}
		else
			UpdatableObject::All.erase(object);
	}
	UpdatableObject::All.clear();

	while (!InputReader::InputReaders.empty())
	{
		InputReader* object = *(InputReader::InputReaders.begin());
		if (object != NULL)
		{
			object->deleteMe();
		}
		else
			InputReader::InputReaders.erase(object);
	}
	UpdatableObject::All.clear();
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
