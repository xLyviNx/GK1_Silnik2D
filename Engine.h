#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "ApplicationData.h"
#include <iostream>
#include <string>
#include "InputReader.h"
#include <fstream>
#include "UpdatableObject.h"

#define LOGFILE "log.txt"
#define LOGFILE_OLD "log-old.txt"

namespace Engine2D
{
	class Engine
	{
	private:
		void InitGame();
		void EngineLoop();
		bool enabled;
		void Cleanup();
		void CleanupScene();
		bool keyboardInputEnabled;
		bool mouseInputEnabled;
		sf::Vector2i mousePosition;
		static void InitLogs();
		void SpawnGame();
	protected:
		static Engine* singleton;
	public:
		static float Gravity;
		Engine();
		~Engine();
		static void PrintLog(const std::string& log);
		sf::RenderWindow* Window;
		static Engine* GetSingleton(bool);
		double deltaTime;
		static double AngleToRad(float angle);
		bool isKeyTriggered(sf::Keyboard::Key key);
	};
}
