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
	void ShapeObject::Draw()
	{
		if (renderWindow)
			renderWindow->draw(vertices);
	}
	void Shapes::RectangleShape::PropertiesChanged()
	{

		worldA = localA * this->worldScale().x;
		worldB = localB * this->worldScale().y;
		//cout << "POSITION: " << worldPosition().x << " " << worldPosition().y << endl;
		points[0] = Vector2f(worldPosition().x - worldA / 2.0, worldPosition().y - worldB / 2.0);
		points[1] = Vector2f(worldPosition().x - worldA / 2.0, worldPosition().y + worldB / 2.0);
		points[2] = Vector2f(worldPosition().x + worldA / 2.0, worldPosition().y + worldB / 2.0);
		points[3] = Vector2f(worldPosition().x + worldA / 2.0, worldPosition().y - worldB / 2.0);
		points[4] = points[0];
		vertices = VertexArray(sf::Points);

		for (int i = 0; i < 4; ++i)
		{
			double rad = Engine::AngleToRad(this->rotation);
			int x1 = points[i].x;
			int y1 = points[i].y;
			int x2 = points[i + 1].x;
			int y2 = points[i + 1].y;

			int x1r = (cos(rad) * (x1 - worldPosition().x) - sin(rad) * (y1 - worldPosition().y) + worldPosition().x);
			int y1r = (sin(rad) * (x1 - worldPosition().x) + cos(rad) * (y1 - worldPosition().y) + worldPosition().y);
			int x2r = (cos(rad) * (x2 - worldPosition().x) - sin(rad) * (y2 - worldPosition().y) + worldPosition().x);
			int y2r = (sin(rad) * (x2 - worldPosition().x) + cos(rad) * (y2 - worldPosition().y) + worldPosition().y);

			x1 = x1r;
			y1 = y1r;
			x2 = x2r;
			y2 = y2r;

			int dx = abs(x2 - x1);
			int dy = abs(y2 - y1);
			int sx = (x1 < x2) ? 1 : -1;
			int sy = (y1 < y2) ? 1 : -1;
			int err = dx - dy;
			while (x1 != x2 || y1 != y2)
			{
				for (int i = 0; i < width; i++)
				{
					for (int j = 0; j < width; j++)
					{
						sf::Vertex pixel(sf::Vector2f(x1 + i, y1 + j), color);
						vertices.append(pixel);
					}
				}
				int err2 = 2 * err;
				if (err2 > -dy)
				{
					err -= dy;
					x1 += sx;
				}
				if (err2 < dx)
				{
					err += dx;
					y1 += sy;
				}
			}
		}
	}
	Shapes::RectangleShape::RectangleShape(Vector2f position, float A, float B, Color color, float width)
		: ShapeObject("RectangleShape Object", position) {
		cout << "RECTANGLE CONSTRUCT POSITION: " << position.x << " " << position.y << endl;
		this->width = width;
		localA = A;
		localB = B;
		this->color = color;
		PropertiesChanged();
	}

	Shapes::RectangleShape::RectangleShape(std::string name, Vector2f position, float A, float B, Color color, float width) : ShapeObject(name, position)
	{
		this->width = width;
		localA = A;
		localB = B;
		this->color = color;
		PropertiesChanged();
	}

	void Shapes::RectangleShape::deleteMe()
	{
		delete (RectangleShape*)this;
	}
	void Shapes::CircleShape::PropertiesChanged()
	{
		worldRadius = localRadius * this->worldScale().x;
		vertices.clear();
		vertices = VertexArray(sf::Points);
		float step = 1.0 / worldRadius;
		Vector2f center = worldPosition();
		for (float a = 0; a < M_PI / 4; a += step)
		{
			float cosa = cos(a);
			float sina = sin(a);

			float x1 = center.x + worldRadius * cosa;
			float y1 = center.y + worldRadius * sina;
			vertices.append(sf::Vertex(Vector2f(x1, y1), color));
			x1 = center.x + worldRadius * cosa;
			y1 = center.y - worldRadius * sina;
			vertices.append(sf::Vertex(Vector2f(x1, y1), color));

			x1= center.x - worldRadius * cosa;
			y1 = center.y + worldRadius * sina;
			vertices.append(sf::Vertex(Vector2f(x1, y1), color));

			x1 = center.x - worldRadius * cosa;
			y1 = center.y - worldRadius * sina;
			vertices.append(sf::Vertex(Vector2f(x1, y1), color));

			x1 = center.x + worldRadius * sina;
			y1 = center.y + worldRadius * cosa;
			vertices.append(sf::Vertex(Vector2f(x1, y1), color));

			x1 = center.x - worldRadius * sina;
			y1 = center.y - worldRadius * cosa;
			vertices.append(sf::Vertex(Vector2f(x1, y1), color));

			x1 = center.x - worldRadius * sina;
			y1 = center.y + worldRadius * cosa;
			vertices.append(sf::Vertex(Vector2f(x1, y1), color));

			x1 = center.x + worldRadius * sina;
			y1 = center.y - worldRadius * cosa;
			vertices.append(sf::Vertex(Vector2f(x1, y1), color));

		}
	}
	void Shapes::CircleShape::deleteMe()
	{
		delete(this);
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