#include "Textures.h"
#include "Primitives.h"
#define CAMERA_OFFSET 250

// Methods - class Hero:

Hero::Hero(int x, int y)
{
	this->x = x;
	this->y = y;
	this->ground = true;
	this->jump = false;
	this->p_y = SCREEN_H;
	this->lewo = false;
	this->prawo = true;
	this->anim = false;
	this->acceleration = 1;
	BMP =  load_bitmap("BMP/hero.bmp",NULL);
}

void Hero::draw(BITMAP* buffor,int timer)
{
    if(!ground&&!anim)
    {
        if(p_y<y&&prawo)
            masked_blit(this->BMP, buffor, 50, 0, x, y, BMP->w/3, BMP->h/5);
        else if(p_y>y&&prawo)
           masked_blit(this->BMP, buffor, 100, 0, x, y, BMP->w/3, BMP->h/5);
        else if(p_y<y&&lewo)
           masked_blit(this->BMP, buffor, 50, 240, x, y, BMP->w/3, BMP->h/5);
        else
            masked_blit(this->BMP, buffor, 100, 240, x, y, BMP->w/3, BMP->h/5);
    }
	else if(!anim){
        if(prawo)
            masked_blit(this->BMP, buffor,klatka, 80, x, y, BMP->w/3, BMP->h/5);
        else if(lewo)
            masked_blit(this->BMP, buffor, klatka, 160, x, y, BMP->w/3, BMP->h/5);
        else
            masked_blit(this->BMP, buffor, 0, 0, x, y, BMP->w/3, BMP->h/5);
	}
	else
    {
        masked_blit(this->BMP, buffor, klatka, 320, x, y, BMP->w/3, BMP->h/5);
    }
    if(key[KEY_E])
    {
        //textprintf_centre_ex(screen, font, 500, 500, makecol(255, 255, 255), -1, "%d", mx);
        //textprintf_centre_ex(screen, font, 500, 500, makecol(255, 255, 255), -1, "%d", hero->x);
           // putpixel(buffor,((x+40)+i*(x-mx)),(y+40)+i*(y-my),makecol(255,0,0));
            if (x >= CAMERA_OFFSET && x <= 2100 - SCREEN_W + CAMERA_OFFSET)
                line(buffor,x+40,y+40,mouse_x+x-CAMERA_OFFSET,mouse_y,makecol(255,35,0));
            else if (x <= CAMERA_OFFSET)                                              //LEWA STRONA PLANSZY
                line(buffor,x+40,y+40,mouse_x,mouse_y,makecol(255,35,0));
            else
            {
                for(int i=0;i<20;i++)
                    line(buffor,x+40,y+40,mouse_x+x+(i*5)-CAMERA_OFFSET,mouse_y,makecol(255,35,0));
            }
            poll_mouse();
    }
}

void Hero::move(int jump_height,int timer)
{
//    if(!key[KEY_A]&&!key[KEY_D]&&!jump)
//    {
//        lewo = false;
//        prawo = false;
//    }
	if (key[KEY_A]){
		x--;
        lewo = true;
        prawo = false;
        klatka = timer*50;
		}
	if (key[KEY_D]){
		x++;
        prawo = true;
        lewo = false;
        klatka = timer*50;
	}
	if (key[KEY_W] && !jump && ground)
	{
	    acceleration = 1;
		jump = true;
		ground = false;
		p_y = y - jump_height;
		if (p_y<0)
			p_y = 0;
	}
	if(key[KEY_S]){
        ground = false;
	}

	if(key[KEY_Q])
    {
        anim = true;
        klatka = timer*50;
    }
    if(anim&&!key[KEY_Q])
    {
        if(timer>1)
            anim = false;
    }
	if (jump)
	{
	    if(acceleration<3)
            acceleration+=0.01;
		if (y >= p_y)
			y-=acceleration;
		else
		{
			jump = false;
			p_y = SCREEN_H;
		}
	}
	if (!ground && !jump)
    {
		y+=acceleration;
		acceleration+=0.01;
    }
	if (key[KEY_R])
	{
		x = 1500;
		y = -50;
		acceleration = 1;
	}
	Ground::gravity_blocks = 0;
}

// Methods - class Sky:

Sky::Sky(int color)
{
	this->color = color;
	Circle *c = new Circle(SCREEN_W / 2, SCREEN_H + (SCREEN_H / 2), SCREEN_H + (SCREEN_H / 2) + (SCREEN_H / 10), color);
	BMP = create_bitmap(SCREEN_W, SCREEN_H);
	c->draw(this->BMP, true, true, false);
}

