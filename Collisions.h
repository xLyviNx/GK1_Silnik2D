#pragma once
#include <SFML/Graphics.hpp>
#include <set>
namespace Engine2D
{
	class Collisions;
	struct RaycastHit
	{
		bool hit;
		Collisions* collidedObject;
		sf::Vector2f point;

		RaycastHit(bool hits, Collisions* collided, sf::Vector2f hpoint) {
			hit = hits;
			collidedObject = collided;
			point = hpoint;
		}
	};

	class Collisions
	{
	protected:
		sf::FloatRect globalBounds;
	public:
		bool enabled;
		Collisions();
		~Collisions();
		static std::set<Collisions*> All;
		virtual void deleteMe();
		sf::FloatRect getGlobalBounds();
		bool Collides(sf::FloatRect otherRect);
		Collisions* CollidesWithAny();
		//static Collisions* PointCollide(sf::Vector2f point);
		static Collisions* PointCollide(sf::Vector2f point, Collisions* ignoreOne);

		static RaycastHit Raycast(sf::Vector2f start, sf::Vector2f end, std::set<Collisions*> ignore);
	};

}