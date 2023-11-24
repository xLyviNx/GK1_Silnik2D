#pragma once
#include <vector>
#include "GameObject.h"
using namespace std;
namespace Engine2D 
{
	class UpdatableObject : public virtual GameObject
	{
	public:
		static vector<UpdatableObject*> All;
		virtual void Update(float deltaTime);
		virtual void Start();
		UpdatableObject();
		~UpdatableObject();
		virtual void deleteMe() override;
	};
}