#include "Library.h"
#include "Engine.h"
#include "Colors.h"
#include "Primitives.h"
#include "Functions.h"

using namespace std;

int main(void)
{
	//Declaration objects:
	TBEngine * engine = new TBEngine(800, 600);
	static BITMAP * buffor = create_bitmap(SCREEN_W, SCREEN_H);
	Colors * color = new Colors();
	Line * line = new Line(200, 100, 100, 200, color->blue);
	Circle * circle = new Circle(200, 250, 100, color->orange);
	Circle * circle3 = new Circle(300, 470, 40, color->lime);
	Circle * circle2 = new Circle(500, 470, 70, color->make_color(96, 68, 145));
	Rectangle * rect = new Rectangle(20, 100, 300, 20, color->green);
	Rectangle * rect2 = new Rectangle(400, 30, 600, 270, color->gray);
	Triangle * triangle = new Triangle(300,100, 500,300,300,400, color->brown);
	Axis * axis = new Axis();
	//Test methods:
	while (true)
	{
		clear_to_color(buffor, color->make_color(0, 0, 0));
		circle->draw(buffor,true,true,false);
		circle2->draw(buffor,true,false,true);
		circle3->draw(buffor, true, true, true);
		axis->draw(buffor);
		rect->draw(buffor, true);
		rect2->draw(buffor, false);
		triangle->draw(buffor);
		blit(buffor, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		engine->fullscreen();
		circle->field();
		circle->length();
		circle2->field();
		circle2->length();
		rect->field();
		rect->length();
		rect2->field();
		rect2->length();
		triangle->length();
		triangle->field();
		triangle->middle_triangle();
		rest(25);
		if (key[KEY_ESC]) {
			return 0;
		}
	}
	return 0;

}
END_OF_MAIN()