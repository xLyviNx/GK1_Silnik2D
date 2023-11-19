#include "spriteObject.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Calculations.h"
#include "BitmapHandler.h"
#include "Player.h"

namespace Engine2D
{

	void SpriteObject::setTexture()
	{
		//loadFromFile("sprite sheet.png");
		// texture.loadFromImage(bitmap);
	}
	void SpriteObject::Movement(Engine* engine, float deltaTime)
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
				Vector2f goalPosition = position + (movement * (float)(movementSpeed * 25.0) * deltaTime);
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
}
