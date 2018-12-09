#ifndef _VISUAL_OBJECT_H
#define _VISUAL_OBJECT_H

#include "Point.h"

class VisualObject : public Point
{
private:
	static unsigned int _objCount;
	char _symbol;

public:
	VisualObject();
	VisualObject(const Point &point, const char symbol);
	VisualObject(const int x, const int y, const char symbol);
	VisualObject(const VisualObject &) = delete;
	virtual ~VisualObject();

	char Symbol() const;

	bool operator==(const VisualObject &other);
	bool operator==(const Point &other) override;

	static unsigned int ObjCount();
};

#endif
