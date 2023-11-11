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
			movement = Calculations::Vector2f_Normalize(movement);
			Vector2f goalPosition = position+ (movement * (float)(movementSpeed * 25.0) * deltaTime);
			set<Collisions*>ignores;
			ignores.insert((Collisions*)this);
			RaycastHit raycast = Collisions::Raycast(worldPosition(), goalPosition, ignores);
			goalPosition = raycast.point;
			setPosition(goalPosition);
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
			set<Collisions*>ignores;
			ignores.insert((Collisions*)this);
			RaycastHit raycast = Collisions::Raycast(worldPosition(), goalPosition, ignores);
			goalPosition = raycast.point;
			setPosition(goalPosition);
			goalPosition -= Vector2f(0, gravityForce) * deltaTime;
			raycast = Collisions::Raycast(worldPosition(), goalPosition, ignores);
			goalPosition = raycast.point;
			setPosition(goalPosition);
			isGrounded = raycast.hit;
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
