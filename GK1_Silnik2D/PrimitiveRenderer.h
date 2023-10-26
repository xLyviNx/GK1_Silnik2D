#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
using namespace std;
class PrimitiveRenderer
{
public:
	sf::Color Color;
	float Width;
	void DrawSingleLine(sf::Vector2f A, sf::Vector2f B);
	virtual void Draw();
	virtual void DrawSFML(float angle);
	void DrawSingleLineSFML(sf::Vector2f posA, sf::Vector2f posB,float angle);
	void DrawCircle(sf::Vector2f center, float radius);
	void DrawEllipse(sf::Vector2f center, float RX, float RY);
	PrimitiveRenderer(sf::Color color, float width);
		void PointLine(std::vector < sf::Vector2f > points);
	
};

class LineRenderer : public PrimitiveRenderer
{
public:
	sf::Vector2f posA;
	sf::Vector2f posB;
	void Draw() override;
	void DrawSFML(float angle) override;
	LineRenderer(sf::Color color, float width, sf::Vector2f positionA, sf::Vector2f positionB);
};