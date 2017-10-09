#include "Library.h"
#include "Engine.h"
#include "Colors.h"
#include "Functions.h"
#include "Textures.h"

#ifndef PRIMI
#define PRIMI
#include "Primitives.h"
#endif // PRIMI

#define CAMERA_OFFSET 250
using namespace std;

int Ground::gravity_blocks = 0;

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
	Triangle * triangle = new Triangle(300, 100, 500, 300, 300, 400, color->brown);
	Square * square = new Square(100, 100, 20, color->azure);
	Axis * axis = new Axis();

	//Test methods:
	while (true)
	{
		clear_to_color(buffor, color->make_color(0, 0, 0));
		engine->fullscreen();

		//Draw methods:
		circle->draw(buffor, true, true, false);
		circle2->draw(buffor, true, false, true);
		circle3->draw(buffor, true, true, true);
		axis->draw(buffor);
		rect->draw(buffor, true);
		rect2->draw(buffor, false);
		triangle->draw(buffor);
		square->draw(buffor, true);
		blit(buffor, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

		//Logic methods:
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
		square->field();
		square->length();

		rest(25);
		if (key[KEY_ESC]) {
			break;
		}
	}


	//************************************************************************************************


	Sky *theme = new Sky(color->make_color(80, 245, 255));
	Stars *stars[20];
	for (int i = 0; i<20; i++)
		stars[i] = new Stars();


	Ground *g = new Ground(5, 50, 50);
	Ground *g2 = new Ground(20, 500, 260);
	Ground *g3 = new Ground(233, 420, 230);
	Ground *g4 = new Ground(460, 300, 120);
	Ground *g5 = new Ground(700, 200, 506);
	Ground *g6 = new Ground(1150,400,900);

	Hero *hero = new Hero(300, 100);

	BITMAP * BOARD = create_bitmap(2100, SCREEN_H);


	while (true)
	{
		clear_to_color(BOARD, color->make_color(0, 0, 0));
		engine->fullscreen();
		theme->draw(BOARD, hero->x, BOARD->w);

		for (int i = 0; i<20; i++)
			stars[i]->draw(BOARD, hero->x, BOARD->w);

		g->draw(BOARD);
		g2->draw(BOARD);
		g3->draw(BOARD);
		g4->draw(BOARD);
		g5->draw(BOARD);
		g6->draw(BOARD);

		hero->draw(BOARD);

		if (hero->x >= CAMERA_OFFSET && hero->x <= BOARD->w - SCREEN_W + CAMERA_OFFSET)
			blit(BOARD, screen, hero->x - CAMERA_OFFSET, 0, 0, 0, SCREEN_W, SCREEN_H);
		else if (hero->x <= CAMERA_OFFSET)
			blit(BOARD, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		else
			blit(BOARD, screen, BOARD->w - SCREEN_W, 0, 0, 0, SCREEN_W, SCREEN_H);

		g->gravity(*hero);
		g2->gravity(*hero);
		g3->gravity(*hero);
		g4->gravity(*hero);
		g5->gravity(*hero);
		g6->gravity(*hero);

		hero->move();

		if (key[KEY_1])
		{
			break;
		}
	}

	return 0;
}
END_OF_MAIN()
