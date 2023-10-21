#include "Engine.h"
#include "PrimitiveRenderer.h"

using namespace std;
using namespace GRUPA3::Engine2D;
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
	EngineLoop();
}
Engine::~Engine() 
{
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

	InitLogs();
	PrintLog("Initializing Game Engine.");
	if (Window == NULL)
		Window = new RenderWindow(sf::VideoMode(appData->WindowSize.x, appData->WindowSize.y), appData->ApplicationName, (appData->displayMode == Fullscreen ? sf::Style::Fullscreen : sf::Style::Default));

	Window->setFramerateLimit(appData->maxFramerate);

	this->EngineLoop();
}
void Engine::EngineLoop()
{
	InputReader* testReader = new InputReader();
	sf::Clock clock;
	deltaTime = 0.0;

	sf::Font font;
	/*if (!font.loadFromFile("./Swansea.ttf"))
	{
		
	}*/
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setString("Hello, SFML!");
	LineRenderer* line = new LineRenderer(Color::Green, 5.0, sf::Vector2f(150, 150), sf::Vector2f(700, 700));
	float angle = 0;
	while (Window != NULL && enabled && Window->isOpen())
	{
		text.setPosition(Window->getSize().x / 2, Window->getSize().y / 2);
		deltaTime = clock.restart().asSeconds();

		angle += 0.5 * deltaTime;

		// Oblicz nowe po³o¿enie punktów linii
		sf::Vector2f center(Window->getSize().x / 2, Window->getSize().y / 2);
		sf::Vector2f offset1(std::cos(angle) * 100, std::sin(angle) * 100);
		sf::Vector2f offset2(std::cos(angle + 3.14159) * 100, std::sin(angle + 3.14159) * 100);

		line->posA = center + offset1;
		line->posB = center + offset2;
		Window->clear(sf::Color::Black);
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
		Window->draw(text);
		line->Draw();
		Window->display();
	}
	enabled = false;
	delete(line);
	delete(testReader);
	Cleanup();
}
void Engine::Cleanup()
{
	PrintLog("Cleaning up the Engine...");
	delete(appData);
	appData = NULL;
	delete(Window);
	Window = NULL;
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
 