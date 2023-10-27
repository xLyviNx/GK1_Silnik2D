#include "UpdatableObject.h"


namespace Engine2D 
{
	set<UpdatableObject*> UpdatableObject::All;

	void UpdatableObject::Update(float deltaTime)
	{
		puts("UPDATABLE UPDATE");
	}

	void UpdatableObject::Start()
	{
		puts("updatable start");
	}

	UpdatableObject::UpdatableObject()
	{
		UpdatableObject::All.insert(this);
		this->Start();
	}

	UpdatableObject::~UpdatableObject()
	{
		UpdatableObject::All.erase(this);
	}
}