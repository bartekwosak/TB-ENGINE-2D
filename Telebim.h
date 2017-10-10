#include "Library.h"
#include "Textures.h"

class Telebim {
	int x;
	int y;
public:
	Telebim(int x, int y);
	void draw(BITMAP * buffor, Hero h);
};