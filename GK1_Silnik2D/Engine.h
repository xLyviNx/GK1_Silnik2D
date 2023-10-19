#pragma once
#include <SFML/Graphics.hpp>

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
		protected:
			static Engine* singleton;
		public:
			Engine();
			~Engine();
			static Engine* GetSingleton(bool);
		};
	}
}