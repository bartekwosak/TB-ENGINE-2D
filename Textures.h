#pragma once
#include "Library.h"

class Hero {

	BITMAP* BMP;
public:
	bool ground;
	bool jump;
	int x;
	int y;
	int p_y;
	int jump_height;
	Hero(int x, int y);
	void draw(BITMAP *buffor);
	void move(int jump_height);
};

class Sky {
	int color;
	BITMAP *BMP;
public:
	Sky(int color);
	void draw(BITMAP *buffor, int x, int w);
};

class Stars {
	int x;
	int y;
	int color;
public:
	Stars();
	void draw(BITMAP *buffor, int x, int w);
};

class Ground {
	int x;
	int y;
	int l;
	BITMAP *BMP;
public:
	static int gravity_blocks;
	Ground(int x, int y, int l);
	void gravity(Hero &h);
	void draw(BITMAP *buffor);
};




