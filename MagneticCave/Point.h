
#ifndef POINT_H
#define POINT_H

class Point
{
public:
	Point(void);
	Point(int inX, int inY) : x(inX), y(inY) {}
	Point(const Point& p) : x(p.x), y(p.y) {}
	virtual ~Point(void);
	
	int x;
	int y;

	bool isValid() { return (x != -1) && (y != -1); }
	
};

#endif