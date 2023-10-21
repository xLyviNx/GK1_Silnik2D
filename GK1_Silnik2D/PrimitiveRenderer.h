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
	virtual void DrawSFML();
	void DrawSingleLineSFML();
	PrimitiveRenderer(sf::Color color, float width);
};

class LineRenderer : public PrimitiveRenderer
{
public:
	sf::Vector2f posA;
	sf::Vector2f posB;
	void Draw() override;
	LineRenderer(sf::Color color, float width, sf::Vector2f positionA, sf::Vector2f positionB);
};