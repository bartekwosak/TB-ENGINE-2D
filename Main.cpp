#include "Library.h"
#include "Engine.h"
#include "Colors.h"
#include "Functions.h"
#include "Textures.h"
#include "Primitives.h"
#include "prostokat.h"
#define CAMERA_OFFSET 250


using namespace std;

int Ground::gravity_blocks = 0;

volatile int timer = 0;

void increment_speed()
{
    timer++;
    if(timer >2)
        timer = 0;
}
END_OF_FUNCTION( increment_speed );

int main(void)
{
    //Declaration objects:
    TBEngine * engine = new TBEngine(800, 600);
    static BITMAP * buffor = create_bitmap(SCREEN_W, SCREEN_H);
    Colors * color = new Colors();
//	Circle * circle = new Circle(200, 250, 100, color->orange);
//	Circle * circle2 = new Circle(500, 470, 70, color->make_color(96, 68, 145));
//	Circle * circle3 = new Circle(300, 470, 40, color->lime);
//	Rectangle * rect = new Rectangle(20, 100, 300, 20, color->green);
//	Rectangle * rect2 = new Rectangle(400, 30, 600, 270, color->gray);
//	Triangle * triangle = new Triangle(300, 100, 500, 300, 300, 400, color->brown);
//	Square * square = new Square(100, 100, 20, color->azure);
//	Axis * axis = new Axis();
//
//	//Test methods:
//	while (true)
//	{
//		clear_to_color(buffor, color->make_color(0, 0, 0));
//		engine->fullscreen();
//
//		//Draw methods:
//		circle->draw(buffor, true, true, true);
//		circle2->draw(buffor, true, false, false);
//		circle3->draw(buffor, true, true, true);
//		axis->draw(buffor);
//		rect->draw(buffor, true);
//		rect2->draw(buffor, false);
//		triangle->draw(buffor);
//		square->draw(buffor, true);
//		blit(buffor, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
//
//		//Logic methods:
//		circle->field();
//		circle->length();
//		circle2->field();
//		circle2->length();
//		rect->field();
//		rect->length();
//		rect2->field();
//		rect2->length();
//		triangle->length();
//		triangle->field();
//		triangle->middle_triangle();
//		square->field();
//		square->length();
//
//		if (key[KEY_1]) {
//			break;
//		}
//
//		if (key[KEY_ESC])
//		{
//			exit(1);
//		}
//	}


    //Engine - game:

    LOCK_VARIABLE( timer );
    LOCK_FUNCTION( increment_speed );
    install_int_ex( increment_speed, BPS_TO_TIMER( 10 ) );

    Sky *theme = new Sky(color->purple);
    Moon *moon = new Moon();

    Stars *stars[20];
    for (int i = 0; i<20; i++)
        stars[i] = new Stars();

    Ground *g = new Ground(5, 50, 50);
    Ground *g2 = new Ground(20, 500, 213);
    Ground *g3 = new Ground(233, 420, 230);
    Ground *g4 = new Ground(460, 300, 120);
    Ground *g5 = new Ground(680, 200, 506);
    Ground *g6 = new Ground(1150,400,400);
    Ground *g7 = new Ground(1450,510,600);

    Telebim *t1 = new Telebim(730,300);

    Tree *tree1 = new Tree(90,207);
    Tree *tree2 = new Tree(442,7);
    Tree *tree3 = new Tree(1000,-79);
    Tree *tree4 = new Tree(1200,109);

    Bush *b1 = new Bush(63,467);
    Bush *b2 = new Bush(820,160);
    Bush *b3 = new Bush(1380,360);

    Water_clif *w1 = new Water_clif(14,150);
    Water_clif *w2 = new Water_clif(500,400);
    Water_clif *w3 = new Water_clif(690,300);
    Water_clif *w4 = new Water_clif(1300,500);
    Water_clif *w5 = new Water_clif(1800,500);


    Hero *hero = new Hero(300, 100);

    Enemy *enemy1 = new Enemy(690,210,680,1106);

    BITMAP * BOARD = create_bitmap(2100, SCREEN_H);

    while (true)
    {
        clear_to_color(BOARD, color->make_color(0, 0, 0));
        engine->fullscreen();
        theme->draw(BOARD, hero->x, BOARD->w);

        for (int i = 0; i<20; i++)
            stars[i]->draw(BOARD, hero->x, BOARD->w);

        moon->draw(BOARD);

        enemy1->draw(BOARD);

        g->draw(BOARD);
        w1->draw(BOARD);

        g2->draw(BOARD);
        g3->draw(BOARD);

        g4->draw(BOARD);
        w2->draw(BOARD);

        g5->draw(BOARD);
        w3->draw(BOARD);

        g6->draw(BOARD);
        w4->draw(BOARD);
        w5->draw(BOARD);

        g7->draw(BOARD);

        tree1->draw(BOARD);
        tree2->draw(BOARD);
        tree3->draw(BOARD);
        tree4->draw(BOARD);

        b1->draw(BOARD);
        b2->draw(BOARD);
        b3->draw(BOARD);


        hero->draw(BOARD,timer);



        t1->draw(BOARD,*hero,timer);
        //r1->draw(BOARD,hero->x);
        if (hero->x >= CAMERA_OFFSET && hero->x <= BOARD->w - SCREEN_W + CAMERA_OFFSET)
            blit(BOARD, screen, hero->x - CAMERA_OFFSET, 0, 0, 0, SCREEN_W, SCREEN_H);
        else if (hero->x <= CAMERA_OFFSET)                                              //LEWA STRONA PLANSZY
            blit(BOARD, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        else                                                                             //PRAWA STRONA PLANSZY
        {
            //blit(BOARD, screen, BOARD->w - SCREEN_W, 0, 0, 0, SCREEN_W, SCREEN_H);
            masked_stretch_blit(BOARD, screen, BOARD->w - SCREEN_W+hero->x-1550, hero->x-1550, SCREEN_W-hero->x+1550, SCREEN_H-hero->x+1550, 0, 0, SCREEN_W, SCREEN_H);

        }
        //textprintf_centre_ex(screen, font, 500, 500, makecol(255, 255, 255), -1, "%d", hero->x);
        g->gravity(*hero);
        g2->gravity(*hero);
        g3->gravity(*hero);
        g4->gravity(*hero);
        g5->gravity(*hero);
        g6->gravity(*hero);
        g7->gravity(*hero);
        enemy1->ini(hero->x);
        enemy1->move();

        hero->move(170,timer);
        moon->move(hero->x,hero->klatka,hero->anim);

        //textprintf_centre_ex(screen, font, 500, 500, makecol(255, 255, 255), -1, "%d",  timer);

        if (key[KEY_ESC])
        {
            break;
        }
    }

    return 0;
}
END_OF_MAIN()
