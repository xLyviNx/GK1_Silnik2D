#pragma once
#include "DrawableObject.h"
#include "Transform.h"
#include "PrimitiveRenderer.h"
#include "Engine.h"
namespace Engine2D
{
	class ShapeObject : public virtual TransformableObject, public virtual DrawableObject
	{
	protected:
		sf::RenderWindow* renderWindow;
		VertexArray vertices;
	public:
		ShapeObject(Vector2f position);
		ShapeObject(std::string name, Vector2f position);
		virtual void deleteMe() override;
		virtual void Draw() override;
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
			Vector2f points[5];
		public:
			Color color;
			void PropertiesChanged() override;
			//RectangleShape();
			RectangleShape(Vector2f position, float A, float B, Color color, float width);
			RectangleShape(std::string name, Vector2f position, float A, float B, Color color, float width);
			void deleteMe() override;
		};
		class CircleShape : public virtual ShapeObject
		{
		private:
			float localRadius;
			float worldRadius;
			//float width;
		public:
			Color color;
			void PropertiesChanged() override;
			CircleShape(Vector2f position, float R, Color color);
			CircleShape(std::string name, Vector2f position, float R, Color color);
			void deleteMe() override;
		};
	}
}