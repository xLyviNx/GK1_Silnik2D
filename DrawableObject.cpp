#include "DrawableObject.h"
namespace Engine2D {
	std::set<DrawableObject*> DrawableObject::All;
	void DrawableObject::Draw()
	{

	}
	DrawableObject::DrawableObject()
	{
		visible = true;
		All.insert(this);
	}

	DrawableObject::~DrawableObject()
	{
		All.erase(this);
	}

	void DrawableObject::deleteMe()
	{
		delete this;
	}

}