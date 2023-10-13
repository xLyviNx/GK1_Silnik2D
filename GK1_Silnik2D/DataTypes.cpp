#include "DataTypes.h"

using namespace GRUPA3::DataTypes;
Vector2::Vector2(double x, double y)
{
	this->x = x;
	this->y = y;
}
Vector2::Vector2(double x)
{
	this->x = x;
	this->y = 0;
}
Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}