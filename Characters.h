#pragma once
#include "Library.h"
#define CAMERA_OFFSET 250

class Bullet{
    public:
    int x;
    int y;
    int range;
    bool direction;
        Bullet(int x,int y,bool direction);
        void draw(BITMAP* BMP);
        void move();
        int del();

};

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
	void move(int jump_height,int timer,bool &end);
	void attack(std::vector<Bullet> &bullets,volatile int &rest);
};


class Enemy {

    bool all;
    bool direction;

public:
    int x;
    int y;
    int ymin;
    int ymax;
    int xmin;
    int xmax;
    bool dest;
    bool init;
    BITMAP *BMP;
    Enemy(int x,int y, int xmin, int xmax);
    void ini(int x);
    void draw(BITMAP * buffor);
    int movedead();
    void move();
    int check_bullet(std::vector<Bullet> &bullets);
    int check_hero(BITMAP* buffor, Hero &h);
    void swap_bmp();
};

class Boss{
    public:
    int x;
    int y;
    int hp;
    int xmin;
    int xmax;
    bool direction;
    bool init;
    BITMAP *BMP;

    Boss(int x,int y);
    void draw(BITMAP* buffor);
    void move();
    void attack(std::vector<Enemy> &enemies);
};
