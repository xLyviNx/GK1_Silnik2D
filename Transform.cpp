#include "Transform.h"

Vector2f Engine2D::TransformableObject::worldPosition()
{
	return parent == NULL ? this->position : (this->position + parent->worldPosition());
}

Vector2f Engine2D::TransformableObject::worldScale()
{
	return parent == NULL ? this->scale : (this->scale + parent->worldScale());
}

float Engine2D::TransformableObject::worldRotation()
{
	return fmodf(parent == NULL ? this->rotation : (this->rotation + parent->worldRotation()), 360);
}

void Engine2D::TransformableObject::Translate(float X, float Y)
{
	position.x += X;
	position.y += Y;
}
void Engine2D::TransformableObject::Translate(Vector2f XY)
{
	position += XY;
}

void Engine2D::TransformableObject::Scale(float XY)
{
	scale *= XY;
}

void Engine2D::TransformableObject::Scale(float X, float Y)
{
	scale.x *= X;
	scale.y *= Y;
}

void Engine2D::TransformableObject::Scale(Vector2f XY)
{
	scale.x* XY.x;
	scale.y* XY.y;
}

void Engine2D::TransformableObject::Rotate(float rotation)
{
	this->rotation += rotation;
}

void Engine2D::TransformableObject::SetParent(TransformableObject* newParent)
{
	position = worldPosition();
	scale = worldScale();
	rotation = worldRotation();
	if (parent != NULL)
	{
		parent->children.erase(this);
	}
	if (newParent != NULL)
	{
		position -= newParent->worldPosition();
		scale -= newParent->worldScale();
		rotation -= newParent->worldRotation();
		newParent->children.insert(this);
	}
	parent = newParent;
}

Engine2D::TransformableObject::TransformableObject()
{
	children = set<TransformableObject*>();
	this->parent = NULL;
	this->position = Vector2f(0, 0);
	this->scale = Vector2f(1, 1);
	this->rotation = 0;
}

Engine2D::TransformableObject::TransformableObject(Vector2f position)
{
	children = set<TransformableObject*>();
	this->parent = NULL;
	this->position = position;
	this->scale = Vector2f(1, 1);
	this->rotation = 0;
}

Engine2D::TransformableObject::TransformableObject(Vector2f position, float rotation)
{
	children = set<TransformableObject*>();
	this->parent = NULL;
	this->position = position;
	this->scale = Vector2f(1, 1);
	this->rotation = rotation;
}

Engine2D::TransformableObject::TransformableObject(Vector2f position, Vector2f scale, float rotation)
{
	children = set<TransformableObject*>();
	this->parent = NULL;
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
}

Engine2D::TransformableObject::TransformableObject(Vector2f position, Vector2f scale, float rotation, TransformableObject* parent)
{
	if (parent != NULL)
	{
		parent->children.insert(this);
	}
	this->parent = parent;
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
}

Engine2D::TransformableObject::TransformableObject(TransformableObject* parent)
{
	if (parent != NULL)
	{
		parent->children.insert(this);
	}
	children = set<TransformableObject*>();
	this->parent = parent;
	this->position = Vector2f(0, 0);
	this->scale = Vector2f(1, 1);
	this->rotation = 0;
}

Engine2D::TransformableObject* Engine2D::TransformableObject::GetParent()
{
	return this->parent;
}

Engine2D::TransformableObject::~TransformableObject()
{
	if (GetParent())
	{
		GetParent()->children.erase(this);
	}
	for (auto child : this->children)
	{
		child->SetParent(NULL);
		delete(child);
	}
}