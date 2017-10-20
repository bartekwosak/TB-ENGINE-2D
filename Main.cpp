#include "Library.h"
#include "Engine.h"
#include "Colors.h"
#include "Functions.h"
#include "Textures.h"
#include "Primitives.h"
#include "Characters.h"

#define CAMERA_OFFSET 250

using namespace std;

int Ground::gravity_blocks = 0;

volatile int timer = 0;
volatile int attack_rest = 0;

void increment_speed()
{
    timer++;
    attack_rest++;
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
    LOCK_VARIABLE( timer );
    LOCK_FUNCTION( increment_speed );
    install_int_ex( increment_speed, BPS_TO_TIMER( 10 ) );
    //Engine - game:


    int lvl=0;
    BITMAP *lvl1 = load_bitmap("BMP/lvl1.bmp",NULL);
    BITMAP *lvl2 = load_bitmap("BMP/lvl2.bmp",NULL);
    BITMAP *lvl3 = load_bitmap("BMP/lvl3.bmp",NULL);
    BITMAP *lvl4 = load_bitmap("BMP/lvl4.bmp",NULL);
    BITMAP *lvl5 = load_bitmap("BMP/lvl5.bmp",NULL);
    BITMAP *lvl6 = load_bitmap("BMP/lvl6.bmp",NULL);
    BITMAP *lvl7 = load_bitmap("BMP/lvl7.bmp",NULL);
    BITMAP *lvl8 = load_bitmap("BMP/lvl8.bmp",NULL);
    BITMAP *profile = load_bitmap("BMP/profile.bmp",NULL);
    BITMAP *outfit = load_bitmap("BMP/outfits.bmp",NULL);
    BITMAP *exit = load_bitmap("BMP/exit.bmp",NULL);

    BITMAP *outfit_maska = load_bitmap("BMP/maska.bmp", NULL);
    BITMAP *outfit_wlosy = load_bitmap("BMP/wlosy.bmp", NULL);


    while(1)        //menu
    {
        clear_to_color(buffor, color->make_color(0, 0, 0));
        blit(lvl1, buffor, 0, 0, 20, 20, 180, 100);              // lvl 1
        blit(lvl2, buffor, 0, 0, 220, 20, 400, 100);             // lvl 2
        blit(lvl3, buffor, 0, 0, 420, 20, 600, 100);             // lvl 3
        blit(lvl4, buffor, 0, 0, 620, 20, 780, 100);             // lvl 4
        blit(lvl5, buffor, 0, 0, 20, 220, 180, 200);             // lvl 5
        blit(lvl6, buffor, 0, 0, 220, 220, 180, 200);            // lvl 6
        blit(lvl7, buffor, 0, 0, 420, 220, 180, 200);            // lvl 7
        blit(lvl8, buffor, 0, 0, 620, 220, 180, 200);    // boss
        rectfill(buffor,20,420,200,500,makecol(255,255,255));    // lvl 7
        rectfill(buffor,220,420,400,500,makecol(255,255,255));   // lvl 8
        rectfill(buffor,420,420,600,500,makecol(255,255,255));   // lvl 9
        rectfill(buffor,620,420,780,500,makecol(255,255,255));   // boss

        blit(profile, buffor, 0, 0, 120, 520, 180, 60);
        blit(outfit, buffor, 0, 0, 340, 520, 180, 60);
        blit(exit, buffor, 0, 0, 560, 520, 180, 60);

        blit(buffor, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if(key[KEY_ESC])
            break;
        if(mouse_b&1 && mouse_x>20&&mouse_x<200 && mouse_y>20 && mouse_y< 120)
            lvl = 1;
        if(mouse_b&1 && mouse_x>220&&mouse_x<400 && mouse_y>20 && mouse_y< 120)
            lvl = 2;
        if(mouse_b&1 && mouse_x>420&&mouse_x<600 && mouse_y>20 && mouse_y< 120)
            lvl = 3;
        if(mouse_b&1 && mouse_x>620&&mouse_x<780 && mouse_y>20 && mouse_y< 120)
            lvl = 4;
        if(mouse_b&1 && mouse_x>20&&mouse_x<200 && mouse_y>200 && mouse_y< 300)
            lvl = 5;
        if(mouse_b&1 && mouse_x>220&&mouse_x<400 && mouse_y>200 && mouse_y< 300)
            lvl = 6;
        if(mouse_b&1 && mouse_x>420&&mouse_x<600 && mouse_y>200 && mouse_y< 300)
            lvl = 7;
        if(mouse_b&1 && mouse_x>620&&mouse_x<780 && mouse_y>200 && mouse_y< 300)
            lvl = 8;


        if(mouse_b&1 && mouse_x>340&&mouse_x<520 && mouse_y>520 && mouse_y< 580)
            lvl = -1;
        if(mouse_b&1 && mouse_x>560&&mouse_x<740 && mouse_y>520 && mouse_y< 580)
            return 0;

        if(lvl==-1)
        {
            Hero *hero = new Hero(350,300,outfit_maska,outfit_wlosy);
            bool holder;
            char tab[6][3] = {{'r','g','b'},
                {'r','b','g'},
                {'g','r','b'},
                {'g','b','r'},
                {'b','r','g'},
                {'b','g','r'}
            };
            int wybor_maska = 0;
            int wybor_wlosy = 0;
            while(1)
            {
                clear_to_color(buffor, color->make_color(0, 0, 0));
                rectfill(buffor,300,200,350,250,makecol(120,120,120));   // WLOSY
                rectfill(buffor,400,200,450,250,makecol(120,120,120));
                rectfill(buffor,300,300,350,350,makecol(120,120,120));   // MASKA
                rectfill(buffor,400,300,450,350,makecol(120,120,120));
                rectfill(buffor,100,500,150,550,makecol(120,120,120));   // WSTECZ
                hero->draw(buffor,timer);
                blit(buffor, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

                if(mouse_b&1 &&((mouse_x>300&&mouse_x<350 && mouse_y>300 && mouse_y< 350)||(mouse_x>400&&mouse_x<450 && mouse_y>300 && mouse_y< 350)) && !holder)       //MASKA
                {
                    outfit_maska = load_bitmap("BMP/maska.bmp",NULL);
                    if(mouse_x>400)
                        wybor_maska++;
                    else
                        wybor_maska--;
                    if(wybor_maska==6)
                        wybor_maska = 0;
                    else if(wybor_maska==-1)
                        wybor_maska = 5;
                    for(int i=0; i<150; i++)
                    {
                        for(int j=0; j<400; j++)
                        {
                            int pix = getpixel(outfit_maska,i,j);
                            if(pix != makecol(255,0,255))
                            {
                                int r = getr(pix);
                                int g = getg(pix);
                                int b = getb(pix);
                                int nextr;
                                int nextg;
                                int nextb;
                                if(tab[wybor_maska][0] == 'r')
                                    nextr = r;
                                if(tab[wybor_maska][0] == 'g')
                                    nextr = g;
                                if(tab[wybor_maska][0] == 'b')
                                    nextr = b;
                                if(tab[wybor_maska][1] == 'r')
                                    nextg = r;
                                if(tab[wybor_maska][1] == 'g')
                                    nextg = g;
                                if(tab[wybor_maska][1] == 'b')
                                    nextg = b;
                                if(tab[wybor_maska][2] == 'r')
                                    nextb = r;
                                if(tab[wybor_maska][2] == 'g')
                                    nextb = g;
                                if(tab[wybor_maska][2] == 'b')
                                    nextb = b;
                                putpixel(outfit_maska,i,j,makecol(nextr,nextg,nextb));
                            }
                        }
                    }

                    hero = new Hero(350,300,outfit_maska,outfit_wlosy);
                    holder = true;
                }
                if(mouse_b&1 &&((mouse_x>300&&mouse_x<350 && mouse_y>200 && mouse_y< 250)||(mouse_x>400&&mouse_x<450 && mouse_y>200 && mouse_y< 250)) && !holder)
                {
                    outfit_wlosy = load_bitmap("BMP/wlosy.bmp",NULL);
                    if(mouse_x>400)
                        wybor_wlosy++;
                    else
                        wybor_wlosy--;
                    if(wybor_wlosy==6)
                        wybor_wlosy = 0;
                    else if(wybor_wlosy==-1)
                        wybor_wlosy = 5;
                    for(int i=0; i<150; i++)
                    {
                        for(int j=0; j<400; j++)
                        {
                            int pix = getpixel(outfit_wlosy,i,j);
                            if(pix != makecol(255,0,255))
                            {
                                int r = getr(pix);
                                int g = getg(pix);
                                int b = getb(pix);
                                int nextr;
                                int nextg;
                                int nextb;
                                if(tab[wybor_wlosy][0] == 'r')
                                    nextr = r;
                                if(tab[wybor_wlosy][0] == 'g')
                                    nextr = g;
                                if(tab[wybor_wlosy][0] == 'b')
                                    nextr = b;
                                if(tab[wybor_wlosy][1] == 'r')
                                    nextg = r;
                                if(tab[wybor_wlosy][1] == 'g')
                                    nextg = g;
                                if(tab[wybor_wlosy][1] == 'b')
                                    nextg = b;
                                if(tab[wybor_wlosy][2] == 'r')
                                    nextb = r;
                                if(tab[wybor_wlosy][2] == 'g')
                                    nextb = g;
                                if(tab[wybor_wlosy][2] == 'b')
                                    nextb = b;

                                putpixel(outfit_wlosy,i,j,makecol(nextr,nextg,nextb));
                            }
                        }
                    }

                    hero = new Hero(350,300,outfit_maska,outfit_wlosy);
                    holder = true;
                }
                if(!mouse_b&1)
                    holder = false;
                if(mouse_b&1 && mouse_x>100&&mouse_x<150 && mouse_y>500 && mouse_y< 550)
                {
                    lvl = 0;
                    break;
                }
            }
        }

        if(lvl==1)
        {
            Sky *theme = new Sky(color->purple);
            Moon *moon = new Moon();

            Stars *stars[20];
            for (int i = 0; i<20; i++)
                stars[i] = new Stars();

            Ground *g = new Ground(5, 50, 50,false);
            Ground *g2 = new Ground(20, 500, 213,false);
            Ground *g3 = new Ground(233, 420, 230,false);
            Ground *g4 = new Ground(460, 300, 120,false);
            Ground *g5 = new Ground(680, 200, 506,false);
            Ground *g6 = new Ground(1150,400,400,false);
            Ground *g7 = new Ground(1450,510,600,false);
            Ground *g8 = new Ground(2050,450,50,true);
            Ground *g9 = new Ground(2200,350,50,true);
            Ground *g10 = new Ground(2350,250,50,true);
            Ground *g11 = new Ground(2600,450,900,false);
            Ground *g12 = new Ground(3600,350,200,false);
            Ground *g13 = new Ground(3800,250,190,true);
            Ground *g14 = new Ground(4200,450,500,false);
            Ground *g15 = new Ground(4700,550,300,false);

            Telebim *t1 = new Telebim(730,300);

            Tree *tree1 = new Tree(90,207);
            Tree *tree2 = new Tree(442,7);
            Tree *tree3 = new Tree(1000,-79);
            Tree *tree4 = new Tree(1200,109);
            Tree *tree5 = new Tree(1600,217);
            Tree *tree6 = new Tree(1800,217);
            Tree *tree7 = new Tree(2800,160);
            Tree *tree8 = new Tree(3200,160);
            Tree *tree9 = new Tree(3630,64);
            Tree *tree10 = new Tree(4530,165);
            Tree *tree11 = new Tree(4230,165);

            Bush *b1 = new Bush(63,467);
            Bush *b2 = new Bush(820,160);
            Bush *b3 = new Bush(1380,360);
            Bush *b4 = new Bush(1950,470);
            Bush *b5 = new Bush(3100,410);
            Bush *b6 = new Bush(3400,410);

            Water_clif *w1 = new Water_clif(14,150);
            Water_clif *w2 = new Water_clif(500,400);
            Water_clif *w3 = new Water_clif(690,300);
            Water_clif *w4 = new Water_clif(1300,500);
            Water_clif *w5 = new Water_clif(1800,500);


            Hero *hero = new Hero(10, -50,outfit_maska,outfit_wlosy);

            vector<Enemy> enemies;

            Enemy enemy1(240,430,233,430);
            Enemy enemy2(690,210,680,1106);
            Enemy enemy3(1170,410,1170,1500);
            Enemy enemy4(1550,520,1550,1650);
            Enemy enemy5(1850,520,1650,1950);
            Enemy enemy6(2700,452,2700,2800);
            Enemy enemy7(2900,452,2900,3000);
            Enemy enemy8(3100,452,3100,3200);
            Enemy enemy9(3600,352,3600,3800);
            enemies.push_back(enemy1);
            enemies.push_back(enemy2);
            enemies.push_back(enemy3);
            enemies.push_back(enemy4);
            enemies.push_back(enemy5);
            enemies.push_back(enemy6);
            enemies.push_back(enemy7);
            enemies.push_back(enemy8);
            enemies.push_back(enemy9);
            vector<Enemy> deadenemies;

            vector<Bullet> bullets;

            BITMAP * BOARD = create_bitmap(5000, SCREEN_H);

            BITMAP * FLAG = load_bitmap("BMP/flag.bmp",NULL);

            bool end = false;

            while (true)
            {
                clear_to_color(BOARD, color->make_color(0, 0, 0));
                engine->fullscreen();
                theme->draw(BOARD, hero->x, BOARD->w);
                rectfill(BOARD,0,SCREEN_H-20,BOARD->w,SCREEN_H,makecol(0,0,50));  // WODA
                for (int i = 0; i<20; i++)
                    stars[i]->draw(BOARD, hero->x, BOARD->w);

                moon->draw(BOARD);


                for (std::vector<Enemy>::iterator it = enemies.begin() ; it != enemies.end();)
                {
                    it->draw(BOARD);
                    if(it->check_hero(buffor,*hero))
                        end = true;
                    ++it;
                }
                for (std::vector<Enemy>::iterator it = deadenemies.begin() ; it != deadenemies.end();)
                {
                    it->draw(BOARD);
                    ++it;
                }

                for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
                {
                    it->draw(BOARD);
                    ++it;
                }


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

                g8->draw(BOARD);

                g9->draw(BOARD);

                g10->draw(BOARD);

                g11->draw(BOARD);

                g12->draw(BOARD);

                g13->draw(BOARD);

                g14->draw(BOARD);

                g15->draw(BOARD);

                tree1->draw(BOARD);
                tree2->draw(BOARD);
                tree3->draw(BOARD);
                tree4->draw(BOARD);
                tree5->draw(BOARD);
                tree6->draw(BOARD);
                tree7->draw(BOARD);
                tree8->draw(BOARD);
                tree9->draw(BOARD);
                tree10->draw(BOARD);
                tree11->draw(BOARD);

                b1->draw(BOARD);
                b2->draw(BOARD);
                b3->draw(BOARD);
                b4->draw(BOARD);
                b5->draw(BOARD);
                b6->draw(BOARD);

                hero->draw(BOARD,timer);



                t1->draw(BOARD,*hero,timer);

                masked_blit(FLAG,BOARD,0,0,4800,450,FLAG->w,FLAG->h);

                if (hero->x >= CAMERA_OFFSET && hero->x <= BOARD->w - SCREEN_W + CAMERA_OFFSET)
                    blit(BOARD, screen, hero->x - CAMERA_OFFSET, 0, 0, 0, SCREEN_W, SCREEN_H);
                else if (hero->x <= CAMERA_OFFSET)                                              //LEWA STRONA PLANSZY
                    blit(BOARD, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                else                                                                             //PRAWA STRONA PLANSZY
                    masked_stretch_blit(BOARD, screen, BOARD->w - SCREEN_W+hero->x-4450, hero->x-4450, SCREEN_W-hero->x+4450, SCREEN_H-hero->x+4450, 0, 0, SCREEN_W, SCREEN_H);
                g->gravity(*hero);
                g2->gravity(*hero);
                g3->gravity(*hero);
                g4->gravity(*hero);
                g5->gravity(*hero);
                g6->gravity(*hero);
                g7->gravity(*hero);
                g8->gravity(*hero);
                g9->gravity(*hero);
                g10->gravity(*hero);
                g11->gravity(*hero);
                g12->gravity(*hero);
                g13->gravity(*hero);
                g14->gravity(*hero);
                g15->gravity(*hero);

                g8->move(*hero);
                g9->move(*hero);
                g10->move(*hero);
                g13->move(*hero);

                for (std::vector<Enemy>::iterator it = enemies.begin() ; it != enemies.end();)
                {
                    it->ini(hero->x);
                    it->move();
                    if(it->check_bullet(bullets))
                    {
                        deadenemies.push_back(*it);
                        it = enemies.erase(it);
                    }
                    else
                        ++it;
                }
                for (std::vector<Enemy>::iterator it = deadenemies.begin() ; it != deadenemies.end();)
                {
                    if(it->movedead())
                        it = deadenemies.erase(it);
                    else
                        ++it;
                }
                for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
                {
                    it->move();
                    if(it->del())
                        it = bullets.erase(it);
                    else
                        ++it;
                }

                hero->move(170,timer,end);
                hero->attack(bullets,attack_rest);
                moon->move(hero->x,hero->klatka,hero->anim);

                if(hero->x > 4800 )
                    end = true;
                if (key[KEY_ESC] || end)
                {
                    lvl = 0;
                    break;
                }
            }
        }

        if(lvl==2)
        {
            Sky *theme = new Sky(color->blue);
            Moon *moon = new Moon();

            Stars *stars[20];
            for (int i = 0; i<20; i++)
                stars[i] = new Stars();

            Ground *g1 = new Ground(5, 450, 50,false);
            Ground *g2 = new Ground(205, 450, 50,true);
            Ground *g3 = new Ground(355, 400, 50,true);
            Ground *g4 = new Ground(505, 350, 50,true);
            Ground *g5 = new Ground(655, 300, 50,true);
            Ground *g6 = new Ground(805, 250, 50,true);
            Ground *g7 = new Ground(1000, 450, 500,false);
            Ground *g8 = new Ground(1500, 300, 500,false);
            Ground *g9 = new Ground(2000, 150, 500,true);
            Ground *g10 = new Ground(2600, 550, 500,false);
            Ground *g11 = new Ground(3150, 450, 50,true);
            Ground *g12 = new Ground(3300, 350, 50,true);
            Ground *g13 = new Ground(3220, 250, 50,true);
            Ground *g14 = new Ground(3360, 130, 50,true);
            Ground *g15 = new Ground(3400, 70, 500,false);
            Ground *g16 = new Ground(3900,350,300,false);
            Ground *g17 = new Ground(4200,450,500,false);
            Ground *g18 = new Ground(4700,550,300,false);

            Tree *t1 = new Tree(1200,175);
            Tree *t2 = new Tree(1600,15);
            Tree *t3 = new Tree(1800,15);
            Tree *t4 = new Tree(2700,260);
            Tree *t5 = new Tree(2900,260);
            Tree *t6 = new Tree(4000,60);
            Tree *t7 = new Tree(4400,160);

            Bush *b1 = new Bush(1100,420);
            Bush *b2 = new Bush(1170,420);
            Bush *b3 = new Bush(2800,520);
            Bush *b4 = new Bush(3500,30);
            Bush *b5 = new Bush(3600,30);

            Hero *hero = new Hero(10, -100,outfit_maska,outfit_wlosy);

            vector<Enemy> enemies;

            Enemy enemy1(1150,460,1100,1400);
            Enemy enemy2(1600,320,1500,1800);
            Enemy enemy3(1800,320,1500,1800);
            Enemy enemy4(2800,570,2600,2900);
            Enemy enemy5(3600,70,3400,3800);
            Enemy enemy6(4100,370,3900,4100);
            Enemy enemy7(4400,470,4200,4400);

            enemies.push_back(enemy1);
            enemies.push_back(enemy2);
            enemies.push_back(enemy3);
            enemies.push_back(enemy4);
            enemies.push_back(enemy5);
            enemies.push_back(enemy6);
            enemies.push_back(enemy7);

            vector<Enemy> deadenemies;

            vector<Bullet> bullets;

            BITMAP * BOARD = create_bitmap(5000, SCREEN_H);

            BITMAP * FLAG = load_bitmap("BMP/flag.bmp",NULL);

            bool end = false;

            while (true)
            {
                clear_to_color(BOARD, color->make_color(0, 0, 0));
                engine->fullscreen();
                theme->draw(BOARD, hero->x, BOARD->w);
                rectfill(BOARD,0,SCREEN_H-20,BOARD->w,SCREEN_H,makecol(0,0,50));  // WODA
                for (int i = 0; i<20; i++)
                    stars[i]->draw(BOARD, hero->x, BOARD->w);

                moon->draw(BOARD);

                for (std::vector<Enemy>::iterator it = enemies.begin() ; it != enemies.end();)
                {
                    it->draw(BOARD);
                    if(it->check_hero(buffor,*hero))
                        end = true;
                    ++it;
                }
                for (std::vector<Enemy>::iterator it = deadenemies.begin() ; it != deadenemies.end();)
                {
                    it->draw(BOARD);
                    ++it;
                }

                for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
                {
                    it->draw(BOARD);
                    ++it;
                }

                g1->draw(BOARD);
                g2->draw(BOARD);
                g3->draw(BOARD);
                g4->draw(BOARD);
                g5->draw(BOARD);
                g6->draw(BOARD);
                g7->draw(BOARD);
                g8->draw(BOARD);
                g9->draw(BOARD);
                g13->draw(BOARD);
                g14->draw(BOARD);
                g10->draw(BOARD);
                g11->draw(BOARD);
                g12->draw(BOARD);
                g15->draw(BOARD);
                g16->draw(BOARD);
                g17->draw(BOARD);
                g18->draw(BOARD);

                t1->draw(BOARD);
                t2->draw(BOARD);
                t3->draw(BOARD);
                t4->draw(BOARD);
                t5->draw(BOARD);
                t6->draw(BOARD);
                t7->draw(BOARD);

                b1->draw(BOARD);
                b2->draw(BOARD);
                b3->draw(BOARD);
                b4->draw(BOARD);
                b5->draw(BOARD);

                hero->draw(BOARD,timer);




                masked_blit(FLAG,BOARD,0,0,4800,450,FLAG->w,FLAG->h);

                if (hero->x >= CAMERA_OFFSET && hero->x <= BOARD->w - SCREEN_W + CAMERA_OFFSET)
                    blit(BOARD, screen, hero->x - CAMERA_OFFSET, 0, 0, 0, SCREEN_W, SCREEN_H);
                else if (hero->x <= CAMERA_OFFSET)                                              //LEWA STRONA PLANSZY
                    blit(BOARD, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                else                                                                             //PRAWA STRONA PLANSZY
                    masked_stretch_blit(BOARD, screen, BOARD->w - SCREEN_W+hero->x-4450, hero->x-4450, SCREEN_W-hero->x+4450, SCREEN_H-hero->x+4450, 0, 0, SCREEN_W, SCREEN_H);


                for (std::vector<Enemy>::iterator it = enemies.begin() ; it != enemies.end();)
                {
                    it->ini(hero->x);
                    it->move();
                    if(it->check_bullet(bullets))
                    {
                        deadenemies.push_back(*it);
                        it = enemies.erase(it);
                    }
                    else
                        ++it;
                }
                for (std::vector<Enemy>::iterator it = deadenemies.begin() ; it != deadenemies.end();)
                {
                    if(it->movedead())
                        it = deadenemies.erase(it);
                    else
                        ++it;
                }
                for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
                {
                    it->move();
                    if(it->del())
                        it = bullets.erase(it);
                    else
                        ++it;
                }

                g1->gravity(*hero);
                g2->gravity(*hero);
                g3->gravity(*hero);
                g4->gravity(*hero);
                g5->gravity(*hero);
                g6->gravity(*hero);
                g7->gravity(*hero);
                g8->gravity(*hero);
                g9->gravity(*hero);
                g10->gravity(*hero);
                g11->gravity(*hero);
                g12->gravity(*hero);
                g13->gravity(*hero);
                g14->gravity(*hero);
                g15->gravity(*hero);
                g16->gravity(*hero);
                g17->gravity(*hero);
                g18->gravity(*hero);

                g2->move(*hero);
                g3->move(*hero);
                g4->move(*hero);
                g5->move(*hero);
                g6->move(*hero);
                g9->move(*hero);
                g11->move(*hero);
                g12->move(*hero);
                g13->move(*hero);
                g14->move(*hero);

                hero->move(170,timer,end);
                hero->attack(bullets,attack_rest);
                moon->move(hero->x,hero->klatka,hero->anim);

                if(hero->x > 4800 )
                    end = true;
                if (key[KEY_ESC] || end)
                {
                    lvl = 0;
                    break;
                }
            }
        }
        if(lvl==3)
        {
            Sky *theme = new Sky(color->blue);

            Stars *stars[20];
            for (int i = 0; i<20; i++)
                stars[i] = new Stars();

            Ground *g1 = new Ground(0,450, SCREEN_W,false);

            Hero *hero = new Hero(400, 350,outfit_maska,outfit_wlosy);

            vector<Enemy> enemies;
            for(int i=0; i<10; i++)
            {
                Enemy *en = new Enemy(1200+(i*250),470,0,1200+(i*250));
                en->init = true;
                enemies.push_back(*en);
            }
            for(int i=0; i<10; i++)
            {
                Enemy *en = new Enemy(-2800-(i*250),470,(-2800-(i*250)),SCREEN_W);
                en->init = true;
                enemies.push_back(*en);
            }

            for(int i=0; i<3; i++)
            {
                Enemy *en = new Enemy(5400-(i*40),470,0,3400-(i*40));
                en->init = true;
                enemies.push_back(*en);
            }

            for(int i=0; i<3; i++)
            {
                Enemy *en = new Enemy(-5600-(i*40),470,-5400-(i*40),SCREEN_W);
                en->init = true;
                enemies.push_back(*en);
            }
            for(int i=0; i<3; i++)
            {
                Enemy *en = new Enemy(6300-(i*40),350,0,6300-(i*40));
                en->init = true;
                enemies.push_back(*en);
            }
            for(int i=0; i<3; i++)
            {
                Enemy *en = new Enemy(-6000-(i*40),470,-6000-(i*40),SCREEN_W);
                en->init = true;
                enemies.push_back(*en);
            }
            for(int i=0; i<6; i++)
            {
                Enemy *en = new Enemy(6600-(i*40),350,0,6300-(i*40));
                en->init = true;
                enemies.push_back(*en);
            }

            vector<Enemy> deadenemies;

            vector<Bullet> bullets;

            BITMAP * BOARD = create_bitmap(SCREEN_W, SCREEN_H);

            bool end = false;

            while (true)
            {
                clear_to_color(BOARD, color->make_color(0, 0, 0));
                engine->fullscreen();
                theme->draw(BOARD, hero->x, BOARD->w);
                for (int i = 0; i<20; i++)
                    stars[i]->draw(BOARD, hero->x, BOARD->w);



                for (std::vector<Enemy>::iterator it = enemies.begin() ; it != enemies.end();)
                {
                    it->draw(BOARD);
                    if(it->x == 300)
                        it->dest = true;
                    if(it->check_hero(buffor,*hero))
                        end = true;
                    ++it;
                }

                for (std::vector<Enemy>::iterator it = deadenemies.begin() ; it != deadenemies.end();)
                {
                    it->draw(BOARD);
                    ++it;
                }

                for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
                {
                    it->draw(BOARD);
                    ++it;
                }

                g1->draw(BOARD);


                hero->draw(BOARD,timer);

                blit(BOARD, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

                for (std::vector<Enemy>::iterator it = enemies.begin() ; it != enemies.end();)
                {
                    it->move();
                    if((it->x==it->xmin||it->x==it->xmax) && it->dest)
                    {
                        deadenemies.push_back(*it);
                        it = enemies.erase(it);
                    }
                    else
                        ++it;
                }
                for (std::vector<Enemy>::iterator it = deadenemies.begin() ; it != deadenemies.end();)
                {
                    if(it->movedead())
                        it = deadenemies.erase(it);
                    else
                        ++it;
                }
                for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
                {
                    it->move();
                    if(it->del())
                        it = bullets.erase(it);
                    else
                        ++it;
                }

                g1->gravity(*hero);

                hero->move(170,timer,end);
                hero->attack(bullets,attack_rest);

                if(enemies.size()==0)
                    end = true;
                if (key[KEY_ESC] || end)
                {
                    lvl = 0;
                    break;
                }
                rest(1);
            }
        }
        if(lvl==4)
        {
            Sky *theme = new Sky(color->blue);
            Moon *moon = new Moon();

            Stars *stars[20];
            for (int i = 0; i<20; i++)
                stars[i] = new Stars();

            Ground *g1 = new Ground(0, 450, SCREEN_W,false);

            Hero *hero = new Hero(10, -50,outfit_maska,outfit_wlosy);

            Boss_green *boss = new Boss_green(500,200);

            vector<Enemy> enemies;

            vector<Enemy> deadenemies;

            vector<Bullet> bullets;

            BITMAP * BOARD = create_bitmap(SCREEN_W, SCREEN_H);


            bool end = false;

            while (true)
            {
                clear_to_color(BOARD, color->make_color(0, 0, 0));
                engine->fullscreen();
                theme->draw(BOARD, hero->x, BOARD->w);
                rectfill(BOARD,0,SCREEN_H-20,BOARD->w,SCREEN_H,makecol(0,0,50));  // WODA
                for (int i = 0; i<20; i++)
                    stars[i]->draw(BOARD, hero->x, BOARD->w);

                moon->draw(BOARD);

                for (std::vector<Enemy>::iterator it = enemies.begin() ; it != enemies.end();)
                {
                    it->draw(BOARD);
                    if(it->check_hero(buffor,*hero))
                        end = true;
                    ++it;
                }
                for (std::vector<Enemy>::iterator it = deadenemies.begin() ; it != deadenemies.end();)
                {
                    it->draw(BOARD);
                    ++it;
                }

                for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
                {
                    it->draw(BOARD);
                    ++it;
                }

                g1->draw(BOARD);

                hero->draw(BOARD,timer);
                boss->draw(BOARD);

                blit(BOARD, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


                for (std::vector<Enemy>::iterator it = enemies.begin() ; it != enemies.end();)
                {
                    it->ini(hero->x);
                    it->move();
                    if(it->check_bullet(bullets))
                    {
                        deadenemies.push_back(*it);
                        it = enemies.erase(it);
                    }
                    else
                        ++it;
                }
                for (std::vector<Enemy>::iterator it = deadenemies.begin() ; it != deadenemies.end();)
                {
                    if(it->movedead())
                        it = deadenemies.erase(it);
                    else
                        ++it;
                }
                for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
                {
                    it->move();
                    if(it->x-100>=boss->x)
                    {
                        it = bullets.erase(it);
                        boss->hp--;
                    }

                    else if(it->del())
                        it = bullets.erase(it);
                    else
                        ++it;
                }

                g1->gravity(*hero);

                hero->move(170,timer,end);
                hero->attack(bullets,attack_rest);
                moon->move(hero->x,hero->klatka,hero->anim);
                boss->move();
                boss->attack(enemies);
                if(hero->x-80>=boss->x)
                    end = true;
                //
                if(boss->hp ==0)
                    end = true;
                if (key[KEY_ESC] || end)
                {
                    lvl = 0;
                    break;
                }
                rest(2);
            }
        }
        if(lvl==5)
        {
            Sky *theme = new Sky(color->make_color(127,127,200));

            Stars *stars[20];
            for (int i = 0; i<20; i++)
                stars[i] = new Stars();

            Ground *g1 = new Ground(20, 500, 300,false,true);
            Ground *g2 = new Ground(500, 300, 300,false,true);
            Ground *g3 = new Ground(800, 500, 600,false,true);
            Ground *g4 = new Ground(1500, 500, 100,true,true);
            Ground *g5 = new Ground(1700, 500, 100,true,true);
            Ground *g6 = new Ground(1900, 500, 100,true,true);
            Ground *g7 = new Ground(2100, 500, 400,false,true);
            Ground *g8 = new Ground(2590, 150, 420,false,true);
            Ground *g9 = new Ground(2600, 550, 1800,false,true);
            Ground *g10 = new Ground(4700, 550, 300,false,true);

            Water_clif *w1 = new Water_clif(54,570,true);
            Water_clif *w2 = new Water_clif(560,400,true);
            Water_clif *w3 = new Water_clif(700,440,true);

            Block *block1 = new Block(400,400,100,300,500,true);
            //Block *block2 = new Block(1400,150,700,300,500,true);
            Block *block3 = new Block(2510,300,80,150,500,true);
            Block *block4 = new Block(3000,150,125,3000,3600,false);
            Block *block5 = new Block(4325,150,125,3725,4325,false);

            Tree *t1 = new Tree(100,220,true);
            Tree *t2 = new Tree(550,20,true);
            Tree *t3 = new Tree(900,220,true);
            Tree *t4 = new Tree(1100,220,true);
            Tree *t5 = new Tree(2200,270,true);
            Tree *t6 = new Tree(3100,270,true);
            Tree *t7 = new Tree(3400,270,true);
            Tree *t8 = new Tree(3700,270,true);
            Tree *t9 = new Tree(4000,270,true);

            Bush *b1 = new Bush(90,460,true);
            Bush *b2 = new Bush(690,260,true);
            Bush *b3 = new Bush(1050,460,true);
            Bush *b4 = new Bush(1300,460,true);
            Bush *b5 = new Bush(2800,110,true);
            Bush *b6 = new Bush(2900,110,true);

            Telebim *tele = new Telebim(2600,300);

            Hero *hero = new Hero(10, -50,outfit_maska,outfit_wlosy);

            vector<Enemy> enemies;

            Enemy *en1 = new Enemy(600,300,500,700,true);
            Enemy *en2 = new Enemy(900,500,800,1350,true);
            Enemy *en3 = new Enemy(1200,500,800,1350,true);
            Enemy *en4 = new Enemy(2100,500,2100,2450,true);
            Enemy *en5 = new Enemy(3000,550,3000,4250,true);
            Enemy *en6 = new Enemy(3500,550,3000,4250,true);
            Enemy *en7 = new Enemy(4000,550,3000,4250,true);
            Enemy *en8 = new Enemy(4500,550,3000,4250,true);
            Enemy *en9 = new Enemy(3200,550,3000,4250,true);
            Enemy *en10 = new Enemy(3800,550,3000,4250,true);
            Enemy *en11 = new Enemy(2700,550,3000,4250,true);
            Enemy *en12 = new Enemy(3100,550,3000,4250,true);
            en5->init = true;
            en6->init = true;
            en7->init = true;
            en8->init = true;
            en9->init = true;
            en10->init = true;
            en11->init = true;
            en12->init = true;
            enemies.push_back(*en1);
            enemies.push_back(*en2);
            enemies.push_back(*en3);
            enemies.push_back(*en4);
            enemies.push_back(*en5);
            enemies.push_back(*en6);
            enemies.push_back(*en7);
            enemies.push_back(*en8);
            enemies.push_back(*en9);
            enemies.push_back(*en10);
            enemies.push_back(*en11);
            enemies.push_back(*en12);

            vector<Enemy> deadenemies;
            vector<Bullet> bullets;

            BITMAP * BOARD = create_bitmap(5000, SCREEN_H);

            BITMAP * FLAG = load_bitmap("BMP/flag.bmp",NULL);

            bool end = false;

            while (true)
            {
                clear_to_color(BOARD, color->make_color(0, 0, 0));
                engine->fullscreen();
                theme->draw(BOARD, hero->x, BOARD->w);
                rectfill(BOARD,0,SCREEN_H-20,BOARD->w,SCREEN_H,makecol(120,120,120));  // LOD

                for (int i = 0; i<20; i++)
                    stars[i]->draw(BOARD, hero->x, BOARD->w);

                t1->draw(BOARD);
                t2->draw(BOARD);
                t3->draw(BOARD);
                t4->draw(BOARD);
                t5->draw(BOARD);
                t6->draw(BOARD);
                t7->draw(BOARD);
                t8->draw(BOARD);
                t9->draw(BOARD);



                for (std::vector<Enemy>::iterator it = enemies.begin() ; it != enemies.end();)
                {
                    it->draw(BOARD);
                    if(it->check_hero(buffor,*hero))
                        end = true;
                    ++it;
                }


                for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
                {
                    it->draw(BOARD);
                    ++it;
                }



                g1->draw(BOARD);
                w1->draw(BOARD);
                g2->draw(BOARD);
                w2->draw(BOARD);
                w3->draw(BOARD);
                g3->draw(BOARD);
                g4->draw(BOARD);
                g5->draw(BOARD);
                g6->draw(BOARD);
                g7->draw(BOARD);
                g8->draw(BOARD);
                g9->draw(BOARD);
                g10->draw(BOARD);

                block1->draw(BOARD);
                //block2->draw(BOARD);
                block3->draw(BOARD);
                block4->draw(BOARD);
                block5->draw(BOARD);

                b1->draw(BOARD);
                b2->draw(BOARD);
                b3->draw(BOARD);
                b4->draw(BOARD);
                b5->draw(BOARD);
                b6->draw(BOARD);

                hero->draw(BOARD,timer);
                //std::cout<<hero->x<<std::endl;
                tele->draw(BOARD,*hero,timer);

                masked_blit(FLAG,BOARD,0,0,4800,450,FLAG->w,FLAG->h);

                if (hero->x >= CAMERA_OFFSET && hero->x <= BOARD->w - SCREEN_W + CAMERA_OFFSET)
                    blit(BOARD, screen, hero->x - CAMERA_OFFSET, 0, 0, 0, SCREEN_W, SCREEN_H);
                else if (hero->x <= CAMERA_OFFSET)                                              //LEWA STRONA PLANSZY
                    blit(BOARD, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                else                                                                             //PRAWA STRONA PLANSZY
                    masked_stretch_blit(BOARD, screen, BOARD->w - SCREEN_W+hero->x-4450, hero->x-4450, SCREEN_W-hero->x+4450, SCREEN_H-hero->x+4450, 0, 0, SCREEN_W, SCREEN_H);


                for (std::vector<Enemy>::iterator it = enemies.begin() ; it != enemies.end();)
                {
                    it->ini(hero->x);
                    it->move();
                    if(it->check_bullet(bullets))
                    {
                        it->hp--;
                        it->BMP = load_bitmap("BMP/yeti2.bmp",NULL);
                        if(it->hp == 0)
                        {
                            deadenemies.push_back(*it);
                            it = enemies.erase(it);
                        }
                    }
                    else
                        ++it;
                }
                for (std::vector<Enemy>::iterator it = deadenemies.begin() ; it != deadenemies.end();)
                {
                    if(it->movedead())
                        it = deadenemies.erase(it);
                    else
                        ++it;
                }
                for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
                {
                    it->move();
                    if(it->del())
                        it = bullets.erase(it);
                    else
                        ++it;
                }
                g1->gravity(*hero);
                g2->gravity(*hero);
                g3->gravity(*hero);
                g4->gravity(*hero);
                g5->gravity(*hero);
                g6->gravity(*hero);
                g7->gravity(*hero);
                g8->gravity(*hero);
                g9->gravity(*hero);
                g10->gravity(*hero);

                g4->move(*hero);
                g5->move(*hero);
                g6->move(*hero);

                block1->gravity(*hero);
                block3->gravity(*hero);
                block4->gravity(*hero);
                block5->gravity(*hero);

                block1->move(*hero);
                block3->move(*hero);
                block4->move(*hero);
                block5->move(*hero);


                hero->move(170,timer,end);
                hero->attack(bullets,attack_rest);
                if(hero->x > 4800 )
                    end = true;
                if (key[KEY_ESC] || end)
                {
                    lvl = 0;
                    break;
                }
            }
        }
        if(lvl==6)
        {
            Sky *theme = new Sky(color->make_color(127,127,200));

            Stars *stars[20];
            for (int i = 0; i<20; i++)
                stars[i] = new Stars();

            Ground *g1 = new Ground(0, 200, 300,false,true);
            Ground *g2 = new Ground(400, 400, 600,false,true);
            Ground *g3 = new Ground(1120, 325, 100,true,true);
            Ground *g4 = new Ground(1300, 270, 100,true,true);

            Ground *g5 = new Ground(1500, 390, 450,false,true);
            Ground *g6 = new Ground(1950, 500, 200,false,true);
            Ground *g7 = new Ground(2150, 390, 450,false,true);
            Ground *g8 = new Ground(2600, 500, 200,false,true);
            Ground *g9 = new Ground(2800, 390, 450,false,true);
            Ground *g10 = new Ground(3250, 120, 450,false,true);

            Ground *g11 = new Ground(3070, 330, 50,true,true);
            Ground *g12 = new Ground(3180, 250, 50,true,true);
            Ground *g13 = new Ground(3125, 120, 50,true,true);

            Block *block1 = new Block(300,400,80,200,400,true);

            Tree *t1 = new Tree(500,120,true);
            Tree *t2 = new Tree(1600,120,true);
            Tree *t3 = new Tree(2300,120,true);
            Tree *t4 = new Tree(2800,120,true);

            Bush *b1 = new Bush(820,360,true);
            Bush *b2 = new Bush(900,360,true);
            Bush *b3 = new Bush(2015,450,true);
            Bush *b4 = new Bush(3330,80,true);

            Hero *hero = new Hero(400, 300,outfit_maska,outfit_wlosy);

            Ice_Ball *ib1 = new Ice_Ball(3900,300,100,1600,3900);

            Button *button1 = new Button(3600,80);

            vector<Enemy> enemies;

            vector<Enemy> deadenemies;
            vector<Bullet> bullets;

            BITMAP * BOARD = create_bitmap(3700, SCREEN_H);

            BITMAP * FLAG = load_bitmap("BMP/flag.bmp",NULL);

            bool end = false;

            while (true)
            {
                clear_to_color(BOARD, color->make_color(0, 0, 0));
                engine->fullscreen();
                theme->draw(BOARD, hero->x, BOARD->w);
                rectfill(BOARD,0,SCREEN_H-20,BOARD->w,SCREEN_H,makecol(120,120,120));  // LOD

                for (int i = 0; i<20; i++)
                    stars[i]->draw(BOARD, hero->x, BOARD->w);


                t1->draw(BOARD);
                t2->draw(BOARD);
                t3->draw(BOARD);
                t4->draw(BOARD);

                b1->draw(BOARD);
                b2->draw(BOARD);
                b3->draw(BOARD);
                b4->draw(BOARD);

                for (std::vector<Enemy>::iterator it = enemies.begin() ; it != enemies.end();)
                {
                    it->draw(BOARD);
                    if(it->check_hero(buffor,*hero))
                        end = true;
                    ++it;
                }


                for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
                {
                    it->draw(BOARD);
                    ++it;
                }


                g1->draw(BOARD);
                g2->draw(BOARD);
                g3->draw(BOARD);
                g4->draw(BOARD);

                g6->draw(BOARD);
                g7->draw(BOARD);
                g8->draw(BOARD);



                g11->draw(BOARD);
                g12->draw(BOARD);
                g13->draw(BOARD);


                ib1->draw(BOARD);
                g5->draw(BOARD);

                g9->draw(BOARD);
                g10->draw(BOARD);


                block1->draw(BOARD);

                button1->draw(BOARD);

                hero->draw(BOARD,timer);
                //std::cout<<hero->x<<std::endl;

                masked_blit(FLAG,BOARD,0,0,80,110,FLAG->w,FLAG->h);

                if (hero->x >= CAMERA_OFFSET && hero->x <= BOARD->w - SCREEN_W + CAMERA_OFFSET)
                    blit(BOARD, screen, hero->x - CAMERA_OFFSET, 0, 0, 0, SCREEN_W, SCREEN_H);
                else if (hero->x <= CAMERA_OFFSET)                                              //LEWA STRONA PLANSZY
                    blit(BOARD, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                else                                                                             //PRAWA STRONA PLANSZY
                    blit(BOARD, screen, BOARD->w-SCREEN_W, 0, 0, 0, SCREEN_W, SCREEN_H);


                for (std::vector<Enemy>::iterator it = enemies.begin() ; it != enemies.end();)
                {
                    it->ini(hero->x);
                    it->move();
                    if(it->check_bullet(bullets))
                    {
                        it->hp--;
                        it->BMP = load_bitmap("BMP/yeti2.bmp",NULL);
                        if(it->hp == 0)
                        {
                            deadenemies.push_back(*it);
                            it = enemies.erase(it);
                        }
                    }
                    else
                        ++it;
                }
                for (std::vector<Enemy>::iterator it = deadenemies.begin() ; it != deadenemies.end();)
                {
                    if(it->movedead())
                        it = deadenemies.erase(it);
                    else
                        ++it;
                }
                for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
                {
                    it->move();
                    if(it->del())
                        it = bullets.erase(it);
                    else
                        ++it;
                }
                if(ib1->check_hero(*hero))
                {
                    end = true;
                }
                g1->gravity(*hero);
                g2->gravity(*hero);
                g3->gravity(*hero);
                g4->gravity(*hero);
                g5->gravity(*hero);
                g6->gravity(*hero);
                g7->gravity(*hero);
                g8->gravity(*hero);
                g9->gravity(*hero);
                g10->gravity(*hero);
                g11->gravity(*hero);
                g12->gravity(*hero);
                g13->gravity(*hero);

                g3->move(*hero);
                g4->move(*hero);
                g11->move(*hero);
                g12->move(*hero);
                g13->move(*hero);

                block1->gravity(*hero);



                ib1->move();
                if(button1->state)
                {
                    block1->move(*hero);
                    ib1->move();
                }

                button1->active(*hero,enemies);

                hero->move(170,timer,end);
                hero->attack(bullets,attack_rest);
                if(hero->x < 100 && hero->y < 200)
                    end = true;
                if (key[KEY_ESC] || end)
                {
                    lvl = 0;
                    break;
                }
            }

        }
        if(lvl==7)
        {
            Sky *theme = new Sky(color->make_color(127,127,200));

            Stars *stars[20];
            for (int i = 0; i<20; i++)
                stars[i] = new Stars();

            Ground *g1 = new Ground(0,450, SCREEN_W,false,true);

            Hero *hero = new Hero(400, 350,outfit_maska,outfit_wlosy);

            vector<Enemy> enemies;
            for(int i=0; i<10; i++)
            {
                Enemy *en = new Enemy(1200+(i*250),470,0,1200+(i*250),true);
                std::cout<<"s"<<std::endl;
                if(i%3==0)
                {
                    en = new Enemy(-1200-(i*250),470,(-1200-(i*250)),SCREEN_W,true);
                }
                en->init = true;
                enemies.push_back(*en);
            }
            for(int i=0; i<10; i++)
            {
                Enemy *en = new Enemy(-2800-(i*250),470,(-2800-(i*250)),SCREEN_W,true);
                if(i%3==0)
                {
                    en = new Enemy(1200+(i*250),470,0,1200+(i*250),true);
                }
                en->init = true;
                enemies.push_back(*en);
            }

            for(int i=0; i<3; i++)
            {
                Enemy *en = new Enemy(5400-(i*40),470,0,3400-(i*40),true);
                en->init = true;
                enemies.push_back(*en);
            }

            for(int i=0; i<3; i++)
            {
                Enemy *en = new Enemy(-5600-(i*40),470,-5400-(i*40),SCREEN_W,true);
                en->init = true;
                enemies.push_back(*en);
            }
            for(int i=0; i<3; i++)
            {
                Enemy *en = new Enemy(6300-(i*40),350,0,6300-(i*40),true);
                en->init = true;
                enemies.push_back(*en);
            }
            for(int i=0; i<3; i++)
            {
                Enemy *en = new Enemy(-6000-(i*40),470,-6000-(i*40),SCREEN_W,true);
                en->init = true;
                enemies.push_back(*en);
            }
            for(int i=0; i<6; i++)
            {
                Enemy *en = new Enemy(6600-(i*40),350,0,6300-(i*40),true);
                en->init = true;
                enemies.push_back(*en);
            }
            for(int i=0; i<16; i++)
            {
                Enemy *en = new Enemy(-6500-(i*250),470,(-6500-(i*250)),SCREEN_W,true);
                if(i%2==0)
                {
                    en = new Enemy(6900+(i*250),470,0,6900+(i*250),true);
                }
                en->init = true;
                enemies.push_back(*en);
            }
            for(int i=0; i<16; i++)
            {
                Enemy *en = new Enemy(-12000-(i*400),470,(-6500-(i*400)),SCREEN_W,true);
                if(i%2==0&& i<8)
                {
                    en = new Enemy(6900+(i*400),470,0,6900+(i*400),true);

                }
                if(i>8)
                    i++;
                en->hp = 1;
                en->BMP  = load_bitmap("BMP/yeti2.bmp",NULL);
                en->init = true;
                enemies.push_back(*en);
            }

            vector<Enemy> deadenemies;

            vector<Bullet> bullets;

            BITMAP * BOARD = create_bitmap(SCREEN_W, SCREEN_H);

            bool end = false;

            while (true)
            {
                clear_to_color(BOARD, color->make_color(0, 0, 0));
                engine->fullscreen();
                theme->draw(BOARD, hero->x, BOARD->w);
                for (int i = 0; i<20; i++)
                    stars[i]->draw(BOARD, hero->x, BOARD->w);



                for (std::vector<Enemy>::iterator it = enemies.begin() ; it != enemies.end();)
                {
                    it->draw(BOARD);
                    if(it->x == 300)
                        it->dest = true;
                    if(it->check_hero(buffor,*hero))
                        end = true;
                    ++it;
                }

                for (std::vector<Enemy>::iterator it = deadenemies.begin() ; it != deadenemies.end();)
                {
                    it->draw(BOARD);
                    ++it;
                }

                for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
                {
                    it->draw(BOARD);
                    ++it;
                }

                g1->draw(BOARD);


                hero->draw(BOARD,timer);

                blit(BOARD, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

                for (std::vector<Enemy>::iterator it = enemies.begin() ; it != enemies.end();)
                {
                    it->move();
                    if((it->x==it->xmin||it->x==it->xmax) && it->dest)
                    {
                        deadenemies.push_back(*it);
                        it = enemies.erase(it);
                    }
                    else
                        ++it;
                }
                for (std::vector<Enemy>::iterator it = deadenemies.begin() ; it != deadenemies.end();)
                {
                    if(it->movedead())
                        it = deadenemies.erase(it);
                    else
                        ++it;
                }
                for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
                {
                    it->move();
                    if(it->del())
                        it = bullets.erase(it);
                    else
                        ++it;
                }

                g1->gravity(*hero);

                hero->move(170,timer,end);
                hero->attack(bullets,attack_rest);
                if(enemies.size()==0)
                    end = true;
                if (key[KEY_ESC] || end)
                {
                    lvl = 0;
                    break;
                }
                rest(2);
            }
        }
        if(lvl==8)
        {
            Sky *theme = new Sky(color->make_color(127,127,200));
            Moon *moon = new Moon();

            Stars *stars[20];
            for (int i = 0; i<20; i++)
                stars[i] = new Stars();

            Ground *g1 = new Ground(0, 550, SCREEN_W,false,true);

            Block *b1 = new Block(100,200,SCREEN_W-200,0,100,false);
            Block *b2 = new Block(0,400,100,200,520,true);
            Block *b3 = new Block(700,400,100,200,520,true);

            Hero *hero = new Hero(10, -50,outfit_maska,outfit_wlosy);

            Boss_ice *boss = new Boss_ice(350,300);

            vector<Enemy> enemies;

            vector<Enemy> deadenemies;

            vector<Bullet> bullets;

            BITMAP * BOARD = create_bitmap(SCREEN_W, SCREEN_H);


            bool end = false;

            while (true)
            {
                clear_to_color(BOARD, color->make_color(0, 0, 0));
                engine->fullscreen();
                theme->draw(BOARD, hero->x, BOARD->w);
                rectfill(BOARD,0,SCREEN_H-20,BOARD->w,SCREEN_H,makecol(0,0,50));  // WODA
                for (int i = 0; i<20; i++)
                    stars[i]->draw(BOARD, hero->x, BOARD->w);

                moon->draw(BOARD);

                for (std::vector<Enemy>::iterator it = enemies.begin() ; it != enemies.end();)
                {
                    it->draw(BOARD);
                    if(it->check_hero(buffor,*hero))
                        end = true;
                    ++it;
                }
                for (std::vector<Enemy>::iterator it = deadenemies.begin() ; it != deadenemies.end();)
                {
                    it->draw(BOARD);
                    ++it;
                }

                for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
                {
                    it->draw(BOARD);
                    ++it;
                }

                g1->draw(BOARD);

                b1->draw(BOARD);
                b2->draw(BOARD);
                b3->draw(BOARD);

                hero->draw(BOARD,timer);

                boss->draw(BOARD);

                blit(BOARD, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


                for (std::vector<Enemy>::iterator it = enemies.begin() ; it != enemies.end();)
                {
                    it->ini(hero->x);
                    it->move();
                    if(it->check_bullet(bullets))
                    {
                        it->hp--;
                        it->BMP = load_bitmap("BMP/yeti2.bmp",NULL);
                        if(it->hp == 0)
                        {
                            deadenemies.push_back(*it);
                            it = enemies.erase(it);
                        }
                    }
                    else
                        ++it;
                }
                for (std::vector<Enemy>::iterator it = deadenemies.begin() ; it != deadenemies.end();)
                {
                    if(it->movedead())
                        it = deadenemies.erase(it);
                    else
                        ++it;
                }
                for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
                {
                    it->move();
                    if(boss->x+30  < it->x && boss->x+70 > it->x && boss->y+10<it->y && boss->y+80 >it->y )                //BOSS ATTACK
                    {
                        it = bullets.erase(it);
                        boss->hp--;
                        boss->add_red();
                    }

                    else if(it->del())
                        it = bullets.erase(it);
                    else
                        ++it;
                }

                g1->gravity(*hero);

                b1->gravity(*hero);
                b2->gravity(*hero);
                b3->gravity(*hero);

                b2->move(*hero);
                b3->move(*hero);

                boss->attack(enemies,*hero);
                hero->move(170,timer,end);
                hero->attack(bullets,attack_rest);
                if(boss->hp ==0)
                    end = true;

                if(boss->check_hero(*hero))
                {
                    end =true;
                }
                if (key[KEY_ESC] || end)
                {
                    lvl = 0;
                    break;
                }
                rest(2);
            }
        }
    }
    return 0;
}
END_OF_MAIN()
