#include "Collisions.h"
#include <iostream>

namespace Engine2D {
	std::set<Engine2D::Collisions*> Collisions::All;
	Collisions::Collisions()
	{
		Collisions::All.insert(this);
		enabled = true;
	}
	Collisions::~Collisions()
	{
		Collisions::All.erase(this);
	}
	void Collisions::deleteMe()
	{
		delete this;
	}

	sf::FloatRect Collisions::getGlobalBounds()
	{
		return globalBounds;
	}

	bool Collisions::Collides(sf::FloatRect otherRect)
	{
		return otherRect.intersects(globalBounds);
	}
	Collisions* Collisions::CollidesWithAny() {
		for (Collisions* collision : All) {
			if (collision == this || !collision->enabled) {
				continue;
			}

			if (this->getGlobalBounds().intersects(collision->getGlobalBounds())) {
				return collision;
			}
		}

		return nullptr; // no collision
	}
	Collisions* Collisions::PointCollide(sf::Vector2f point, Collisions* ignoreOne) {
		for (Collisions* collision : All) {
			if (collision == ignoreOne || !collision->enabled) {
				continue;
			}

			if (collision->getGlobalBounds().contains(point)) {
				return collision;
			}
		}
		return nullptr; // return null if no collision
	}

	RaycastHit Collisions::Raycast(sf::Vector2f start, sf::Vector2f end, std::set<Collisions*> ignore)
	{
		sf::Vector2f direction = end - start;
		float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= distance; // normalize the direction

		for (float i = 0; i < distance; i += 1.0f) {
			sf::Vector2f currentPoint = start + direction * i;

			for (Collisions* collision : All) {
				if (ignore.find(collision) != ignore.end() || !collision->enabled) {
					continue;
				}

				if (collision->getGlobalBounds().contains(currentPoint)) {
					RaycastHit hit(true, collision, currentPoint, end);
					return hit;
				}
			}
		}

		return RaycastHit{ false, nullptr, end, end };
	}
	RaycastHit Collisions::FindClosestNonCollidingPoint(Collisions* Target, sf::Vector2f start, sf::Vector2f end, std::set<Collisions*> ignore) {
		sf::Vector2f direction = end - start;
		float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= distance;
		sf::FloatRect targetBounds = Target->getGlobalBounds();

		for (float d = 0; d <= distance; d += 1.0f) {
			sf::Vector2f point = start + d * direction;
			targetBounds.left = point.x - targetBounds.width / 2; // uwzglêdniamy przesuniêcie
			targetBounds.top = point.y - targetBounds.height / 2; // uwzglêdniamy przesuniêcie
			for (Collisions* obj : Collisions::All) {
				if (obj != Target && ignore.find(obj) == ignore.end() && obj->getGlobalBounds().intersects(targetBounds)) {
					return RaycastHit(true, obj, point, start);
				}
			}
		}
		return RaycastHit(false, nullptr, end, start); // zwraca RaycastHit z punktem koñcowym, jeœli nie mo¿na znaleŸæ punktu bez kolizji
	}


}