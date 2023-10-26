#pragma once
#include "GameObject.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <set>
using namespace std;
using namespace sf;
namespace Engine2D
{
	class GameObject;
	class Transform
	{
	private:
		Transform* parent;
	public:
		GameObject* gameObject;
		set<Transform*> children;
		Vector2f position;
		Vector2f worldPosition();
		Vector2f scale;
		Vector2f worldScale();
		float rotation;
		float worldRotation();
		void Translate(float X, float Y);
		void Translate(Vector2f XY);
		void Scale(float XY);
		void Scale(float X, float Y);
		void Scale(Vector2f XY);
		void Rotate(float rotation);
		void SetParent(Transform* newParent);
		Transform();
		Transform(Vector2f position);
		Transform(Vector2f position, float rotation);
		Transform(Vector2f position, Vector2f scale, float rotation);
		Transform(Vector2f position, Vector2f scale, float rotation, Transform* parent);
		Transform(Transform* parent);
		Transform* GetParent();
	};
}