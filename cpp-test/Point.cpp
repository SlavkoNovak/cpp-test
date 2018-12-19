#include "pch.h"
#include "Point.h"


Point::Point() : _x(0), _y(0)
{
}

Point::Point(const int x, const int y): _x(x), _y(y)
{
}

Point::Point(const Point &src): _x(src._x), _y(src._y)
{
}

Point::~Point()
{
}

int Point::X() const
{
	return _x;
}

Point & Point::SetX(const int x)
{
	_x = x;
	return *this;
}

int Point::Y() const
{
	return _y;
}

Point & Point::SetY(const int y)
{
	_y = y;
	return *this;
}

Point Point::operator+=(const Point &other)
{
	this->_x += other._x;
	this->_y += other._y;

	return *this;
}

Point Point::operator+(const Point & other)
{
	Point retVal = *this;

	retVal._x += other._x;
	retVal._y += other._y;

	return retVal;
}

Point Point::operator-=(const Point & other)
{
	this->_x -= other._x;
	this->_y -= other._y;

	return *this;
}

Point Point::operator-(const Point & other)
{
	Point retVal = *this;

	retVal._x -= other._x;
	retVal._y -= other._y;

	return retVal;
}

bool Point::operator==(const Point & other)
{
	return this->_x == other._x && this->_y == other._y;
}
