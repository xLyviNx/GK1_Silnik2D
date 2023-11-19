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
		sf::Vector2f noncollide = start;
		for (float i = 0; i < distance; i += 1.0f) {
			sf::Vector2f currentPoint = start + direction * i;

			for (Collisions* collision : All) {
				if (ignore.find(collision) != ignore.end() || !collision->enabled) {
					continue;
				}

				if (collision->getGlobalBounds().contains(currentPoint)) {
					RaycastHit hit(true, collision, currentPoint, end,noncollide);
					return hit;
				}
			}
			noncollide = currentPoint;
		}

		return RaycastHit{ false, nullptr, end, end, end};
	}
	RaycastHit Collisions::RaycastBox(Collisions* self, sf::Vector2f selfPosition, sf::Vector2f end, std::set<Collisions*> ignore)
	{
		sf::Vector2f direction = end - selfPosition;
		float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= distance; // normalize the direction
		sf::Vector2f noncollide = selfPosition;
		for (float i = 0; i < distance; i += 5.0f) {
			sf::Vector2f currentPoint = selfPosition + direction * i;

			for (Collisions* collision : All) {
				if (ignore.find(collision) != ignore.end() || !collision->enabled || collision == self) {
					continue;
				}

				if (collision->getGlobalBounds().intersects(self->getGlobalBounds())) {
					RaycastHit hit(true, collision, currentPoint, end, noncollide);
					return hit;
				}
			}
			noncollide = currentPoint;
		}

		return RaycastHit{ false, nullptr, end, end, end };
	}
	RaycastHit Collisions::FindClosestNonCollidingPoint(Collisions* Target, sf::Vector2f start, sf::Vector2f end, std::set<Collisions*> ignore) {
		return RaycastHit(false, NULL, end, end, end);
	}
	static sf::Vector2f moveOutOfCollision(Collisions* coll, sf::Vector2f position) {
		sf::FloatRect tempBounds = coll->getGlobalBounds();
		tempBounds.left = position.x - tempBounds.width / 2.f; // Ustawiamy lewy górny róg tak, aby œrodek by³ na pozycji
		tempBounds.top = position.y - tempBounds.height / 2.f; // Ustawiamy górny róg tak, aby œrodek by³ na pozycji
		for (auto& other : Collisions::All) {
			if (coll == other) continue; // Pomiñ ten sam obiekt
			while (tempBounds.intersects(other->getGlobalBounds())) {
				// Przesuñ ten obiekt w dowolnym kierunku, w którym nie ma kolizji
				tempBounds.left += 1.f;
				if (tempBounds.intersects(other->getGlobalBounds())) {
					tempBounds.left -= 2.f;
					if (tempBounds.intersects(other->getGlobalBounds())) {
						tempBounds.top += 1.f;
						if (tempBounds.intersects(other->getGlobalBounds())) {
							tempBounds.top -= 2.f;
						}
					}
				}
			}
		}
		return sf::Vector2f(tempBounds.left + tempBounds.width / 2.f, tempBounds.top + tempBounds.height / 2.f); // Zwracamy œrodek, a nie lewy górny róg
	}
}
