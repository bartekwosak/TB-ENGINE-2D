#include "Library.h"

//Class - Pixel
class Pixel
{
	int x;
	int y;
	int color;
public:
	Pixel(int x, int y, int color);
	void draw(BITMAP * bmp);
};

//Class - Line:
class Line
{
	int x1;
	int x2;
	int y1;
	int y2;
	int color;
	bool f;
	bool l;
public:
	Line(int x1, int x2, int y1, int y2, int color);
	void draw(BITMAP * bmp);
	void field();
	void length();
};

//Class Circle
class Circle
{
	int x;
	int y;
	int r;
	int color;
	int scale;
	bool gradient;
	bool fill;
	bool move;
public:
	Circle(int x, int y, int r, int color);
	void draw(BITMAP * bmp, bool fill, bool gradient, bool move);
	void field();
	void length();
	void moves(int xx);
	static int active;
};

//Class Rectangle
class Rectangle
{
	int x1;
	int y1;
	int x2;
	int y2;
	int color;
public:
	Rectangle(int x1, int y1, int x2, int y2, int color);
	void draw(BITMAP * bmp, bool type);
	void field();
	void length();
};

//Class Rectangle
class Triangle
{
	int x1;
	int y1;
	int x2;
	int y2;
	int x3;
	int y3;
	int color;
public:
	Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color);
	void draw(BITMAP * bmp);
	void field();
	void length();
	void middle_triangle();
};

//Class Square
class Square
{
	int x1;
	int y1;
	int x2;
	int y2;
	int l;
	int color;
	bool fill;
public:
	Square(int x1, int y1, int length, int color);
	void draw(BITMAP * bmp, bool fill);
	void field();
	void length();
};


