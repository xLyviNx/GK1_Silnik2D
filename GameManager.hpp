#pragma once
#include "fb_Obstacle.hpp"
#include "UpdatableObject.h"
#include "Calculations.h"
#include "Menu.h"
namespace FlappyBird
{
	class flappyObstacle;
	class GameManager : public virtual Engine2D::UpdatableObject
	{
	public:
		static int minY;
		static int maxY;
		static int gap;
		GameManager();
		~GameManager();
		Menu* GameMenu;
		bool inGame;
		static GameManager* singleton;
		std::vector<flappyObstacle*> obstacles;
		void SpawnObstales();
		void Update(float deltaTime) override;
		void GameOver();
		void StartGame();
		virtual void deleteMe() override;
		Player* GamePlayer;
		int points;
	};
}