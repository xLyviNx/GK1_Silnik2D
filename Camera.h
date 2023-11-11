#pragma once
#include "UpdatableObject.h"
#include "Transform.h"
#include "InputReader.h"
namespace Engine2D
{
	class Camera : public TransformableObject, public virtual UpdatableObject, public InputReader
	{
	public:
		static Camera* current;
		Camera(string name, Vector2f position);
		void Update(float deltaTime) override;
		void deleteMe() override;
		void KeyPressed(sf::Keyboard::Key keyPressed) override;

	};
}