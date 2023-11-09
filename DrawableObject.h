#pragma once
#include <set>
namespace Engine2D {
	class DrawableObject
	{
	public:
		bool visible;
		static std::set<DrawableObject*> All;
		virtual void Draw();
		DrawableObject();
		~DrawableObject();
	};
}