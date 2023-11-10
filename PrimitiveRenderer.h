#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#define M_PI 3.14159265358979323846

using namespace std;
class PrimitiveRenderer
{
protected:
public:
	sf::Color Color;
	float Width;
	static void DrawSingleLine(sf::RenderWindow* renderWindow, sf::Vector2f A, sf::Vector2f B, float Width, sf::Color Color);
	static void DrawSingleLineSFML(sf::Vector2f posA, sf::Vector2f posB, float angle, sf::Color Color);
	static void DrawCircle(sf::Vector2f center, float radius, sf::Color color);
	static void DrawCircle(sf::RenderWindow* renderWindow, sf::Vector2f center, std::vector<sf::Vector2f> points, sf::Color color);
	static void PointLine(sf::RenderWindow* renderWindow, std::vector<sf::Vector2f>* points, float Width, sf::Color Color);
	static void PointLine(sf::RenderWindow* renderWindow, sf::Vector2f points[], int pointsCount, float Width, sf::Color Color);
	static void DrawEllipse(sf::Vector2f center, float RX, float RY, sf::Color color);
	PrimitiveRenderer() : Color(sf::Color::White), Width(1.0f) {};
	PrimitiveRenderer(sf::Color color, float width);
};

class Point2D : public PrimitiveRenderer
{
public:
	sf::Vector2f Position;
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f newPos);
	void DrawPointSFML();
	
	Point2D(sf::Color color, float width, sf::Vector2f position);
};