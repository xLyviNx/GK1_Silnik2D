#pragma once
#include "DrawableObject.h"
#include "Transform.h"
#include "PrimitiveRenderer.h"
#include "Engine.h"
#include "Collisions.h"
namespace Engine2D
{
	class ShapeObject : public virtual TransformableObject, public virtual DrawableObject, public virtual Collisions
	{
	protected:
		sf::RenderWindow* renderWindow;
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
			sf::RectangleShape rectShape;
		public:
			Color fillColor;
			Color color;
			virtual void PropertiesChanged() override;
			//RectangleShape();
			RectangleShape(Vector2f position, float A, float B, Color color, float width);
			RectangleShape(Vector2f position, float A, float B, Color color, Color fillColor, float width);
			RectangleShape(std::string name, Vector2f position, float A, float B, Color color, float width);
			RectangleShape(std::string name, Vector2f position, float A, float B, Color color, Color fillColor, float width);
			void deleteMe() override;
			void Draw() override;
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
			void Draw() override;
		};
	}
}