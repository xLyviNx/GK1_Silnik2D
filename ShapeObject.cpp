#include "ShapeObject.h"
#include "PrimitiveRenderer.h"
namespace Engine2D
{
	ShapeObject::ShapeObject(Vector2f position)
		: TransformableObject(position)
	{
		Engine* engine = Engine::GetSingleton(false);
		if (engine)
		{
			renderWindow = engine->Window;
		}
		cout << "SHAPE CONSTRUCT POSITION: " << position.x << " " << position.y << endl;
		this->position = position;
		this->name = "Shape Object";
	}

	ShapeObject::ShapeObject(std::string name, Vector2f position)
		: TransformableObject(name, position)
	{
		Engine* engine = Engine::GetSingleton(false);
		if (engine)
		{
			renderWindow = engine->Window;
		}
		cout << "SHAPE CONSTRUCT POSITION: " << position.x << " " << position.y << endl;
		this->position = position;
		this->name = name;
	}

	void ShapeObject::deleteMe()
	{
		delete (ShapeObject*)this;
	}
	void Shapes::RectangleShape::PropertiesChanged()
	{

		worldA = localA * this->worldScale().x;
		worldB = localB * this->worldScale().y;
		rectShape.setPosition(worldPosition());
		rectShape.setSize(Vector2f(worldA, worldB));
		sf::FloatRect bounds = rectShape.getLocalBounds();
		rectShape.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
		rectShape.setOutlineColor(color);
		rectShape.setOutlineThickness(width);
		rectShape.setFillColor(fillColor);
		rectShape.setRotation(this->rotation);
	}
	Shapes::RectangleShape::RectangleShape(Vector2f position, float A, float B, Color color, float width)
		: ShapeObject("RectangleShape Object", position) {
		this->fillColor = Color::Transparent;
		cout << "RECTANGLE CONSTRUCT POSITION: " << position.x << " " << position.y << endl;
		this->width = width;
		localA = A;
		localB = B;
		this->color = color;
		PropertiesChanged();
	}

	Shapes::RectangleShape::RectangleShape(Vector2f position, float A, float B, Color color, Color fillColor, float width) : RectangleShape(position, A, B, color, width)
	{
		this->fillColor = fillColor;
	}

	Shapes::RectangleShape::RectangleShape(std::string name, Vector2f position, float A, float B, Color color, float width) : ShapeObject(name, position)
	{
		this->fillColor = Color::Transparent;
		this->width = width;
		localA = A;
		localB = B;
		this->color = color;
		PropertiesChanged();
	}

	Shapes::RectangleShape::RectangleShape(std::string name, Vector2f position, float A, float B, Color color, Color fillColor, float width) : RectangleShape(name,position,A,B,color,width)
	{
		this->fillColor = fillColor;
	}

	void Shapes::RectangleShape::deleteMe()
	{
		delete (RectangleShape*)this;
	}
	void Shapes::RectangleShape::Draw()
	{
		//rysowanie rectangle
		if (renderWindow)
			renderWindow->draw(rectShape);
	}
	void Shapes::CircleShape::PropertiesChanged()
	{
		worldRadius = localRadius * this->worldScale().x;
		//tutaj
	}
	void Shapes::CircleShape::deleteMe()
	{
		delete(this);
	}
	void Shapes::CircleShape::Draw()
	{
		//rysowanie kolka
	}
	Shapes::CircleShape::CircleShape(Vector2f position, float R, Color color) : ShapeObject("CircleShape Object", position)
	{
		this->localRadius = R;
		this->color = color;
		PropertiesChanged();
	}
	Shapes::CircleShape::CircleShape(std::string name, Vector2f position, float R, Color color) : ShapeObject(name, position)
	{
		this->localRadius = R;
		this->color = color;
		PropertiesChanged();
	}
}