void Sky::draw(BITMAP *buffor, int x, int w) {
	if (x - CAMERA_OFFSET>0 && x<w - SCREEN_W + CAMERA_OFFSET)
		blit(this->BMP, buffor, 0, 0, x - CAMERA_OFFSET, 0, SCREEN_W, SCREEN_H);
	else if (x>w - SCREEN_W)
		blit(this->BMP, buffor, 0, 0, w - SCREEN_W, 0, SCREEN_W, SCREEN_H);
	else
		blit(this->BMP, buffor, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

// Methods - class Moon:

Moon::Moon(){
    this->x = 2000;
    this->y = -40;
    BMP = create_bitmap(200,200);
    clear_to_color(BMP,makecol(255,0,255));
    Circle *s = new Circle(100,100,50,makecol(255,255,150));
    s->draw(BMP,true,true,false);
    s = new Circle(80,100,50,makecol(255,0,255));
    s->draw(BMP,true,false,false);
}

void Moon::draw(BITMAP * buffor){
    masked_blit(this->BMP, buffor, 0, 0, this->x, this->y, SCREEN_W, SCREEN_H);
}

void Moon::move(int xx,int timer,bool anim){
    this->x=1600-xx;
    //textprintf_centre_ex(screen, font, 500, 500, makecol(255, 255, 255), -1, "%d",  timer);
    if(xx>x-100 &&   xx<x+100   && anim)
    {
         Circle *s = new Circle(100,100,50,makecol(255-timer,255-timer,150-timer));
         s->draw(BMP,true,true,false);
         s = new Circle(80,100,50,makecol(255,0,255));
         s->draw(BMP,true,false,false);
         delete s;
    }
}

// Methods - class Stars:

Stars::Stars() {
	this->x = rand() % SCREEN_W;
	this->y = rand() % 50;
	this->color = makecol(100 + rand() % 150, 100 + rand() % 150, 100 + rand() % 150);
}

void Stars::draw(BITMAP *buffor, int h, int w) {
	if (h - CAMERA_OFFSET>0 && h<w - SCREEN_W + CAMERA_OFFSET) {
		putpixel(buffor, x + h - CAMERA_OFFSET, y, color);
		putpixel(buffor, x + h - CAMERA_OFFSET + 1, y, color);
		putpixel(buffor, x + h - CAMERA_OFFSET, y + 1, color);
		putpixel(buffor, x + h - CAMERA_OFFSET + 1, y + 1, color);
	}
	else if (h>w - SCREEN_W)
	{
		putpixel(buffor, w - SCREEN_W + x, y, color);
		putpixel(buffor, w - SCREEN_W + x + 1, y, color);
		putpixel(buffor, w - SCREEN_W + x, y + 1, color);
		putpixel(buffor, w - SCREEN_W + x + 1, y + 1, color);
	}
	else {
		putpixel(buffor, x, y, color);
		putpixel(buffor, x + 1, y, color);
		putpixel(buffor, x, y + 1, color);
		putpixel(buffor, x + 1, y + 1, color);
	}
}

// Methods - class Ground:

Ground::Ground(int x, int y, int l) {
	this->x = x;
	this->y = y;
	this->l = l;
	BMP = create_bitmap(l, SCREEN_H - y);
	clear_to_color(BMP, makecol(255, 0, 255));

	for (int tmpx = 0; tmpx <= l; tmpx += 14)
		for (int tmpy = 7; tmpy <= SCREEN_H - y; tmpy += 7)
		{
			if (rand() % 200) // rysowanie szarego
				rectfill(BMP, tmpx, tmpy, tmpx + 14, tmpy + 7, makecol(61 + rand() % 5, 43 + rand() % 5, 31 + rand() % 5));
			else {
				int r = +rand() % 25; // rysowanie brazowego
				rectfill(BMP, tmpx, tmpy, tmpx + 14, tmpy + 7, makecol(70 + r, 70 + r, 70 + r));
			}
		}

	for (int tmpy = 30; tmpy <SCREEN_H - y; tmpy++)
		rectfill(BMP, 0, tmpy, 1, tmpy + 1, makecol(41, 23, 21)); // rysowanie linii grubszej po stronie lewej

	for (int tmpy = 30; tmpy <SCREEN_H - y; tmpy++)
		rectfill(BMP, l - 2, tmpy, l - 1, tmpy + 1, makecol(41, 23, 21)); // rysowanie linii grubszej po stronie prawej

	for (int tmpx = 0; tmpx <= l; tmpx += 14)
		for (int tmpy = 7; tmpy <= 30; tmpy += 7){
            if (rand() % 20==0)
                rectfill(BMP, tmpx, tmpy, tmpx + 14, tmpy + 7, makecol(200 + rand() % 55, 200 + rand() % 55, 31 + rand() % 5));
            else
                rectfill(BMP, tmpx, tmpy, tmpx + 14, tmpy + 7, makecol(61 + rand() % 5, 113 + rand() % 55, 31 + rand() % 5)); // rysowanie trawy
        }
	for (int tmpx = 0; tmpx <= l; tmpx += 14)
		if (rand() % 2)
			rectfill(BMP, tmpx, 0, tmpx + 14, 7, makecol(61 + rand() % 5, 80 + rand() % 55, 31 + rand() % 5)); // rysowanie nad traw¹

	for (int tmpx = 0; tmpx <= l; tmpx += 14)
		if (rand() % 2)
			rectfill(BMP, tmpx, 36, tmpx + 14, 45, makecol(61 + rand() % 5, 80 + rand() % 55, 31 + rand() % 5)); // rysowanie pod trawa
}

void Ground::draw(BITMAP *buffor) {
	masked_blit(this->BMP, buffor, 0, 0, x, y, BMP->w, BMP->h);
}

void Ground::gravity(Hero &h) {
	for (int tmpx = 0; tmpx <= l; tmpx++)
	{
		if (h.x+h.BMP->w/3>x    &&  h.x<x + l  &&     h.y+(h.BMP->h/5)-20>y    && h.y+h.BMP->h/5<y + 30)
			gravity_blocks++;
		if (gravity_blocks>0)
		{
			h.ground = true;
		}
		else
			h.ground = false;
	}
}

// Methods - class Tree:

Tree::Tree(int x, int y)
{
    this->x = x;
    this->y = y;
    BMP = create_bitmap(140,300);
    clear_to_color(BMP,makecol(255,0,255));
    for (int tmpx = 50; tmpx <= 90; tmpx += 14)
		for (int tmpy = 120; tmpy <= 300; tmpy += 7)
		{
				int r = +rand() % 25;
				rectfill(BMP, tmpx, tmpy, tmpx + 14, tmpy + 7, makecol(35 + r, 25 + r, 45 + r));
        }
    for (int tmpx = 15; tmpx <= 120; tmpx += 14)
		for (int tmpy = 0; tmpy <= 130; tmpy += 7)
		{
            if(rand()%20==0)
                rectfill(BMP, tmpx, tmpy, tmpx + 14, tmpy + 7, makecol(25 , 80 , 25 ));
            else{
				int r = +rand() % 25;
				rectfill(BMP, tmpx, tmpy, tmpx + 14, tmpy + 7, makecol(35 + r, 130 + r, 45 + r));
            }
        }
    for (int tmpx = 0; tmpx <= 150; tmpx += 14)
		for (int tmpy = 28; tmpy <= 95; tmpy += 7)
		{
            if(rand()%20==0)
                rectfill(BMP, tmpx, tmpy, tmpx + 14, tmpy + 7, makecol(170 , 50 , 75 ));
            else{
				int r = +rand() % 25;
				rectfill(BMP, tmpx, tmpy, tmpx + 14, tmpy + 7, makecol(35 + r, 130 + r, 45 + r));
            }
        }
}

void Tree::draw(BITMAP* buffor){
    masked_blit(this->BMP, buffor, 0, 0, this->x, this->y, BMP->w, BMP->h);
}

// Methods - class Bush:

Bush::Bush(int x, int y)
{
    this->x = x;
    this->y = y;
    BMP = create_bitmap(50,50);
    clear_to_color(BMP,makecol(255,0,255));
    for (int tmpx = 10; tmpx <= 30; tmpx += 14)
		for (int tmpy = 0; tmpy <= 50; tmpy += 7)
		{
				int r = +rand() % 25;
				rectfill(BMP, tmpx, tmpy, tmpx + 14, tmpy + 7, makecol(20 + r, 30 + r, 90 + r));
        }
    for (int tmpx = 0; tmpx <= 44; tmpx += 14)
		for (int tmpy = 10; tmpy <= 37; tmpy += 7)
		{
				int r = +rand() % 25;
				rectfill(BMP, tmpx, tmpy, tmpx + 14, tmpy + 7, makecol(70 + r, 80 + r, 45 + r));
        }
}

void Bush::draw(BITMAP* buffor){
    masked_blit(this->BMP, buffor, 0, 0, this->x, this->y, BMP->w, BMP->h);
}

// Methods - class Water_clif

Water_clif::Water_clif(int x,int y){
    this->x = x;
    this->y = y;
    this->delta = SCREEN_H-y;
}
void Water_clif::draw(BITMAP* buffor){
    rectfill(buffor, this->x-2, this->y-6, this->x+24, this->y+20, makecol(24+rand()%5, 24+rand()%5, 20+rand()%5));
    for (int tmpx = x; tmpx <= x+20; tmpx += 2)
    {
        int r = +rand() % 4;
        rectfill(buffor, tmpx, this->y, tmpx+2, this->y+this->delta, makecol(70 + r, 80 + r, 100 + r));
    }
}

// Methods - class Water_clif

Telebim::Telebim(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Telebim::draw(BITMAP *buffor, Hero h, int timer) {
	rectfill(buffor, this->x - 5, this->y - 3, this->x + 410, this->y + 206, makecol(20, 20, 20));

	if (h.x<this->x - 200 || h.x>this->x + 400)
	{
		for (int i = this->x; i<this->x + 400; i += 14)
			for (int j = this->y; j<this->y + 200; j += 7)
			{
				int r = rand() % 20;
				rectfill(buffor, i, j, i + 14, j + 7, makecol(70 + r, 70 + r, 70 + r));
			}
	}
	else {
		int tmpy = h.y - 100;
		if (h.y - 100<0)
			tmpy = 0;
		if (h.y + 100>SCREEN_H)
			tmpy = SCREEN_H - 200;
		stretch_blit(buffor, buffor, h.x - 200, tmpy, 400, 200, this->x, this->y, 400, 200);
		h.draw(buffor, timer);
	}
}
