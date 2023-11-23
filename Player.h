#pragma once
#include "InputReader.h"
#include "Transform.h"
#include "ShapeObject.h"
#include "Collisions.h"

namespace Engine2D
{
	class Player : public virtual Shapes::RectangleShape, public InputReader, public UpdatableObject, public virtual Collisions
	{
	private:
		bool jumped;

	protected:
		bool isTopView;
		float movementSpeed;
		float gravityForce;
		bool isGrounded;
		Vector2f movement;
		
	public:
		float jumpForce;
		bool enableGravity;
		virtual void deleteMe() override;
		Player(string name, Vector2f position);
		virtual void Start() override;
		virtual void Movement(Engine* engine, float deltaTime);
		virtual void Update(float deltaTime) override;
		virtual void KeyReleased(sf::Keyboard::Key keyReleased) override;
		virtual void KeyPressed(sf::Keyboard::Key keyPressed) override;
		virtual void OnCollisionEnter(Collisions* col) override;
		virtual void OnCollisionStay(Collisions* col) override;
		virtual void OnCollisionExit(Collisions* col) override;
		bool canJumpMidAir;
		void Move(Vector2f position, Vector2f dir, bool* collided);
		void Move(Vector2f position, Vector2f dir, bool* collided, bool collisionsMoveOut);
		virtual void Draw() override;
	};
}