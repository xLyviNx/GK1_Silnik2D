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
		cout << "TEST" << endl;
		cout << appData->WindowSize.x << endl;
		cout << appData->WindowSize.y << endl;
		string stdStr = "ja pierdole";
		sf::String sfStr = sf::String::fromUtf8(stdStr.begin(), stdStr.end());
		//RenderWindow window(sf::VideoMode(appData->WindowSize.x, appData->WindowSize.y), appData->ApplicationName);

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