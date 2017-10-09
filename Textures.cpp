#include "Textures.h"
#include "Primitives.h"


#define CAMERA_OFFSET 250

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

//********

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
//********
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
		for (int tmpy = 7; tmpy <= 30; tmpy += 7)
			rectfill(BMP, tmpx, tmpy, tmpx + 14, tmpy + 7, makecol(61 + rand() % 5, 113 + rand() % 55, 31 + rand() % 5)); // rysowanie trawy

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
		if (h.x>x    &&  h.x<x + l  &&     h.y>y    && h.y<y + 30)
			gravity_blocks++;
		if (gravity_blocks>0)
		{
			h.ground = true;
		}
		else
			h.ground = false;
	}
}
//************************
Hero::Hero(int x, int y)
{
	this->x = x;
	this->y = y;
	this->ground = false;
	this->jump = false;
	this->p_y = SCREEN_H;
	BMP = create_bitmap(40, 32);
	rectfill(BMP, 0, 0, 40, 32, makecol(255, 255, 255));
}

void Hero::draw(BITMAP* buffor)
{
	masked_blit(this->BMP, buffor, 0, 0, x, y, BMP->w, BMP->h);
}

void Hero::move()
{
	if (key[KEY_A])
		x--;
	if (key[KEY_D])
		x++;
	if (key[KEY_W] && !jump&& ground)
	{
		jump = true;
		ground = false;
		p_y = y - 150;
		if (p_y<0)
			p_y = 0;
	}
	if (jump)
	{
		if (y != p_y)
			y--;
		else
		{
			jump = false;
			p_y = SCREEN_H;
		}
	}
	if (!ground && !jump)
		y++;
	if (key[KEY_R])
	{
		x = 300;
		y = 100;
	}
	Ground::gravity_blocks = 0;
}
//************************
