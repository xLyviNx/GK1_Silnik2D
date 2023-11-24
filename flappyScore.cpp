#include "flappyScore.hpp"

void FlappyBird::flappyScore::Draw()
{
	rectShape.setPosition(worldPosition());
	//Engine::GetSingleton(false)->Window->draw(rectShape);
}

void FlappyBird::flappyScore::deleteMe()
{
	delete this;
}

void FlappyBird::flappyScore::OnCollisionEnter(Collisions* other)
{
	
	if (other->myTransform)
	{
		if (other->myTransform->tag == "Player")
		{
			isRemoving = true;
			if (GameManager::singleton)
			{
				GameManager::singleton->points++;
			}
		}
	}
}

FlappyBird::flappyScore::flappyScore(Vector2f pos) : RectangleShape("Point", pos, 50, GameManager::gap/2.0, Color::Green, 3.f)
{
	outlinewidth = 3;
	color = Color::Green;
	ChangeSize(50, GameManager::gap/2.0);
	setPosition(pos);
	tag = "ignore";
}
