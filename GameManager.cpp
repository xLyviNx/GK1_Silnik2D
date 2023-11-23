#include "GameManager.hpp"

int FlappyBird::GameManager::gap = 500;
int FlappyBird::GameManager::minY = -100;
int FlappyBird::GameManager::maxY = 100;
void FlappyBird::GameManager::SpawnObstales()
{
	int maxOnScreen = 6;
	float scale = 5.f;
	if (obstacles.size() < (maxOnScreen*2) &&  (obstacles.size()==0|| (obstacles.size() > 0 && obstacles[obstacles.size()-1]->worldPosition().x < appData->WindowSize.x - (13*scale*7))))
	{
		cout << obstacles.size() << endl;
		float posY = Calculations::Random(minY, maxY);
		for (int i = 0; i < 2; i++)
		{
			flappyObstacle* obst = new flappyObstacle(this);
			obst->setScale(scale, scale);
			obst->isTopOne = i == 0;
			obst->setPosition(Vector2f(appData->WindowSize.x + (13 * scale), -200));
			Vector2f pos = Vector2f(obst->position.x, appData->WindowSize.y / 2.0 + posY);
			if (i == 0)
			{
				pos.y -= gap;
			}
			else {
				pos.y += gap;
			}
			cout << "["<<i<<"] X: " << pos.x << ", Y : " << pos.y << ", posY: " << posY << endl;
			obst->setPosition(pos);
			obst->SetProperties();
			obstacles.push_back(obst);
		}
	}
}

void FlappyBird::GameManager::deleteMe()
{
	delete(this);
}

void FlappyBird::GameManager::Update(float deltaTime)
{
	SpawnObstales();
}
