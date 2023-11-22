#include "Collisions.h"
#include <iostream>
#include "Engine.h"
#include "Calculations.h"
#define drawPoints false
namespace Engine2D {
	std::set<Engine2D::Collisions*> Collisions::All;
	Collisions::Collisions()
	{
		myTransform = NULL;
		Collisions::All.insert(this);
		this->currentCollisions = std::set<Collisions*>();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
		enabled = true;
	}
	Collisions::Collisions(TransformableObject* transform) : Collisions()
	{
		myTransform = transform;
	}
	Collisions::~Collisions()
	{
		Collisions::All.erase(this);
		for (Collisions* c : Collisions::All)
		{
			c->OnCollisionExit(this);
			c->currentCollisions.erase(this);
		}
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
		std::vector<sf::Vector2f> corners(self->myCorners.size());


		for (float i = 0; i < distance; i += 3.0f) {
			sf::Vector2f currentPoint = selfPosition + direction * i;
			
			for (int v = 0; v < corners.size(); v++)
			{
				corners[v] = self->myCorners[v] + direction * i;
			}
			if (drawPoints) {
				drawCorners(corners);
			}
			for (Collisions* collision : All)
			{
				if (ignore.find(collision) != ignore.end() || !collision->enabled || collision == self) {
					continue;
				}
				if (collision->Collides(corners)) {
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
	void Collisions::OnCollisionEnter(Collisions* other)
	{
	}
	void Collisions::OnCollisionStay(Collisions* other)
	{
	}
	void Collisions::OnCollisionExit(Collisions* other)
	{
	}
	sf::Vector2f Collisions::moveOutOfCollision(Collisions* coll, sf::Vector2f position) {
		std::vector<sf::Vector2f> corners = coll->myCorners; // Copy coll->myCorners
		sf::Vector2f displacement(0.f, 0.f);

		for (auto& other : Collisions::All)
		{
			if (coll == other) continue; // Skip the same object

			while (other->Collides(corners)) {
				// Calculate the center of mass for the other object
				sf::Vector2f otherCenter(0.f, 0.f);
				for (const auto& corner : other->myCorners) {
					otherCenter += corner;
				}
				otherCenter /= static_cast<float>(other->myCorners.size());

				// Calculate the displacement vector based on the position difference
				sf::Vector2f diff = position - otherCenter;
				float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);
				sf::Vector2f direction = diff / length; // Normalize the displacement vector

				// Add a small step in the direction to each corner
				for (auto& corner : corners) {
					corner += direction * 0.1f;
				}

				// Add the step to the displacement
				displacement += direction * 0.1f;
			}
		}

		return position + displacement; // Return the new position
	}


	bool Collisions::Collides(Collisions* other)
	{
		if (myCorners.size() > 0 && other->myCorners.size()>0)
		{
			//cout << myCorners.size() << endl;
			if (drawPoints) {
				drawCorners(myCorners);
			}
			for (int i = 0; i < 2; ++i) {
				const std::vector<sf::Vector2f>& corners = (i == 0) ? this->myCorners : other->myCorners;

				for (size_t j = 0; j < corners.size(); ++j) {
					sf::Vector2f edge = corners[j] - corners[(j + 1) % corners.size()];
					sf::Vector2f axis(-edge.y, edge.x); // Perpendicular to the edge

					float minA = std::numeric_limits<float>::max();
					float maxA = std::numeric_limits<float>::lowest();
					for (const auto& corner : this->myCorners) {
						float projection = Calculations::dotProduct(corner, axis);
						minA = std::min(minA, projection);
						maxA = std::max(maxA, projection);
					}

					float minB = std::numeric_limits<float>::max();
					float maxB = std::numeric_limits<float>::lowest();
					for (const auto& corner : other->myCorners) {
						float projection = Calculations::dotProduct(corner, axis);
						minB = std::min(minB, projection);
						maxB = std::max(maxB, projection);
					}

					if (maxA < minB || maxB < minA)
						return false; // No collision
				}
			}

			return true; // Collision

		}
		return false;
	}

	bool Collisions::Collides(sf::Vector2f point)
	{
		if (myCorners.size() > 0)
		{
			for (size_t j = 0; j < myCorners.size(); ++j) {
				sf::Vector2f edge = myCorners[j] - myCorners[(j + 1) % myCorners.size()];
				sf::Vector2f axis(-edge.y, edge.x); // Perpendicular to the edge

				float minA = std::numeric_limits<float>::max();
				float maxA = std::numeric_limits<float>::lowest();
				for (const auto& corner : this->myCorners) {
					float projection = Calculations::dotProduct(corner, axis);
					minA = std::min(minA, projection);
					maxA = std::max(maxA, projection);
				}

				float minB = std::numeric_limits<float>::max();
				float maxB = std::numeric_limits<float>::lowest();
				float projection = Calculations::dotProduct(point, axis);
				minB = std::min(minB, projection);
				maxB = std::max(maxB, projection);

				if (maxA < minB || maxB < minA)
					return false; // No collision
			}

			return true; // Collision
		}
		return false;
	}
	sf::Vector2f Collisions::moveOutOfCollision(Collisions* coll, sf::Vector2f position, sf::Vector2f velocity) {
		if (Calculations::Vector2f_Magnitude(velocity) <= 0.0)
			return moveOutOfCollision(coll, position);
		std::vector<sf::Vector2f> corners = coll->myCorners; // Copy coll->myCorners
		sf::Vector2f displacement(0.f, 0.f);

		for (auto& other : Collisions::All)
		{
			if (coll == other) continue; // Skip the same object

			while (other->Collides(corners)) {
				// Calculate the displacement vector based on the velocity
				sf::Vector2f direction = -velocity / std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y); // Normalize the velocity vector and reverse it

				// Add a small step in the direction to each corner
				for (auto& corner : corners) {
					corner += direction * 0.1f;
				}

				// Add the step to the displacement
				displacement += direction * 0.1f;
			}
		}

		return position + displacement; // Return the new position
	}

	bool Collisions::Collides(std::vector<sf::Vector2f> inputCorners)
	{
		if (myCorners.size() > 0 && inputCorners.size() > 0)
		{
			for (int i = 0; i < 2; ++i) {
				const std::vector<sf::Vector2f>& corners = (i == 0) ? this->myCorners : inputCorners;

				for (size_t j = 0; j < corners.size(); ++j) {
					sf::Vector2f edge = corners[j] - corners[(j + 1) % corners.size()];
					sf::Vector2f axis(-edge.y, edge.x); // Perpendicular to the edge

					float minA = std::numeric_limits<float>::max();
					float maxA = std::numeric_limits<float>::lowest();
					for (const auto& corner : this->myCorners) {
						float projection = Calculations::dotProduct(corner, axis);
						minA = std::min(minA, projection);
						maxA = std::max(maxA, projection);
					}

					float minB = std::numeric_limits<float>::max();
					float maxB = std::numeric_limits<float>::lowest();
					for (const auto& corner : corners) {
						float projection = Calculations::dotProduct(corner, axis);
						minB = std::min(minB, projection);
						maxB = std::max(maxB, projection);
					}

					if (maxA < minB || maxB < minA)
						return false; // No collision
				}
			}

			return true; // Collision
		}
		return false;
	}

	void Collisions::CalculateCorners(float width, float height, float angle, const sf::Vector2f position)
	{
		if (oldAngle != angle) 
		{
			float radian = angle * M_PI / 180.0f;
			oldCos = cos(radian);
			oldSin = sin(radian);
			oldAngle = angle;
		}
		float halfWidth = width / 2.0f;
		float halfHeight = height / 2.0f;

		std::vector<sf::Vector2f> corners(4);
		if (fmodf(angle, 360) != 0 && fmodf(angle, 360) != 180)
		{
			corners[0] = sf::Vector2f(position.x + halfWidth * oldCos - halfHeight * oldSin, position.y + halfWidth * oldSin + halfHeight * oldCos);
			corners[1] = sf::Vector2f(position.x - halfWidth * oldCos - halfHeight * oldSin, position.y - halfWidth * oldSin + halfHeight * oldCos);
			corners[2] = sf::Vector2f(position.x - halfWidth * oldCos + halfHeight * oldSin, position.y - halfWidth * oldSin - halfHeight * oldCos);
			corners[3] = sf::Vector2f(position.x + halfWidth * oldCos + halfHeight * oldSin, position.y + halfWidth * oldSin - halfHeight * oldCos);
		}
		else
		{
			corners[0] = sf::Vector2f(position.x + halfWidth, position.y + halfHeight); // prawy dolny róg
			corners[1] = sf::Vector2f(position.x - halfWidth, position.y + halfHeight); // lewy dolny róg
			corners[2] = sf::Vector2f(position.x - halfWidth, position.y - halfHeight); // lewy górny róg
			corners[3] = sf::Vector2f(position.x + halfWidth, position.y - halfHeight); // prawy górny róg
		}
		
		/*if (halfWidth < 50)
		{
			cout << "   A: " << halfWidth << " B: " << halfHeight << endl;
			cout << "   CORNER: " << endl;
			printCorners(corners);
			cout << "   ======== " << endl;

		}*/
		this->myCorners = corners;
	}
	void Collisions::printCorners(const std::vector<sf::Vector2f>& corners) {
		for (size_t i = 0; i < corners.size(); ++i) {
			std::cout << "Corner " << i << ": (" << corners[i].x << ", " << corners[i].y << ")\n";
		}
	}
	void Collisions::drawCorners(const std::vector<sf::Vector2f>& myCorners)
	{
		sf::CircleShape a(3);
		a.setPosition(myCorners[0]);
		a.setFillColor(Color::Red);
		Engine::GetSingleton(false)->Window->draw(a);


		sf::CircleShape b(3);
		b.setPosition(myCorners[1]);
		b.setFillColor(Color::Red);
		Engine::GetSingleton(false)->Window->draw(b);

		sf::CircleShape c(3);
		c.setPosition(myCorners[2]);
		c.setFillColor(Color::Red);
		Engine::GetSingleton(false)->Window->draw(c);

		sf::CircleShape d(3);
		d.setPosition(myCorners[3]);
		d.setFillColor(Color::Red);
		Engine::GetSingleton(false)->Window->draw(d);
	}
}

