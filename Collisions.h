#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include "Transform.h"
#include <vector>
namespace Engine2D
{
	class Collisions;
	struct RaycastHit
	{
		bool hit;
		Collisions* collidedObject;
		sf::Vector2f point;
		sf::Vector2f pointBefore;
		sf::Vector2f targetEnd;

		RaycastHit(bool hits, Collisions* collided, sf::Vector2f hpoint, sf::Vector2f end, sf::Vector2f pointBef) {
			hit = hits;
			collidedObject = collided;
			point = hpoint;
			targetEnd = end;
			pointBefore = pointBef;
		}
	};

	class Collisions
	{
	private:
		float oldAngle;
		float oldSin;
		float oldCos;
	protected:
		sf::FloatRect globalBounds;
	public:
		bool enabled;
		Collisions();
		Collisions(TransformableObject* transform);
		~Collisions();
		static std::set<Collisions*> All;
		virtual void deleteMe();
		sf::FloatRect getGlobalBounds();
		bool Collides(sf::FloatRect otherRect);
		Collisions* CollidesWithAny();
		//static Collisions* PointCollide(sf::Vector2f point);
		static Collisions* PointCollide(sf::Vector2f point, Collisions* ignoreOne);
		TransformableObject* myTransform;
		static RaycastHit Raycast(sf::Vector2f start, sf::Vector2f end, std::set<Collisions*> ignore);
		static RaycastHit RaycastBox(Collisions* self, sf::Vector2f selfPosition, sf::Vector2f end, std::set<Collisions*> ignore);
		static RaycastHit FindClosestNonCollidingPoint(Collisions* Target, sf::Vector2f start, sf::Vector2f end, std::set<Collisions*> ignore);
		virtual void OnCollisionEnter(Collisions* other);
		virtual void OnCollisionStay(Collisions* other);
		virtual void OnCollisionExit(Collisions* other);
		std::set<Collisions*> currentCollisions;
		static sf::Vector2f moveOutOfCollision(Collisions* coll, sf::Vector2f position);
		bool Collides(Collisions* other);
		bool Collides(sf::Vector2f point);
		sf::Vector2f moveOutOfCollision(Collisions* coll, sf::Vector2f position, sf::Vector2f velocity);
		bool Collides(std::vector<sf::Vector2f> corners);
		void CalculateCorners(float width, float height, float angle, const sf::Vector2f position);
		static void printCorners(const std::vector<sf::Vector2f>& corners);
		std::vector<Vector2f> myCorners;
	};

}