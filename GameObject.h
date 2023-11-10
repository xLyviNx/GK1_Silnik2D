#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <set>
using namespace std;
using namespace sf;
namespace Engine2D
{
	class GameObject
	{
		void Initialize();
	public:
		static set<GameObject*> All;
		string name;
		virtual void deleteMe();
		GameObject();
		GameObject(std::string name);
		~GameObject();

	};
}