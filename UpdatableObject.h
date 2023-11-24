#pragma once
#include <vector>
#include "GameObject.h"
using namespace std;
namespace Engine2D 
{/**
 * @brief klasa implementujaca do programu obiekt, dla ktorego mozliwe sa zmiany w czasie rzeczywistym
 */
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