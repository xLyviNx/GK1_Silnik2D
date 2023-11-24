#pragma once
#include "GameManager.hpp"
#include "Collisions.h"
using namespace Engine2D;
namespace FlappyBird {
	class flappyScore : public virtual Shapes::RectangleShape, public virtual Collisions
	{
	public:
		void Draw() override;
		void deleteMe();
		void OnCollisionEnter(Collisions* other) override;
		flappyScore(Vector2f pos);
	};
}
