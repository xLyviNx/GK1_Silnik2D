#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <set>
#include "GameObject.h"

using namespace std;
using namespace sf;
namespace Engine2D
{
	class TransformableObject : public virtual GameObject
	{
	private:
		
		TransformableObject* parent;
	public:
		static set<TransformableObject*> All;
		set<TransformableObject*> children;
		Vector2f position;
		Vector2f lastPosition;
		Vector2f worldPosition();
		Vector2f lastWorldPosition();
		Vector2f scale;
		Vector2f worldScale();
		Vector2f bounds;
		Vector2f worldBounds();
		float rotation;
		float worldRotation();
		void Translate(float X, float Y);
		void Translate(Vector2f XY);
		void setPosition(Vector2f XY);
		void Scale(float XY);
		void Scale(float X, float Y);
		void Scale(Vector2f XY);
		void Rotate(float rotation);
		void SetParent(TransformableObject* newParent);
		TransformableObject();
		TransformableObject(Vector2f position);
		TransformableObject(Vector2f position, float rotation);
		TransformableObject(Vector2f position, Vector2f scale, float rotation);
		TransformableObject(Vector2f position, Vector2f scale, float rotation, TransformableObject* parent);
		TransformableObject(TransformableObject* parent);
		TransformableObject* GetParent();
		~TransformableObject();
		virtual void PropertiesChanged();
		TransformableObject(std::string name, Vector2f position);
		virtual void deleteMe() override;
		//virtual void checkPropertyChanged();
	};
}