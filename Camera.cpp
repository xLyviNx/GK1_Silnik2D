#include "Camera.h"
#include "Engine.h"
Engine2D::Camera* Engine2D::Camera::current = NULL;
Engine2D::Camera::Camera(string name, Vector2f position) : TransformableObject(name, position)
{
	return;
	if (!current)
		current = this;
}

void Engine2D::Camera::Update(float deltaTime)
{
	Engine* engine = Engine::GetSingleton(false);
	if (engine)
	{
		if (engine->isKeyTriggered(Keyboard::R))
		{
			this->Rotate(10 * deltaTime);
		}
		if (engine->isKeyTriggered(Keyboard::E))
		{
			this->Translate(Vector2f(10, 0) * deltaTime);
		}
	}
}

void Engine2D::Camera::deleteMe()
{
	delete this;
}

void Engine2D::Camera::KeyPressed(sf::Keyboard::Key keyPressed)
{
	if (keyPressed == Keyboard::N)
		current = this;
}
