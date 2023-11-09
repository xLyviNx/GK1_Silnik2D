#pragma once
#include "DrawableObject.h"
#include "Transform.h"
#include "PrimitiveRenderer.h"
#include "Engine.h"
namespace Engine2D
{
	class ShapeObject : public virtual DrawableObject, public virtual TransformableObject
	{
	public:
		ShapeObject(Vector2f position);
		ShapeObject(std::string name, Vector2f position);
	};

	namespace Shapes
	{
		class RectangleShape : public virtual ShapeObject
		{
		private:
			float localA;
			float localB;
			float worldA;
			float worldB;
			float width;
			Vector2f points[4];
		public:
			Color color;
			sf::RenderWindow* renderWindow;
			void Draw() override;
			void PropertiesChanged() override;
			//RectangleShape();
			RectangleShape(Vector2f position, float A, float B, Color color, float width);
		};
	}
}