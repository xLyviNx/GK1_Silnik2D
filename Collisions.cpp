#include "Collisions.h"
#include <iostream>
#include "Engine.h"
#include "Calculations.h"
#define drawPoints false
namespace Engine2D {
	std::vector<Engine2D::Collisions*> Collisions::All;
	Collisions::Collisions()
	{
		myTransform = NULL;
		Collisions::All.push_back(this);
		this->currentCollisions = std::vector<Collisions*>();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
		enabled = true;
	}
	Collisions::Collisions(TransformableObject* transform) : Collisions()
	{
		myTransform = transform;
	}
	Collisions::~Collisions()
	{
		for (vector<Collisions*>::iterator it = Collisions::All.begin(); it != Collisions::All.end(); ++it)
		{
			if (*it == this) {
				*it = NULL;
				break;
			}
		}
		for (Collisions* c : Collisions::All)
		{
			if (c != NULL) {
				c->OnCollisionExit(this);
				for (vector<Collisions*>::iterator it = c->currentCollisions.begin(); it != c->currentCollisions.end(); ++it)
				{
					if (*it == this) {
						*it = NULL;
						break;
					}
				}
			}
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

			for (Collisions* collision : All) 
			{
				if (collision == NULL)
					continue;
				if (ignore.find(collision) != ignore.end() || !collision->enabled) {
					continue;
				}
				if (collision->Collides(end)) {
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


		for (float i = 0; i < distance; i += 0.5f) {
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
				if (collision == NULL)
					continue;
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
			return Collides(other->myCorners);
		}
		return false;
	}

	bool Collisions::Collides(sf::Vector2f point)
	{
		if (myCorners.size() > 0)
		{
			for (size_t j = 0; j < myCorners.size(); ++j) {
				sf::Vector2f edge = myCorners[j] - myCorners[(j + 1) % myCorners.size()];
				sf::Vector2f axis(-edge.y, edge.x);

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
					return false;
			}

			return true; 
		}
		return false;
	}
	sf::Vector2f Collisions::moveOutOfCollision(Collisions* coll, sf::Vector2f position, sf::Vector2f velocity) {
		if (Calculations::Vector2f_Magnitude(velocity) <= 0.0)
			return moveOutOfCollision(coll, position);
		std::vector<sf::Vector2f> corners = coll->myCorners;
		sf::Vector2f displacement(0.f, 0.f);

		for (auto& other : Collisions::All)
		{
			if (coll == other) continue;

			while (other->Collides(corners)) {
				sf::Vector2f direction = -velocity / std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y); // Normalize the velocity vector and reverse it

				for (auto& corner : corners) {
					corner += direction * 0.1f;
				}

				displacement += direction * 0.1f;
			}
		}

		return position + displacement; // Return the new position
	}

	bool Collisions::Collides(std::vector<sf::Vector2f> inputCorners)
	{
		if (myCorners.size() > 0 && inputCorners.size() > 0)
		{
			if (drawPoints) {
				drawCorners(myCorners);
			}
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
					for (const auto& corner : inputCorners) {
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
			corners[0] = sf::Vector2f(position.x + halfWidth, position.y + halfHeight); // prawy dolny r�g
			corners[1] = sf::Vector2f(position.x - halfWidth, position.y + halfHeight); // lewy dolny r�g
			corners[2] = sf::Vector2f(position.x - halfWidth, position.y - halfHeight); // lewy g�rny r�g
			corners[3] = sf::Vector2f(position.x + halfWidth, position.y - halfHeight); // prawy g�rny r�g
		}
		/*sf::Vector2f middle1 = 0.5f * (corners[0] + corners[1]);
		sf::Vector2f middle2 = 0.5f * (corners[1] + corners[2]);
		sf::Vector2f middle3 = 0.5f * (corners[2] + corners[3]);
		sf::Vector2f middle4 = 0.5f * (corners[3] + corners[0]);
		std::vector<sf::Vector2f> middles{middle1,middle2,middle3,middle4};

		bottom = middle1;
		left = middle2;
		top = middle3;
		right = middle4;

		for (int i = 0; i < 4; i++)
		{
			if (middles[i].y < top.y)
			{
				top = middles[i];
			}
			if (middles[i].x < left.x)
			{
				left = middles[i];
			}
			if (middles[i].x > right.x)
			{
				right = middles[i];
			}
			if (middles[i].y > bottom.y)
			{
				bottom = middles[i];
			}
		}
		*/
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
		for (sf::Vector2f corner : myCorners) 
		{
			sf::CircleShape a(3);
			a.setPosition(myCorners[0]);
			a.setFillColor(Color::Red);
			Engine::GetSingleton(false)->Window->draw(a);
		}
	}
}

