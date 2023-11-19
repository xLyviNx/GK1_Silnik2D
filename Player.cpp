#include "Player.h"
#include "Calculations.h"
void Engine2D::Player::deleteMe()
{
	delete this;
}

Engine2D::Player::Player(string name, Vector2f position) : RectangleShape(name, position, 64, 64, Color::White, 2.0), ShapeObject(name, position)
{
	movementSpeed = 5;
	enableGravity = false;
	isTopView = true;
	jumpForce = 10;
	gravityForce = 0;
	isGrounded = false;

}

void Engine2D::Player::Start()
{

}

void Engine2D::Player::Update(float deltaTime)
{
	Engine* engine = Engine::GetSingleton(false);
	if (engine)
	{
		Movement(engine, deltaTime);
	}
}
void Engine2D::Player::Movement(Engine* engine, float deltaTime)
{
	Vector2f movement(0, 0);
	if (isTopView)
	{
		if (engine->isKeyTriggered(Keyboard::W))
		{
			movement.y -= 1;
		}
		if (engine->isKeyTriggered(Keyboard::S))
		{
			movement.y += 1;
		}
		if (engine->isKeyTriggered(Keyboard::A))
		{
			movement.x -= 1;
		}
		if (engine->isKeyTriggered(Keyboard::D))
		{
			movement.x += 1;
		}
		if (Calculations::Vector2f_Magnitude(movement) > 0.0)
		{
			Vector2f movementNorm = Calculations::Vector2f_Normalize(movement);
			Vector2f goalPosition = position+ (movementNorm * (float)(movementSpeed * 25.0) * deltaTime);
			this->Move(goalPosition, movement, NULL);
		}
	}
	else
	{
		if (isGrounded || !enableGravity)
			gravityForce = 0;
		else if (enableGravity && !isGrounded)
		{
			gravityForce -= engine->Gravity * deltaTime;
		}
		if (engine->isKeyTriggered(Keyboard::A))
		{
			movement.x -= 1;
		}
		if (engine->isKeyTriggered(Keyboard::D))
		{
			movement.x += 1;
		}
		if (Calculations::Vector2f_Magnitude(movement) > 0.0 || gravityForce != 0)
		{
			Vector2f goalPosition = position + (movement * (float)(movementSpeed * 25.0) * deltaTime);
			this->Move(goalPosition, movement, NULL);
			this->Move(this->worldPosition() - Vector2f(0, gravityForce) * deltaTime, movement, &isGrounded);
		}
	}
}

void Engine2D::Player::KeyPressed(sf::Keyboard::Key keyPressed)
{
	if (keyPressed == Keyboard::Space)
	{
		if (!isTopView && isGrounded && jumpForce>0)
		{
			gravityForce += jumpForce;
		}
	}
}

void Engine2D::Player::PropertiesChanged()
{
	RectangleShape::PropertiesChanged();
}
void Engine2D::Player::Move(Vector2f position, Vector2f dir, bool* collided)
{
	this->Move(position, dir, collided, true);
}
void Engine2D::Player::Move(Vector2f position, Vector2f dir, bool* collided, bool collisionsMoveOut)
{
	set<Collisions*>ignores;
	Vector2f normalizedDirection = dir;
	sf::CircleShape cs1(3.0);

	cs1.setPosition(worldPosition());
	renderWindow->draw(cs1);
	float diagonal = sqrt(pow(getGlobalBounds().width, 2) + pow(getGlobalBounds().height, 2));
	diagonal /= 2.0;
	Vector2f startPos = worldPosition() + Vector2f(getGlobalBounds().width/2.0 * normalizedDirection.x, getGlobalBounds().height/2.0 * normalizedDirection.y);


	sf::CircleShape cs(3.0);
	renderWindow->draw(cs);
	ignores.insert((Collisions*)this);
	RaycastHit raycast = Collisions::RaycastBox((Collisions*)this, worldPosition(), position, ignores);
	cs.setPosition(position);

	position = Vector2f(raycast.pointBefore.x, raycast.pointBefore.y);
	if (raycast.hit)
	{
		Engine2D::Shapes::CircleShape* ns = new Shapes::CircleShape(position, 3, 1, Color::Transparent, Color::Red);
	}
	setPosition(position);
}
