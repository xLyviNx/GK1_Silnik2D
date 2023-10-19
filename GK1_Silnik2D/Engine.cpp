#include "Engine.h"
#include "ApplicationData.h"
#include <iostream>
#include <string>
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
	if (appData != NULL)
	{
		if (Window==NULL)
			Window = new RenderWindow(sf::VideoMode(appData->WindowSize.x, appData->WindowSize.y), appData->ApplicationName, (appData->displayMode == Fullscreen ? sf::Style::Fullscreen : sf::Style::Default));

		this->EngineLoop();
	}
	else {
		cout << "ERROR! APP DATA NOT FOUND\n";
	}
}
void Engine::EngineLoop()
{
	while (enabled)
	{

	}
	ClearMess();
}
void Engine::ClearMess()
{
	delete(appData);
	appData = NULL;
}