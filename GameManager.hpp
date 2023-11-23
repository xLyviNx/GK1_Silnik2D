#pragma once
#include "fb_Obstacle.hpp"
#include "UpdatableObject.h"
#include "Calculations.h"

namespace FlappyBird
{
	class flappyObstacle;
	class GameManager : public virtual Engine2D::UpdatableObject
	{
		static int minY;
		static int maxY;
		static int gap;
	public:
		std::vector<flappyObstacle*> obstacles;
		void SpawnObstales();
		void Update(float deltaTime) override;
		void deleteMe() override;
	};
}