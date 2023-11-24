#include "GameObject.h"

namespace Engine2D
{
	vector<GameObject*> GameObject::All;
	void GameObject::Initialize()
	{
		isRemoving = false;
		GameObject::All.push_back(this);
	}

	void GameObject::deleteMe()
	{
		delete (GameObject*)(this);
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
		for (vector<GameObject*>::iterator it = All.begin(); it != All.end(); ++it)
		{
			if (*it == this)
			{
				All.erase(it);
				break;
			}
		}
	}
}