#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <set>
#include "Transform.h"
using namespace std;
using namespace sf;
namespace Engine2D
{
	class GameObject
	{
		void Initialize();
	public:
		static set<GameObject*> All;

		Transform* transform;
		string name;

		GameObject();
		GameObject(Transform* parent);
		~GameObject();

	};
}