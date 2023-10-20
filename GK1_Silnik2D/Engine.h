#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "ApplicationData.h"
#include <iostream>
#include <string>
#include "InputReader.h"
#include <fstream>

#define LOGFILE "log.txt"
#define LOGFILE_OLD "log-old.txt"

namespace GRUPA3
{
	namespace Engine2D
	{
		class Engine
		{
		private:
			void InitGame();
			void EngineLoop();
			bool enabled;
			sf::RenderWindow* Window;
			int fps;
			void Cleanup();
			bool keyboardInputEnabled;
			bool mouseInputEnabled;
			sf::Vector2i mousePosition;
			static void InitLogs();
			static void PrintLog(const std::string& log);
		protected:
			static Engine* singleton;
		public:
			Engine();
			~Engine();
			static Engine* GetSingleton(bool);
			double deltaTime;
		};
	}
}