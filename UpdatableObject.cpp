#include "UpdatableObject.h"
#include <iostream>


namespace Engine2D 
{
	vector<UpdatableObject*> UpdatableObject::All;

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
		UpdatableObject::All.push_back(this);
		this->Start();
	}

	UpdatableObject::~UpdatableObject()
	{
		std::cout << "SETTING NULL" << std::endl;
		for (vector<UpdatableObject*>::iterator it = UpdatableObject::All.begin(); it != UpdatableObject::All.end(); ++it)
		{
			if (*it == this) {
				*it = NULL;
				break;
			}
		}
		std::cout << "SET UPDATABLE NULL" << std::endl;

	}
	void UpdatableObject::deleteMe()
	{
		delete (UpdatableObject*)(this);
	}
}