#include "fb_Obstacle.hpp"
float FlappyBird::flappyObstacle::obstacleSpeed = 10.0f;

void FlappyBird::flappyObstacle::Update(float deltaTime)
{

	setPosition(Vector2f(position.x - deltaTime * obstacleSpeed * 10.0f, position.y));
	if (worldPosition().x <= -13.f * worldScale().x)
	{
		deleteMe();
		cout << "JA PIERODLE";
	}
}

void FlappyBird::flappyObstacle::Start()
{
	if (isTopOne)
	{
		
	}
}

void FlappyBird::flappyObstacle::deleteMe()
{
	if (obstacleMan != NULL)
	{
		for (vector<flappyObstacle*>::iterator it = obstacleMan->obstacles.begin(); it != obstacleMan->obstacles.end(); ++it)
		{
			if (*it == this) {
				obstacleMan->obstacles.erase(it);
				break;
			}
		}
	}
	delete (flappyObstacle*)(this);
}

void FlappyBird::flappyObstacle::Draw()
{
	//cout << "width: " << outlinewidth << "  color: " << (int)color.r << endl;
	Shapes::RectangleShape::Draw();
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
	localA = 26;
	localB= 160;
	color = Color::Red;
	outlinewidth = 1;
	renderWindow = Engine::GetSingleton(false)->Window;
	this->obstacleMan = obstacleman;
	Texture tx;
	renderobj.setScale(worldScale());
	tx.loadFromFile("img/obstacle.png");
	loadbitmaps(std::vector<Texture>({tx}));
	renderobj.setOrigin(renderobj.getLocalBounds().width/2.0, renderobj.getLocalBounds().height/2.0);
}

FlappyBird::flappyObstacle::~flappyObstacle()
{
	cout << "DELETING"<<endl;
}


