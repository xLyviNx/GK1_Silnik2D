#include "fb_Obstacle.hpp"
float FlappyBird::flappyObstacle::obstacleSpeed = 10.0f;
void FlappyBird::flappyObstacle::Update(float deltaTime)
{

	position.x -= deltaTime * obstacleSpeed * 10.0f;
	if (worldPosition().x <= 150.f)
		deleteMe();
}

void FlappyBird::flappyObstacle::Start()
{
	if (bottom == NULL && isTopOne)
	{
		bottom = flappyObstacle();
	}
}

void FlappyBird::flappyObstacle::deleteMe()
{
	delete(this);
}
