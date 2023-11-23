#pragma once
#include "UpdatableObject.h"
#include "Collisions.h"
#include "ShapeObject.h"
#include "Engine.h"
#include "Player.h"
#include "GameManager.hpp"
#include "Transform.h"
#include "BitmapHandler.h"
using namespace Engine2D;
namespace FlappyBird
{
	class GameManager;
	class flappyObstacle : public virtual TransformableObject, public virtual Collisions, public virtual Shapes::RectangleShape, public virtual BitmapObject, public virtual UpdatableObject
	{
	private:
		GameManager* obstacleMan;
		static float obstacleSpeed;
		static int minY;
		static int maxY;
	public:
		bool isTopOne;
		virtual void Update(float deltaTime) ;
		virtual void Start() ;
		virtual void deleteMe() override;
		void Draw() override;
		void SetProperties();
		flappyObstacle(GameManager* obstacleman);
		~flappyObstacle();
	};
}