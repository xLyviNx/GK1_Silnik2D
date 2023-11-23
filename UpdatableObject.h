#pragma once
#include <vector>
using namespace std;
namespace Engine2D 
{
	class UpdatableObject
	{
	public:
		static vector<UpdatableObject*> All;
		virtual void Update(float deltaTime);
		virtual void Start();
		UpdatableObject();
		~UpdatableObject();
		virtual void deleteMe();
	};
}