#include "GameObject.h"

namespace Engine2D
{
	set<GameObject*> GameObject::All;
	void GameObject::Initialize()
	{
		GameObject::All.insert(this);
	}

	void GameObject::deleteMe()
	{
		delete(this);
	}

	GameObject::GameObject()
	{
		this->name = "Game Object";
		this->Initialize();
	}
	GameObject::GameObject(std::string name)
	{
		this->name = name;
		this->Initialize();
	}
	GameObject::~GameObject()
	{
		auto it = GameObject::All.find(this);
		if (it != GameObject::All.end())
		{
			GameObject::All.erase(it);
		}
	}
}