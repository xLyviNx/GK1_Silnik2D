#include "ShapeObject.h"
namespace Engine2D
{
	ShapeObject::ShapeObject(Vector2f position) : TransformableObject("Shape Object", position)
	{

	}
	ShapeObject::ShapeObject(std::string name, Vector2f position) : TransformableObject(name, position)
	{

	}
	void Shapes::RectangleShape::Draw()
	{
		if (renderWindow != NULL)
		{
			PrimitiveRenderer::PointLine(renderWindow, points, 4, width, color);
		}
	}
	void Shapes::RectangleShape::PropertiesChanged()
	{
		worldA = localA * this->worldScale().x;
		worldB = localB * this->worldScale().y;
		points[0] = Vector2f(worldPosition().x - worldA / 2.0, worldPosition().y - worldB / 2.0);
		points[1] = Vector2f(worldPosition().x - worldA / 2.0, worldPosition().y + worldB / 2.0);
		points[2] = Vector2f(worldPosition().x + worldA / 2.0, worldPosition().y + worldB / 2.0);
		points[3] = Vector2f(worldPosition().x + worldA / 2.0, worldPosition().y - worldB / 2.0);
	}
	Shapes::RectangleShape::RectangleShape(Vector2f position, float A, float B, Color color, float width) : ShapeObject("RectangleShape Object", position)
	{
		Engine* engine = Engine::GetSingleton(false);
		if (engine)
		{
			renderWindow = engine->Window;
		}
		this->width = width;
		localA = A;
		localB = B;
		this->color = color;
		PropertiesChanged();
	}



}