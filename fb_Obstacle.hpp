#pragma once
#include "UpdatableObject.h"
#include "Collisions.h"
#include "ShapeObject.h"
#include "Engine.h"
#include "Player.h"
#include "Transform.h"
using namespace Engine2D;
namespace FlappyBird
{
	class flappyObstacle : public virtual UpdatableObject, public virtual TransformableObject, public virtual Collisions
	{
	private:
		static float obstacleSpeed;
		static int minY;
		static int maxY;
		bool isTopOne;
	public:
		virtual void Update(float deltaTime) override;
		virtual void Start() override;
		virtual void deleteMe() override;
	};
}