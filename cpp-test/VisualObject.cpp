#include "pch.h"
#include "VisualObject.h"

unsigned int VisualObject::_objCount = 0;

VisualObject::VisualObject()
	: Point(0, 0), _symbol(' ')
{
	_objCount++;
}

VisualObject::VisualObject(const Point &point, const char symbol)
	: Point(point), _symbol(symbol)
{
	_objCount++;
}

VisualObject::VisualObject(const int x, const int y, const char symbol)
	: Point(x, y), _symbol(symbol)
{
	_objCount++;
}


VisualObject::~VisualObject()
{
	_objCount--;
}

char VisualObject::Symbol() const
{
	return _symbol;
}

bool VisualObject::operator==(const VisualObject &other)
{
	VisualObject &refOther = const_cast<VisualObject&>(other);
	return this->X() == refOther.X() && this->Y() == refOther.Y() && this->_symbol == refOther._symbol;
}

bool VisualObject::operator==(const Point &other)
{
	return Point::operator==(other);
}

unsigned int VisualObject::ObjCount()
{
	return _objCount;
}
