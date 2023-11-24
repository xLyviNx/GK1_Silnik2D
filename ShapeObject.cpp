#include "ShapeObject.h"
#include "PrimitiveRenderer.h"
namespace Engine2D
{
	ShapeObject::ShapeObject() : Collisions()
	{
		myTransform = (TransformableObject*)myTransform;
	}
	ShapeObject::ShapeObject(Vector2f position)
		: TransformableObject(position), Collisions((TransformableObject*)this)
	{
		Engine* engine = Engine::GetSingleton(false);
		if (engine)
		{
			renderWindow = engine->Window;
		}
		//cout << "SHAPE CONSTRUCT POSITION: " << position.x << " " << position.y << endl;
		this->position = position;
		this->name = "Shape Object";
	}

	ShapeObject::ShapeObject(std::string name, Vector2f position)
		: TransformableObject(name, position), Collisions((TransformableObject*)this)
	{
		Engine* engine = Engine::GetSingleton(false);
		if (engine)
		{
			renderWindow = engine->Window;
		}
		//cout << "SHAPE CONSTRUCT POSITION: " << position.x << " " << position.y << endl;
		this->position = position;
		this->name = name;
		visible = true;
		//printf("ADDRESS: %p\n NAME: ", myTransform);
		//cout << name << endl;
	}

	void ShapeObject::deleteMe()
	{
		delete (ShapeObject*)this;
	}
	void ShapeObject::Draw()
	{
	}
	void Shapes::RectangleShape::PropertiesChanged()
	{
		worldA = localA * this->worldScale().x;
		worldB = localB * this->worldScale().y;
		
		rectShape.setSize(Vector2f(worldA, worldB));
		sf::FloatRect bounds = rectShape.getLocalBounds();
		rectShape.setOrigin(rectShape.getSize().x / 2, rectShape.getSize().y / 2);
		rectShape.setOutlineColor(color);
		rectShape.setOutlineThickness(outlinewidth);
		rectShape.setFillColor(fillColor);
		//rectShape.setRotation(this->worldRotation());
		globalBounds = rectShape.getGlobalBounds();
		this->bounds = rectShape.getSize();
		this->CalculateCorners(worldA, worldB, this->worldRotation(), this->worldPosition());
		myTransform = (TransformableObject*)this;

	}
	Shapes::RectangleShape::RectangleShape(Vector2f position, float A, float B, Color color, float width)
		: ShapeObject("RectangleShape Object", position) {
		this->fillColor = Color::Transparent;
		//cout << "RECTANGLE CONSTRUCT POSITION: " << position.x << " " << position.y << endl;
		this->outlinewidth = width;
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
		this->outlinewidth = width;
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
		{
			rectShape.setPosition(worldPosition());
			rectShape.setRotation(this->worldRotation());
			rectShape.setFillColor(fillColor);
			rectShape.setOutlineColor(color);
			renderWindow->draw(rectShape);
		}
		//drawCorners(std::vector<sf::Vector2f>({ top }));
	}
	void Shapes::RectangleShape::ChangeSize(float A, float B)
	{
		localA = A;
		localB = B;
		PropertiesChanged();
	}
	void Shapes::CircleShape::PropertiesChanged()
	{
		worldRadius = localRadius * this->worldScale().x;
		circleShape.setRadius(worldRadius);
		sf::FloatRect bounds = circleShape.getLocalBounds();
		circleShape.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
		circleShape.setOutlineColor(color);
		circleShape.setOutlineThickness(width);
		circleShape.setFillColor(fillColor);
		globalBounds = circleShape.getGlobalBounds();
		myTransform = (TransformableObject*)this;

	}
	void Shapes::CircleShape::deleteMe()
	{
		delete(this);
	}
	void Shapes::CircleShape::Draw()
	{
		//rysowanie kolka
		if (renderWindow)
		{
			circleShape.setPosition(worldPosition());
			circleShape.setRotation(this->worldRotation());
			renderWindow->draw(circleShape);
		}
	}
	
	Shapes::CircleShape::CircleShape(Vector2f position, float Rad, float width, Color color, Color fillColor) : ShapeObject("CircleShape Object", position)
	{
		this->localRadius = Rad;
		this->color = color;
		this->fillColor = fillColor;
		this->width = width;
		PropertiesChanged();
	}
	Shapes::CircleShape::CircleShape(std::string name, Vector2f position, float R, Color color) : ShapeObject(name, position)
	{
		this->localRadius = R;
		this->color = color;
		PropertiesChanged();
		//cout << "bb";
	}
}