#include "Transform.h"

Vector2f Engine2D::Transform::worldPosition()
{
	return parent == NULL ? this->position : (this->position + parent->worldPosition());
}

Vector2f Engine2D::Transform::worldScale()
{
	return parent == NULL ? this->scale : (this->scale + parent->worldScale());
}

float Engine2D::Transform::worldRotation()
{
	return fmodf(parent == NULL ? this->rotation : (this->rotation + parent->worldRotation()), 360);
}

void Engine2D::Transform::Translate(float X, float Y)
{
	position.x += X;
	position.y += Y;
}
void Engine2D::Transform::Translate(Vector2f XY)
{
	position += XY;
}

void Engine2D::Transform::Scale(float XY)
{
	scale *= XY;
}

void Engine2D::Transform::Scale(float X, float Y)
{
	scale.x *= X;
	scale.y *= Y;
}

void Engine2D::Transform::Scale(Vector2f XY)
{
	scale.x* XY.x;
	scale.y* XY.y;
}

void Engine2D::Transform::Rotate(float rotation)
{
	this->rotation += rotation;
}

void Engine2D::Transform::SetParent(Transform* newParent)
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

Engine2D::Transform::Transform()
{
	children = set<Transform*>();
	this->parent = NULL;
	this->position = Vector2f(0, 0);
	this->scale = Vector2f(1, 1);
	this->rotation = 0;
}

Engine2D::Transform::Transform(Vector2f position)
{
	children = set<Transform*>();
	this->parent = NULL;
	this->position = position;
	this->scale = Vector2f(1, 1);
	this->rotation = 0;
}

Engine2D::Transform::Transform(Vector2f position, float rotation)
{
	children = set<Transform*>();
	this->parent = NULL;
	this->position = position;
	this->scale = Vector2f(1, 1);
	this->rotation = rotation;
}

Engine2D::Transform::Transform(Vector2f position, Vector2f scale, float rotation)
{
	children = set<Transform*>();
	this->parent = NULL;
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
}

Engine2D::Transform::Transform(Vector2f position, Vector2f scale, float rotation, Transform* parent)
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

Engine2D::Transform::Transform(Transform* parent)
{
	if (parent != NULL)
	{
		parent->children.insert(this);
	}
	children = set<Transform*>();
	this->parent = parent;
	this->position = Vector2f(0, 0);
	this->scale = Vector2f(1, 1);
	this->rotation = 0;
}

Engine2D::Transform* Engine2D::Transform::GetParent()
{
	return this->parent;
}
