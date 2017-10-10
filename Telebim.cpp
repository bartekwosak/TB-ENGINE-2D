#include "Telebim.h"

// Methods - class Telebim

Telebim::Telebim(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Telebim::draw(BITMAP *buffor, Hero h) {
	rectfill(buffor, this->x - 5, this->y - 3, this->x + 410, this->y + 206, makecol(20, 20, 20));

	if (h.x<this->x - 200 || h.x>this->x + 400)
	{
		for (int i = this->x; i < this->x + 400; i += 14)
			for (int j = this->y; j < this->y + 200; j += 7)
			{
				int r = rand() % 20;
				rectfill(buffor, i, j, i + 14, j + 7, makecol(70 + r, 70 + r, 70 + r));
			}
	}
	else {
		int tmpy = h.y - 100;
		if (h.y - 100 < 0)
			tmpy = 0;
		if (h.y + 100 > SCREEN_H)
			tmpy = SCREEN_H - 200;
		stretch_blit(buffor, buffor, h.x - 200, tmpy, 400, 200, this->x, this->y, 400, 200);
		h.draw(buffor);
	}
}