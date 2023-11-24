#include "fb_Obstacle.hpp"
float FlappyBird::flappyObstacle::obstacleSpeed = 10.0f;

void FlappyBird::flappyObstacle::Update(float deltaTime)
{

	setPosition(Vector2f(position.x - deltaTime * obstacleSpeed * 10.0f, position.y));
	if (worldPosition().x <= -13.f * worldScale().x || (GameManager::singleton && !GameManager::singleton->inGame))
	{
		isRemoving = true;
		
	}
}

void FlappyBird::flappyObstacle::Start()
{

}
void FlappyBird::flappyObstacle::deleteMe()
{
	GameManager* obstacleMan = GameManager::singleton;
	if (obstacleMan != nullptr)
	{
		for (auto it = obstacleMan->obstacles.begin(); it != obstacleMan->obstacles.end();)
		{
			if (*it == this)
			{
				it = obstacleMan->obstacles.erase(it);
				break; // przerwij pêtlê, bo ju¿ usuniêto obiekt
			}
			else
			{
				++it;
			}
		}
	}

	delete this;
}


void FlappyBird::flappyObstacle::Draw()
{
	//cout << "width: " << outlinewidth << "  color: " << (int)color.r << endl;
	//Shapes::RectangleShape::Draw();
	renderobj.setPosition(worldPosition());
	renderobj.setRotation(isTopOne? worldRotation() +180.f: worldRotation());
	renderobj.setScale(worldScale());
	renderWindow->draw(renderobj);

}

void FlappyBird::flappyObstacle::SetProperties()
{
}

FlappyBird::flappyObstacle::flappyObstacle(GameManager* obstacleman) : Engine2D::Shapes::RectangleShape("Obstacle", Vector2f(appData->WindowSize.x + 13, -200), 26, 160, sf::Color::Red, 1)
{
	this->name = "Obstacle";
	this->tag = "kill";
	localA = 26;
	localB= 160;
	color = Color::Red;
	outlinewidth = 1;
	renderWindow = Engine::GetSingleton(false)->Window;
	Texture tx;
	renderobj.setScale(worldScale());
	tx.loadFromFile("img/obstacle.png");
	loadbitmaps(std::vector<Texture>({tx}));
	renderobj.setOrigin(renderobj.getLocalBounds().width/2.0, renderobj.getLocalBounds().height/2.0);
}

FlappyBird::flappyObstacle::~flappyObstacle()
{
	//cout << "DELETING"<<endl;
}


