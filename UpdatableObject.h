#pragma once
#include <set>
using namespace std;
namespace Engine2D 
{
	class UpdatableObject
	{
	public:
		static set<UpdatableObject*> All;
		virtual void Update(float deltaTime);
		virtual void Start();
		UpdatableObject();
		~UpdatableObject();
	};
}