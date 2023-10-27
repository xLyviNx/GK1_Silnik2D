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
		this->Initialize();
	}
	GameObject::~GameObject()
	{
		GameObject::All.erase(this);
	}
}