#pragma once
#include "Library.h"

class Hero {
public:
	bool ground;
	bool jump;
	int x;
	int y;
	int p_y;
	float acceleration;
	bool lewo;
	bool prawo;
	bool anim;
	int klatka;
	BITMAP* BMP;
	Hero(int x, int y);
	void draw(BITMAP *buffor, int timer);
	void move(int jump_height,int timer);
};

class Sky {
	int color;
	BITMAP *BMP;
public:
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
	BITMAP *BMP;
public:
	static int gravity_blocks;
	Ground(int x, int y, int l);
	void gravity(Hero &h);
	void draw(BITMAP *buffor);
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

class Portal{
    int x;
    int y;
    BITMAP* BMP;
public:
    Portal(int x,int y);
    void draw(BITMAP* buffor);
};
