#ifndef _POINT_H
#define _POINT_H

class Point
{
private:
	int _x;
	int _y;

public:
	explicit Point();
	explicit Point(const int x, const int y);
	Point(const Point &src);
	virtual ~Point();

	int X();
	Point &SetX(const int x);

	int Y();
	Point &SetY(const int y);

	Point operator+=(const Point &other);
	Point operator+(const Point &other);

	Point operator-=(const Point &other);
	Point operator-(const Point &other);

	virtual bool operator==(const Point &other);
};

#endif


