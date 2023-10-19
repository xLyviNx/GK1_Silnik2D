#include "Engine.h"
#include "ApplicationData.h"
#include <iostream>
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
	cout << "Creating Engine Singleton.\n";
	enabled = true;
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
	cout << "TEST" << endl;
	cout << appData->WindowSize.x << endl;
	cout << appData->WindowSize.y << endl;
	string appname = appData->ApplicationName;
	cout << appname << endl;
	sf::String mySfString(appname);
	cout << mySfString.toAnsiString() << endl;
	Window = new RenderWindow(sf::VideoMode(appData->WindowSize.x, appData->WindowSize.y), mySfString);

	this->EngineLoop();
}
void Engine::EngineLoop()
{
	while (enabled)
	{

	}
}