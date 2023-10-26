#include "GameObject.h"
#include "Transform.h"

namespace Engine2D
{
	set<GameObject*> GameObject::All;
	void GameObject::Initialize()
	{
		if (transform)
			transform->gameObject = this;
		GameObject::All.insert(this);
	}

	GameObject::GameObject()
	{
		transform = new Transform();
		this->Initialize();
	}

	GameObject::GameObject(Transform* parent)
	{
		transform = new Transform(parent);
		this->Initialize();
	}

	GameObject::~GameObject()
	{
		GameObject::All.erase(this);
		if (transform != NULL)
		{
			if (transform->GetParent())
			{
				transform->GetParent()->children.erase(transform);
			}
			for (auto child : transform->children)
			{
				child->SetParent(NULL);
				delete(child->gameObject);
			}
			delete(transform);
			transform = NULL;
		}
	}
}