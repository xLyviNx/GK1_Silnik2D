#include "fb_Obstacle.hpp"
float FlappyBird::flappyObstacle::obstacleSpeed = 10.0f;
int FlappyBird::flappyObstacle::minY = 0 ;
int FlappyBird::flappyObstacle::maxY = 0 ;
void FlappyBird::flappyObstacle::Update(float deltaTime)
{

	position.x -= deltaTime * obstacleSpeed * 10.0f;
	if (worldPosition().x <= 150.f)
		deleteMe();
}

void FlappyBird::flappyObstacle::Start()
{
	if (isTopOne)
	{
		
	}
}

void FlappyBird::flappyObstacle::deleteMe()
{
	delete(this);
}
