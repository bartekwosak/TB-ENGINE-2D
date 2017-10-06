#include "Library.h"
#include "Engine.h"
#include "Colors.h"
#include "Functions.h"
#include "Primitives.h"

TBEngine::TBEngine(int w, int h)
{
	this->w = w;
	this->h = h;
	this->full = false;
	allegro_init();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, w, h, 0, 0);
	install_keyboard();
	install_mouse();
	enable_hardware_cursor();
	select_mouse_cursor(MOUSE_CURSOR_ARROW);
	show_mouse(screen);
}

void TBEngine::fullscreen()
{
	if (key[KEY_F5])
	{
		BITMAP *bmp = create_bitmap(w, h);
		blit(screen, bmp, 0, 0, 0, 0, w, h);
		if (!full)
		{
			set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, w, h, 0, 0);
			full = true;
		}
		else
		{
			set_gfx_mode(GFX_AUTODETECT_WINDOWED, w, h, 0, 0);
			full = false;
		}
		blit(bmp, screen, 0, 0, 0, 0, w, h);
	}
}
