#include "GameObject.h"

namespace Engine2D
{
	set<GameObject*> GameObject::All;
	void GameObject::Initialize()
	{
		GameObject::All.insert(this);
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
		GameObject::All.erase(this);
	}
}