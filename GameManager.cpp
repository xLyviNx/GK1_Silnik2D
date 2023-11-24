#include "GameManager.hpp"
#include "flappyScore.hpp"

int FlappyBird::GameManager::gap = 500;
int FlappyBird::GameManager::minY = -100;
int FlappyBird::GameManager::maxY = 100;
FlappyBird::GameManager* FlappyBird::GameManager::singleton = NULL;
FlappyBird::GameManager::GameManager()
{
	if (singleton == NULL)
	{
		singleton = this;
	}
	else {
		isRemoving = true;
	}
	GamePlayer = NULL;
	inGame = false;
	GameMenu = new Menu(Engine::GetSingleton(false)->Window->getSize().x, Engine::GetSingleton(false)->Window->getSize().y);

}
FlappyBird::GameManager::~GameManager()
{
	if (GameManager::singleton == this)
		GameManager::singleton = NULL;
}
void FlappyBird::GameManager::SpawnObstacles()
{
	int maxOnScreen = 6;
	float scale = 5.f;
	if (obstacles.size() < (maxOnScreen*2) &&  (obstacles.size()==0|| (obstacles.size() > 0 && obstacles[obstacles.size()-1]->worldPosition().x < appData->WindowSize.x - (13*scale*7))))
	{
		//cout << obstacles.size() << endl;
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

			obst->setPosition(pos);
			obst->SetProperties();
			obstacles.push_back(obst);
			if (i == 0) {
				pos.y = appData->WindowSize.y / 2.0 + posY;
				flappyScore* score = new flappyScore(pos);
				//cout << "X: " << score->worldPosition().x << ", Y : " << score->worldPosition().y << endl;
				score->SetParent((TransformableObject*)obst);
			}
		}
	}
}

void FlappyBird::GameManager::deleteMe()
{
	delete (GameManager*)this;
}

void FlappyBird::GameManager::Update(float deltaTime)
{
	GameMenu->visible = !inGame;
	if (inGame) {
		SpawnObstacles();
	}
}

void FlappyBird::GameManager::GameOver()
{
	points = -1;
	inGame = false;
	GameMenu->menuActive = true;
	if (GamePlayer)
		((GameObject*)(GamePlayer))->isRemoving = true;
	GamePlayer = NULL;
}
void FlappyBird::GameManager::StartGame()
{
	points = 0;

	GamePlayer = new Player("Player Object", Vector2f(500, 500));
	GamePlayer->tag = "Player";
	std::vector<sf::Texture> toLoadVector;
	sf::Texture frame;
	frame.loadFromFile("flappy_bird.png", sf::IntRect(0, 0, 86, 86));
	toLoadVector.push_back(frame);

	frame.loadFromFile("flappy_bird.png", sf::IntRect(96, 0, 86, 86));
	toLoadVector.push_back(frame);

	frame.loadFromFile("flappy_bird.png", sf::IntRect(192, 0, 86, 86));
	toLoadVector.push_back(frame);
	BitmapObject* bitmapobj = new BitmapObject();
	bitmapobj->loadbitmaps(toLoadVector);
	GamePlayer->loadbitmaps(toLoadVector);
	inGame = true;
	GameMenu->menuActive = false;
	GameMenu->visible = false;
}