#include "Engine.h"
#include "ApplicationData.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace GRUPA3::Engine2D;

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
	sf::RenderWindow window(sf::VideoMode(appData->WindowSize.x, appData->WindowSize.y), appData->ApplicationName);
	this->EngineLoop();
}
void Engine::EngineLoop()
{
	while (enabled)
	{

	}
}