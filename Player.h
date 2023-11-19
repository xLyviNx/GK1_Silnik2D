#pragma once
#include "InputReader.h"
#include "Transform.h"
#include "ShapeObject.h"
#include "Collisions.h"

namespace Engine2D
{
	class Player : public virtual Shapes::RectangleShape, public InputReader, public UpdatableObject, public virtual	Collisions
	{
	protected:
		bool isTopView;
		float movementSpeed;
		float gravityForce;
		bool isGrounded;
	public:
		float jumpForce;
		bool enableGravity;
		void deleteMe() override;
		Player(string name, Vector2f position);
		void Start() override;
		virtual void Movement(Engine* engine, float deltaTime);
		void Update(float deltaTime) override;
		void KeyPressed(sf::Keyboard::Key keyPressed) override;
		virtual void PropertiesChanged() override;
		void Move(Vector2f position, Vector2f dir, bool* collided);
		void Move(Vector2f position, Vector2f dir, bool* collided, bool collisionsMoveOut);
	};
}