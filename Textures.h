#pragma once
#include "Library.h"
#include "Characters.h"

class Sky {
	int color;

public:
    BITMAP *BMP;
	Sky(int color);
	void draw(BITMAP *buffor, int x, int w);
};

class Moon{
    int x;
    int y;
    BITMAP* BMP;
public:
    Moon();
    void draw(BITMAP *buffor);
    void move(int xx,int timer,bool anim);
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
	int yp;
	bool moving;
    bool resume;
    BITMAP *BMP;
public:

	static int gravity_blocks;
	Ground(int x, int y, int l,bool moving);
	void gravity(Hero &h);
	void draw(BITMAP *buffor);
	void move(Hero h);
};

class Telebim{
    int x;
    int y;
public:
    Telebim(int x,int y);
    void draw(BITMAP * buffor,Hero h,int timer);
};

class Tree{
    int x;
    int y;
    BITMAP* BMP;
public:
    Tree(int x,int y);
    void draw(BITMAP * buffor);
};

class Bush{
    int x;
    int y;
    BITMAP* BMP;
public:
    Bush(int x,int y);
    void draw(BITMAP * buffor);
};

class Water_clif{
    int x;
    int y;
    int delta;
public:
    Water_clif(int x,int y);
    void draw(BITMAP* buffor);
};

